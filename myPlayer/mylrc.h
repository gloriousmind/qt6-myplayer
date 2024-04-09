#ifndef MYLRC_H
#define MYLRC_H

#include <QLabel>
#include <QTimer>

class MyLrc : public QLabel
{
    Q_OBJECT
public:
    explicit MyLrc(QWidget * parent = 0);
    void startLrcMask(qint64 intervalTime);
    void stopLrcMask();
    void pauseLrcMask();
    QTimer * lrcTimer();
    bool & mask_flag_from_pause();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void contextMenuEvent(QContextMenuEvent * event);

private slots:
    void timeout();

private:
    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
    QFont font;
    QTimer * timer;
    qreal lrcMaskWidth;
    qreal lrcMaskWidthInterval; //每次歌词遮罩增加的宽度
    QPoint offset;
    bool mask_returnFromPause = false;
};

#endif // MYLRC_H
