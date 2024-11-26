#include "mylrc.h"
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>

const int lrclength = 1800;
const int lrcwidth = 60;

MyLrc::MyLrc(QWidget * parent) : QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //设置透明背景
    setAttribute(Qt::WA_TranslucentBackground);
    //固定部件大小
    setMaximumSize(lrclength, lrcwidth);
    setMinimumSize(lrclength, lrcwidth);

    //歌词的线性渐变填充
    linearGradient.setStart(0, 10);
    linearGradient.setFinalStop(0, 40);
    linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    // 遮罩的线性渐变填充
    maskLinearGradient.setStart(0, 10);
    maskLinearGradient.setFinalStop(0, 40);
    maskLinearGradient.setColorAt(0.1, QColor(222, 54, 4));
    maskLinearGradient.setColorAt(0.5, QColor(255, 72, 16));
    maskLinearGradient.setColorAt(0.9, QColor(222, 54, 4));
    //设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);
    //设置定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    lrcMaskWidth = 0;
    lrcMaskWidthInterval = 0;
}

//定时器溢出增加遮罩宽度并更新
void MyLrc::timeout()
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();
}

void MyLrc::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(font);
    //先绘制底层文字作为阴影， 再在上面绘制渐变文字，这样会使显示效果更加清晰更有质感
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(1, 1, lrclength, 60, Qt::AlignLeft, text());
    painter.setPen(QPen(linearGradient, 0));
    painter.drawText(0, 0, lrclength, 60, Qt::AlignLeft, text());
    //设置歌词遮罩
    painter.setPen(QPen(maskLinearGradient, 0));
    painter.drawText(0, 0, lrcMaskWidth, 60, Qt::AlignLeft, text());
}

//开启遮罩，需要制定当前歌词开始与结束的时间间隔
void MyLrc::startLrcMask(qint64 intervalTime)
{
    qreal count = intervalTime / 30;
    //获取遮罩每次增加宽度
    lrcMaskWidthInterval = lrclength / count;
    lrcMaskWidth = 0;
    timer->start(30);
}

//停止遮罩
void MyLrc::stopLrcMask()
{
    timer->stop();
    lrcMaskWidth = 0;
    update();
}
//暂停状态遮罩
void MyLrc::pauseLrcMask()
{
    timer->stop();
    mask_returnFromPause = true;
    update();
}

void MyLrc::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        offset = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void MyLrc::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::PointingHandCursor);
        move(event->globalPosition().toPoint() - offset);
    }
}

//实现右键菜单
void MyLrc::contextMenuEvent(QContextMenuEvent * event)
{
    QMenu menu;
    menu.addAction("隐藏", this, SLOT(hide()));
    menu.exec(event->globalPos());
}

//返回计时器
QTimer * MyLrc::lrcTimer()
{
    return this->timer;
}

//返回歌词遮罩播放状态
bool & MyLrc::mask_flag_from_pause()
{
    return this->mask_returnFromPause;
}
