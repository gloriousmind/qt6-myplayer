/****************************************************************************
** Meta object code from reading C++ file 'mywidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myPlayer/mywidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMyWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMyWidgetENDCLASS = QtMocHelpers::stringData(
    "MyWidget",
    "updateTime",
    "",
    "time",
    "set_play_or_pause",
    "setStop",
    "skipBackward",
    "skipForward",
    "openFile",
    "setPlaylistShown",
    "setLrcShown",
    "mywidget_setVolume",
    "playbackStateChanged",
    "QMediaPlayer::PlaybackState",
    "newState",
    "playback_mediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "resolve_mediaStatusChanged",
    "showError",
    "QMediaPlayer::Error",
    "error",
    "errorString",
    "playback_sourceChanged",
    "media",
    "resolve_extractmetaData",
    "tableDoubleClicked",
    "row",
    "clearSources",
    "trayIconActivated",
    "QSystemTrayIcon::ActivationReason",
    "activationReason"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMyWidgetENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[9];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[18];
    char stringdata5[8];
    char stringdata6[13];
    char stringdata7[12];
    char stringdata8[9];
    char stringdata9[17];
    char stringdata10[12];
    char stringdata11[19];
    char stringdata12[21];
    char stringdata13[28];
    char stringdata14[9];
    char stringdata15[28];
    char stringdata16[26];
    char stringdata17[7];
    char stringdata18[27];
    char stringdata19[10];
    char stringdata20[20];
    char stringdata21[6];
    char stringdata22[12];
    char stringdata23[23];
    char stringdata24[6];
    char stringdata25[24];
    char stringdata26[19];
    char stringdata27[4];
    char stringdata28[13];
    char stringdata29[18];
    char stringdata30[34];
    char stringdata31[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMyWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMyWidgetENDCLASS_t qt_meta_stringdata_CLASSMyWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "MyWidget"
        QT_MOC_LITERAL(9, 10),  // "updateTime"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 4),  // "time"
        QT_MOC_LITERAL(26, 17),  // "set_play_or_pause"
        QT_MOC_LITERAL(44, 7),  // "setStop"
        QT_MOC_LITERAL(52, 12),  // "skipBackward"
        QT_MOC_LITERAL(65, 11),  // "skipForward"
        QT_MOC_LITERAL(77, 8),  // "openFile"
        QT_MOC_LITERAL(86, 16),  // "setPlaylistShown"
        QT_MOC_LITERAL(103, 11),  // "setLrcShown"
        QT_MOC_LITERAL(115, 18),  // "mywidget_setVolume"
        QT_MOC_LITERAL(134, 20),  // "playbackStateChanged"
        QT_MOC_LITERAL(155, 27),  // "QMediaPlayer::PlaybackState"
        QT_MOC_LITERAL(183, 8),  // "newState"
        QT_MOC_LITERAL(192, 27),  // "playback_mediaStatusChanged"
        QT_MOC_LITERAL(220, 25),  // "QMediaPlayer::MediaStatus"
        QT_MOC_LITERAL(246, 6),  // "status"
        QT_MOC_LITERAL(253, 26),  // "resolve_mediaStatusChanged"
        QT_MOC_LITERAL(280, 9),  // "showError"
        QT_MOC_LITERAL(290, 19),  // "QMediaPlayer::Error"
        QT_MOC_LITERAL(310, 5),  // "error"
        QT_MOC_LITERAL(316, 11),  // "errorString"
        QT_MOC_LITERAL(328, 22),  // "playback_sourceChanged"
        QT_MOC_LITERAL(351, 5),  // "media"
        QT_MOC_LITERAL(357, 23),  // "resolve_extractmetaData"
        QT_MOC_LITERAL(381, 18),  // "tableDoubleClicked"
        QT_MOC_LITERAL(400, 3),  // "row"
        QT_MOC_LITERAL(404, 12),  // "clearSources"
        QT_MOC_LITERAL(417, 17),  // "trayIconActivated"
        QT_MOC_LITERAL(435, 33),  // "QSystemTrayIcon::ActivationRe..."
        QT_MOC_LITERAL(469, 16)   // "activationReason"
    },
    "MyWidget",
    "updateTime",
    "",
    "time",
    "set_play_or_pause",
    "setStop",
    "skipBackward",
    "skipForward",
    "openFile",
    "setPlaylistShown",
    "setLrcShown",
    "mywidget_setVolume",
    "playbackStateChanged",
    "QMediaPlayer::PlaybackState",
    "newState",
    "playback_mediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "resolve_mediaStatusChanged",
    "showError",
    "QMediaPlayer::Error",
    "error",
    "errorString",
    "playback_sourceChanged",
    "media",
    "resolve_extractmetaData",
    "tableDoubleClicked",
    "row",
    "clearSources",
    "trayIconActivated",
    "QSystemTrayIcon::ActivationReason",
    "activationReason"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMyWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  122,    2, 0x08,    1 /* Private */,
       4,    0,  125,    2, 0x08,    3 /* Private */,
       5,    0,  126,    2, 0x08,    4 /* Private */,
       6,    0,  127,    2, 0x08,    5 /* Private */,
       7,    0,  128,    2, 0x08,    6 /* Private */,
       8,    0,  129,    2, 0x08,    7 /* Private */,
       9,    0,  130,    2, 0x08,    8 /* Private */,
      10,    0,  131,    2, 0x08,    9 /* Private */,
      11,    1,  132,    2, 0x08,   10 /* Private */,
      12,    1,  135,    2, 0x08,   12 /* Private */,
      15,    1,  138,    2, 0x08,   14 /* Private */,
      18,    1,  141,    2, 0x08,   16 /* Private */,
      19,    2,  144,    2, 0x08,   18 /* Private */,
      23,    1,  149,    2, 0x08,   21 /* Private */,
      25,    0,  152,    2, 0x08,   23 /* Private */,
      26,    1,  153,    2, 0x08,   24 /* Private */,
      28,    0,  156,    2, 0x08,   26 /* Private */,
      29,    1,  157,    2, 0x08,   27 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 20, QMetaType::QString,   21,   22,
    QMetaType::Void, QMetaType::QUrl,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,

       0        // eod
};

Q_CONSTINIT const QMetaObject MyWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMyWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMyWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMyWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MyWidget, std::true_type>,
        // method 'updateTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'set_play_or_pause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'skipBackward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'skipForward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setPlaylistShown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLrcShown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mywidget_setVolume'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'playbackStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::PlaybackState, std::false_type>,
        // method 'playback_mediaStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'resolve_mediaStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'showError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::Error, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'playback_sourceChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>,
        // method 'resolve_extractmetaData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tableDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clearSources'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'trayIconActivated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSystemTrayIcon::ActivationReason, std::false_type>
    >,
    nullptr
} };

void MyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateTime((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 1: _t->set_play_or_pause(); break;
        case 2: _t->setStop(); break;
        case 3: _t->skipBackward(); break;
        case 4: _t->skipForward(); break;
        case 5: _t->openFile(); break;
        case 6: _t->setPlaylistShown(); break;
        case 7: _t->setLrcShown(); break;
        case 8: _t->mywidget_setVolume((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->playbackStateChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::PlaybackState>>(_a[1]))); break;
        case 10: _t->playback_mediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 11: _t->resolve_mediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 12: _t->showError((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::Error>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->playback_sourceChanged((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 14: _t->resolve_extractmetaData(); break;
        case 15: _t->tableDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->clearSources(); break;
        case 17: _t->trayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMyWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
