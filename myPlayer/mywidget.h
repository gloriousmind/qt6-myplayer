#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QCloseEvent>
#include <QSlider>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class QLabel;
class MyPlaylist;
class MyLrc;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void updateTime(qint64 time);
    void set_play_or_pause();
    void setStop();
    void skipBackward();
    void skipForward();
    void openFile();
    void setPlaylistShown();
    void setLrcShown();
    void mywidget_setVolume(int);

    void playbackStateChanged(QMediaPlayer::PlaybackState newState);
    void playback_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void resolve_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void showError(QMediaPlayer::Error error, const QString &errorString);
    void playback_sourceChanged(const QUrl &media);
    void resolve_extractmetaData();
    void tableDoubleClicked(int row);
    void clearSources();

    void trayIconActivated(QSystemTrayIcon::ActivationReason activationReason);

private:
    Ui::MyWidget *ui;
    void initPlayer();
    QMediaPlayer * mediaObject_ctrl_playback;
    QMediaPlayer * mediaObject_ctrl_resolve;
    QAudioOutput * audiooutput;
    QAction *playerpauseAction;
    QAction *stopAction;
    QAction *skipBackwardAction;
    QAction *skipForwardAction;
    QLabel *topLabel;
    QLabel *timeLabel;
    QSlider * mediaProgress;
    //QLabel * x;

    //播放列表相关
    MyPlaylist *playlist;
    QList<QUrl> sources;
    void changeActionState();

    //歌词相关
    MyLrc * lrc;
    QMap<qint64, QString> lrcMap;
    void resolveLrc(const QString &sourceFileName);

    //系统托盘相关
    QSystemTrayIcon * trayIcon;
    void closeEvent(QCloseEvent * event);
};
#endif // MYWIDGET_H
