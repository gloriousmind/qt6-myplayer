#include "mywidget.h"
#include "ui_mywidget.h"
#include "mylrc.h"
#include <QIcon>
#include <QLabel>
#include <QSlider>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTime>
#include <QMessageBox>
#include "myplaylist.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTextCodec>
#include <QPoint>
#include <QMenu>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    initPlayer();
}

MyWidget::~MyWidget()
{
    delete ui;
}

//初始化播放器
void MyWidget::initPlayer()
{
    //设置主界面标题，图标和大小
    setWindowTitle("MyPlayer音乐播放器");
    setWindowIcon(QIcon(":/images/myImages/icon.png"));
    setMinimumSize(640, 320);
    setMaximumSize(960, 480);
    //创建播放器
    mediaObject_ctrl_playback = new QMediaPlayer(this);
    mediaObject_ctrl_resolve = new QMediaPlayer(this);
    audiooutput = new QAudioOutput;
    mediaObject_ctrl_playback->setAudioOutput(audiooutput);
    //关联持续时间信号来更新播放时间
    connect(mediaObject_ctrl_playback, SIGNAL(positionChanged(qint64)), this, SLOT(updateTime(qint64)));

    //创建顶部标签，用于显示一些信息
    topLabel = new QLabel("<a href = \"http://www.kugou.com\">www.kugou.com</a>");
    topLabel->setTextFormat(Qt::RichText);
    topLabel->setOpenExternalLinks(true);
    topLabel->setAlignment(Qt::AlignCenter);

    //创建控制播放进度的滑块
    mediaProgress = new QSlider(Qt::Horizontal, this);
    connect(mediaObject_ctrl_playback, &QMediaPlayer::positionChanged, mediaProgress, [=] (){ //只有当加载媒体文件触发信号之后才可以设置进度条大小，没有加载文件之前没有大小可以设置
        mediaProgress->setRange(0, mediaObject_ctrl_playback->duration());
        mediaProgress->setValue(mediaObject_ctrl_playback->position());
    });

    connect(mediaProgress, &QSlider::sliderMoved, mediaObject_ctrl_playback, [=] (){
        mediaObject_ctrl_playback->setPosition(mediaProgress->value());
    });

    //创建包含播放列表图标，显示时间标签，和桌面歌词的工具栏
    QToolBar * widgetBar = new QToolBar(this);
    //显示播放时间标签
    timeLabel = new QLabel("00:00 / 00:00", this);
    timeLabel->setToolTip("当前时间 / 总时间");
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    //创建图标用于控制是否显示播放列表
    QAction *PLAction = new QAction("PL", this);
    PLAction->setShortcut(QKeySequence("F4"));
    PLAction->setToolTip("播放列表(F4)");
    connect(PLAction, SIGNAL(triggered()), this, SLOT(setPlaylistShown()));
    //创建图标，用于控制是否显示桌面歌词
    QAction * LRCAction = new QAction("LRC", this);
    LRCAction->setShortcut(QKeySequence("F2"));
    LRCAction->setToolTip("桌面歌词(F2)");
    connect(LRCAction, SIGNAL(triggered()), this, SLOT(setLrcShown()));
    //添加到工具栏
    widgetBar->addAction(PLAction);
    widgetBar->addSeparator();
    widgetBar->addWidget(timeLabel);
    widgetBar->addSeparator();
    widgetBar->addAction(LRCAction);

    //创建播放控制动作工具栏
    QToolBar * toolBar = new QToolBar(this);
    //播放动作
    playerpauseAction = new QAction(this);
    playerpauseAction->setIcon(QIcon(":/images/myImages/play.png"));
    playerpauseAction->setText("播放(F5)");
    playerpauseAction->setShortcut(QKeySequence("F5"));
    connect(playerpauseAction, SIGNAL(triggered()), this, SLOT(set_play_or_pause()));
    //停止动作
    stopAction = new QAction(this);
    stopAction->setIcon(QIcon(":/images/myImages/stop.png"));
    stopAction->setText("停止(F6)");
    stopAction->setShortcut(QKeySequence("F6"));
    connect(stopAction, SIGNAL(triggered()), this, SLOT(setStop()));
    //跳转到上一首动作
    skipBackwardAction = new QAction(this);
    skipBackwardAction->setIcon(QIcon(":/images/myImages/skipBackward.png"));
    skipBackwardAction->setText("上一首(Ctrl+Left)");
    skipBackwardAction->setShortcut(QKeySequence("Ctrl+Left"));
    connect(skipBackwardAction, SIGNAL(triggered()), this, SLOT(skipBackward()));
    // 跳转到下一首动作
    skipForwardAction = new QAction(this);
    skipForwardAction->setIcon(QIcon(":/images/myImages/skipForward.png"));
    skipForwardAction->setText("下一首(Ctrl+Right)");
    skipForwardAction->setShortcut(QKeySequence("Ctrl+Right"));
    connect(skipForwardAction, SIGNAL(triggered()), this, SLOT(skipForward()));
    //打开文件动作
    QAction * openAction = new QAction(this);
    openAction->setIcon(QIcon(":/images/myImages/open.png"));
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    //控制音量部件
    QSlider * volumeSlider = new QSlider(Qt::Horizontal, this);

    mediaObject_ctrl_playback->audioOutput()->setVolume(0.5);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setValue(50);
    connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(mywidget_setVolume(int)));
    //添加动作到工具栏
    toolBar->addAction(playerpauseAction);
    toolBar->addSeparator();
    toolBar->addAction(stopAction);
    toolBar->addSeparator();
    toolBar->addAction(skipBackwardAction);
    toolBar->addSeparator();
    toolBar->addAction(skipForwardAction);
    toolBar->addSeparator();
    toolBar->addWidget(volumeSlider);
    toolBar->addSeparator();
    toolBar->addAction(openAction);

    //创建界面布局管理器
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topLabel);
    mainLayout->addWidget(mediaProgress);
    mainLayout->addWidget(widgetBar);
    mainLayout->addWidget(toolBar);
    setLayout(mainLayout);

    connect(mediaObject_ctrl_playback, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this, SLOT(playbackStateChanged(QMediaPlayer::PlaybackState)));
    connect(mediaObject_ctrl_playback, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(playback_mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(mediaObject_ctrl_resolve, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(resolve_mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(mediaObject_ctrl_playback, SIGNAL(errorOccurred(QMediaPlayer::Error, const QString &)),
            this, SLOT(showError(QMediaPlayer::Error, const QString &)));

    playlist = new MyPlaylist(this);
    playlist->resize(400, this->height());
    connect(playlist, QTableWidget::cellDoubleClicked, this, &tableDoubleClicked);
    connect(playlist, SIGNAL(playlistClean()), this, SLOT(clearSources()));
    connect(mediaObject_ctrl_playback, SIGNAL(sourceChanged(const QUrl &)), this, SLOT(playback_sourceChanged(const QUrl &)));

    //初始化动作图标状态
    playerpauseAction->setEnabled(false);
    stopAction->setEnabled(false);
    skipBackwardAction->setEnabled(false);
    skipForwardAction->setEnabled(false);
    topLabel->setFocus();

    //创建歌词部件
    lrc = new MyLrc(this);

    //创建系统盘图标
    trayIcon = new QSystemTrayIcon(QIcon(":/images/myImages/icon.png"), this);
    trayIcon->setToolTip("MyPlayer 音乐播放器");
    //创建菜单
    QMenu * menu = new QMenu;
    QList<QAction *> actions;
    actions << playerpauseAction << stopAction << skipBackwardAction << skipForwardAction;
    menu->addActions(actions);
    menu->addSeparator();
    menu->addAction(PLAction);
    menu->addAction(LRCAction);
    menu->addSeparator();
    menu->addAction("退出", qApp, SLOT(quit()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setContextMenu(menu);

    trayIcon->show();
}

//更新timeLabel标签显示的播放时间
void MyWidget::updateTime(qint64 time)
{
    qint64 totalTimeValue = mediaObject_ctrl_playback->duration();
    QTime totalTime(0, totalTimeValue / 60000 % 60, (totalTimeValue / 1000) % 60);
    QTime currentTime(0, time / 60000 % 60, (time / 1000) % 60);
    QString str = currentTime.toString("mm:ss") + " / " + totalTime.toString("mm:ss");
    timeLabel->setText(str);


    //歌词显示更新
    if (!lrcMap.empty())
    {
        int cur_time = 0;
        int next_time = 0;
        foreach (qint64 value, lrcMap.keys())
        {
            if (time >= value)
                cur_time = value;
            else
            {
                next_time = value;
                break;
            }
        }
        if (next_time == 0)
        {
            next_time = totalTimeValue;
        }
        QString curlrc = lrcMap[cur_time];
        if (curlrc.length() < 2)
            curlrc = "MyPlayer音乐播放器";
        if (curlrc != lrc->text())
        {
            lrc->setText(curlrc);
            topLabel->setText(curlrc);
            qint64 interval = next_time - cur_time;
            lrc->startLrcMask(interval);
        }
    }
    else
    {
        topLabel->setText(mediaObject_ctrl_playback->source().fileName());
    }
}

// 打开文件，与openAction动作的触发信号关联
void MyWidget::openFile()
{
    //从系统音乐目录打开多个音乐文件
    QStringList dir = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    QStringList list = QFileDialog::getOpenFileNames(this, "打开音乐文件", dir[0]);
    if (list.empty())
        return;
    //将打开的音乐文件添加到媒体源列表后
    QUrl cur_media;
    int old_size = sources.size();
    foreach(QString songstring, list)
    {
        cur_media = QUrl::fromLocalFile(songstring);
        if (sources.count(cur_media) == 0)
        {
            sources.append(cur_media);
        }
        else
            QMessageBox::warning(this, "媒体源信息", QString("%1已在列表中").arg(QFileInfo(songstring).baseName()));
    }
    if (sources.size() > old_size) //检查是否有新添加的媒体源
    {
        mediaObject_ctrl_resolve->setSource(sources[old_size]);
    }
}

//解析文件及相应解析后状态处理
void MyWidget::resolve_extractmetaData()
{
    //若产生错误状态从媒体源去除新添加的媒体源
    if (mediaObject_ctrl_playback->error() != QMediaPlayer::NoError)
    {
        while (!sources.empty() && !(sources.takeLast() == mediaObject_ctrl_resolve->source()))
        {}
    }

    QMediaMetaData cur_mediametadata= mediaObject_ctrl_resolve->metaData();
    //获取标题，如果为空使用文件名
    QString title = cur_mediametadata.stringValue(QMediaMetaData::Title);
    if (title == "")
        title = mediaObject_ctrl_resolve->source().fileName();
    QTableWidgetItem * titleItem = new QTableWidgetItem(title);
    titleItem->setFlags(titleItem->flags() & (~Qt::ItemIsEditable)); //设置数据项不可编辑

    //获取艺术家信息
    QStringList author_list= cur_mediametadata.value(QMediaMetaData::Author).toStringList();
    QString author = "";
    foreach (QString each_author, author_list)
    {
        author += each_author;
        author += " ";
    }
    author.removeLast();
    if (author.isEmpty())
    {
        author = mediaObject_ctrl_resolve->source().fileName().split('-').first();
    }
    QTableWidgetItem * artistItem = new QTableWidgetItem(author);
    artistItem->setFlags(artistItem->flags() & (~Qt::ItemIsEditable));

    //获取总时间信息
    qint64 totalTime = cur_mediametadata.value(QMediaMetaData::Duration).toInt();
    QTime time(0, (totalTime / 60000) % 60, (totalTime / 1000) % 60);
    QTableWidgetItem * timeItem = new QTableWidgetItem(time.toString("mm:ss"));

    //将获取信息插入到播放列表
    int currentRow = playlist->rowCount();
    playlist->insertRow(currentRow);
    playlist->setItem(currentRow, 0, titleItem);
    playlist->setItem(currentRow, 1, artistItem);
    playlist->setItem(currentRow, 2, timeItem);

    int index = sources.indexOf(mediaObject_ctrl_resolve->source());
    if (index < sources.size() - 1)
    {
        mediaObject_ctrl_resolve->setSource(sources[index + 1]);
    }
    else
        changeActionState();
}

//根据媒体源内容和当前媒体源的位置改变主界面图标的状态
void MyWidget::changeActionState()
{
    //如果媒体源列表为空
    if (sources.count() == 0)
    {
        //播放列表为空且处于停止状态，播放和停止都不可用
        if (mediaObject_ctrl_playback->playbackState() == QMediaPlayer::StoppedState)
        {
            playerpauseAction->setEnabled(false);
            stopAction->setEnabled(false);
            playerpauseAction->setIcon(QIcon(":image/images/play.png"));
        }
        skipBackwardAction->setEnabled(false);
        skipForwardAction->setEnabled(false);
    }
    else //播放列表不为空
    {
        playerpauseAction->setEnabled(true);
        if (mediaObject_ctrl_playback->playbackState() == QMediaPlayer::StoppedState)
        {
            stopAction->setEnabled(false);
            timeLabel->setText("00:00 / 00:00");
            mediaProgress->setRange(0, mediaObject_ctrl_playback->duration());
            mediaProgress->setValue(0);
            playerpauseAction->setIcon(QIcon(":/images/myImages/play.png"));
            playerpauseAction->setText("播放(F5)");
            lrc->stopLrcMask();
            this->lrcMap.clear();
            lrc->setText("MyMediaPlayer");
        }
        else
            stopAction->setEnabled(true);
        if (!sources.contains(mediaObject_ctrl_playback->source()) || sources.count() == 1)
        {
            skipBackwardAction->setEnabled(false);
            skipForwardAction->setEnabled(false);
        }
        else
        {
            skipBackwardAction->setEnabled(true);
            skipForwardAction->setEnabled(true);
            int index = sources.indexOf(mediaObject_ctrl_playback->source());
            if (index == 0)
                skipBackwardAction->setEnabled(false);
            if (index + 1 == sources.count())
                skipForwardAction->setEnabled(false);
        }
    }
}

//播放或暂停
void MyWidget::set_play_or_pause()
{
    if (mediaObject_ctrl_playback->playbackState() == QMediaPlayer::PlayingState)
    {
        mediaObject_ctrl_playback->pause();
    }
    else
    {
        if (mediaObject_ctrl_playback->mediaStatus() == QMediaPlayer::NoMedia && !sources.empty())
            mediaObject_ctrl_playback->setSource(sources[0]);
        mediaObject_ctrl_playback->play();
    }
}

//播放器点击了停止
void MyWidget::setStop()
{
    mediaObject_ctrl_playback->stop();
    if (sources.size() > 0)
        mediaObject_ctrl_playback->setSource(sources[0]);
    else
        mediaObject_ctrl_playback->setSource(QUrl());
    changeActionState();
}

// 播放上一首，与skipBackwardAction动作的触发信号关联
void MyWidget::skipBackward()
{
    lrc->stopLrcMask();
    int index = sources.indexOf(mediaObject_ctrl_playback->source());
    mediaObject_ctrl_playback->setSource(sources[index - 1]);
    mediaObject_ctrl_playback->play();
}

// 播放下一首，与skipForwardAction动作的触发信号关联
void MyWidget::skipForward()
{
    lrc->stopLrcMask();
    int index = sources.indexOf(mediaObject_ctrl_playback->source());
    mediaObject_ctrl_playback->setSource(sources[index + 1]);
    mediaObject_ctrl_playback->play();
}

//单击播放列表某一行的响应
void MyWidget::tableDoubleClicked(int row)
{
    //如果点击的行号大于媒体源列表大小直接返回
    if (row >= sources.size())
    {
        return;
    }
    mediaObject_ctrl_playback->setSource(sources[row]);
    mediaObject_ctrl_playback->play();
}

//清空QList中的媒体源
void MyWidget::clearSources()
{
    sources.clear();
    mediaObject_ctrl_resolve->setSource(QUrl());
    changeActionState();
}

// 显示或者隐藏播放列表，与PLAction动作的触发信号关联
void MyWidget::setPlaylistShown()
{
    if (playlist->isHidden())
    {
        playlist->move(frameGeometry().topRight());
        playlist->show();
    }
    else
        playlist->hide();
}

//媒体对象状态改变
void MyWidget::playbackStateChanged(QMediaPlayer::PlaybackState newState)
{
    switch (newState)
    {
    case QMediaPlayer::StoppedState:
        break;
    case QMediaPlayer::PlayingState:
        stopAction->setEnabled(true);
        playerpauseAction->setIcon(QIcon(":/images/myImages/pause.png"));
        playerpauseAction->setText("暂停(F5)");
        topLabel->setText((mediaObject_ctrl_playback->source().fileName()));
        if (lrc->mask_flag_from_pause())
        {
            lrc->mask_flag_from_pause() = false;
            lrc->lrcTimer()->start(30);
        }
        else
            resolveLrc(mediaObject_ctrl_playback->source().toLocalFile());
        break;
    case QMediaPlayer::PausedState:
        stopAction->setEnabled(true);
        playerpauseAction->setIcon(QIcon(":/images/myImages/play.png"));
        playerpauseAction->setText("播放(F5)");
        if (!lrcMap.empty())
        {
            lrc->pauseLrcMask();
        }
        topLabel->setText(mediaObject_ctrl_playback->source().fileName() + " 已暂停！");
        break;
    default: break;
    }
}

void MyWidget::playback_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status)
    {
    case QMediaPlayer::NoMedia:
        topLabel->setText("没有媒体文件！");
        break;
    case QMediaPlayer::BufferingMedia:
        topLabel->setText("正在缓冲媒体文件！");
        break;
    case QMediaPlayer::BufferedMedia:
        topLabel->setText("媒体文件缓冲完成！");
        break;
    case QMediaPlayer::LoadingMedia:
        topLabel->setText("正在加载媒体！");
        break;
    case QMediaPlayer::StalledMedia:
        topLabel->setText("播放停滞！");
        break;
    case QMediaPlayer::EndOfMedia:
    {
        int index = sources.indexOf(mediaObject_ctrl_playback->source());
        if (index < sources.size() - 1)
        {
            mediaObject_ctrl_playback->setSource(sources[index + 1]);
            mediaObject_ctrl_playback->play();
        }
        else
        {
            mediaObject_ctrl_playback->setSource(sources[0]);
        }
        break;
    }
    case QMediaPlayer::LoadedMedia:
        topLabel->setText("媒体加载完成！");
        break;
    case QMediaPlayer::InvalidMedia:
        topLabel->setText("不可用的媒体文件！");
        break;
    default: break;
    }
}

void MyWidget::resolve_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
    case QMediaPlayer::LoadedMedia:
        resolve_extractmetaData();
        break;
    default: break;
    }
}

void MyWidget::showError(QMediaPlayer::Error error, const QString &errorString)
{
    switch (error)
    {
    case QMediaPlayer::NoError:
        break;
    case QMediaPlayer::ResourceError:
        QMessageBox::warning(this, "错误", errorString);
        break;
    case QMediaPlayer::FormatError:
        QMessageBox::warning(this, "错误", errorString);
        break;
    case QMediaPlayer::NetworkError:
        QMessageBox::warning(this, "错误", errorString);
        break;
    case QMediaPlayer::AccessDeniedError:
        QMessageBox::warning(this, "错误", errorString);
        break;
    default: break;
    }
}

//当前播放媒体源改变时，播放列表中选择相应的行并更新图标状态
void MyWidget::playback_sourceChanged(const QUrl &media)
{
    int index = sources.indexOf(media);
    playlist->selectRow(index);
    changeActionState();
}

// 显示或者隐藏桌面歌词，与LRCAction动作的触发信号关联
void MyWidget::setLrcShown()
{
    if (lrc->isHidden())
    {
        QPoint pos;
        pos.setX(frameGeometry().bottomLeft().x());
        pos.setY(frameGeometry().bottomLeft().y() + 50);
        lrc->move(pos);
        lrc->show();
    }
    else
        lrc->hide();
}

void MyWidget::mywidget_setVolume(int volume)
{
    float audio_volume = volume / 100.0;
    this->mediaObject_ctrl_playback->audioOutput()->setVolume(audio_volume);
}

//解析Lrc歌词
void MyWidget::resolveLrc(const QString & sourceFileName)
{
    //先清空以前的内容
    lrcMap.clear();
    //获取Lrc歌词文件名， 去掉歌曲文件名后缀替换为lrc,即为歌词文件名
    if (sourceFileName.isEmpty())
        return;
    QString fileName_local_path = sourceFileName;
    QString lrcFileName = fileName_local_path.remove(fileName_local_path.right(3)) + "lrc";
    //打开歌词文件
    QFile file(lrcFileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        lrc->setText(mediaObject_ctrl_playback->source().fileName() + " --- 未找到歌词文件");
        return;
    }
    //获取全部歌词信息
    QString allText = QString(file.readAll());
    file.close();
    QStringList lines = allText.split("\n");

    //使用正则表达式将时间标签和歌词内容分离
    QRegularExpression rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach (QString oneLine, lines)
    {
        QString temp = oneLine;
        temp.replace(rx, "");
        QRegularExpressionMatchIterator pos = rx.globalMatch(oneLine, 0);
        while (pos.hasNext())
        {
            QRegularExpressionMatch cur_match = pos.next();
            QRegularExpression cur_rx;
            cur_rx.setPattern("\\d{2}(?=\\:)");
            QRegularExpressionMatchIterator pos_sub = cur_rx.globalMatch(cur_match.captured(), 0);
            int minute = pos_sub.next().captured().toInt();
            cur_rx.setPattern("\\d{2}(?=\\.)");
            pos_sub = cur_rx.globalMatch(cur_match.captured(), 0);
            int seconds = pos_sub.next().captured().toInt();
            cur_rx.setPattern("\\d{2}(?=\\])");
            pos_sub = cur_rx.globalMatch(cur_match.captured(), 0);
            int miliseconds = pos_sub.next().captured().toInt(); //歌词文件里面代表的是十毫秒
            int total_time = minute * 60 * 1000 + seconds * 1000 + miliseconds * 10;
            lrcMap.insert(total_time, temp);
        }
    }
    if (lrcMap.empty())
    {
        lrc->setText(mediaObject_ctrl_playback->source().fileName() + " --- 歌词文件内容错误! ");
        return;
    }
}

//系统托盘被激活
void MyWidget::trayIconActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    //如果单击了系统托盘图标则显示主界面
    if (activationReason == QSystemTrayIcon::Trigger)
        show();
}

//关闭事件处理函数
void MyWidget::closeEvent(QCloseEvent * event)
{
    if (isVisible())
    {
        hide();
        trayIcon->showMessage("MyPlayer 音乐播放器", "点击重新显示主界面");
        event->ignore();
    }
}
