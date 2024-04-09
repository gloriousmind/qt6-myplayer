#include "myplaylist.h"
#include <QMenu>
#include <QContextMenuEvent>

MyPlaylist::MyPlaylist(QWidget * parent) : QTableWidget(parent)
{
    setWindowTitle("播放列表");
    setWindowFlags(Qt::Window);
    setMaximumWidth(960);
    setMinimumWidth(380);

    setRowCount(0);
    setColumnCount(3);
    //设置表头标签
    QStringList list;
    list << "标题" << "艺术家" << "长度";

    setHorizontalHeaderLabels(list);
    //设置只能选择单行
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不显示网格
    setShowGrid(false);
}

//背景菜单事件处理函数，点击鼠标右键时运行一个菜单
void MyPlaylist::contextMenuEvent(QContextMenuEvent * event)
{
    QMenu menu;
    menu.addAction("清空列表", this, SLOT(clearPlaylist()));
    menu.exec(event->globalPos());
}

//清空列表
void MyPlaylist::clearPlaylist()
{
    while (rowCount())
        removeRow(0);
    emit playlistClean();
}

//关闭事件处理函数，如果部件处于显示状态，则使其隐蔽
void MyPlaylist::closeEvent(QCloseEvent * event)
{
    if (isVisible())
    {
        event->accept();
    }
}

