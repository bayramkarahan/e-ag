/****************************************************************************
** Meta object code from reading C++ file 'pc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../pc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Pc_t {
    QByteArrayData data[86];
    char stringdata0[1050];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Pc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Pc_t qt_meta_stringdata_Pc = {
    {
QT_MOC_LITERAL(0, 0, 2), // "Pc"
QT_MOC_LITERAL(1, 3, 13), // "pcClickSignal"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "mac"
QT_MOC_LITERAL(4, 22, 13), // "pcListeSignal"
QT_MOC_LITERAL(5, 36, 18), // "pcListeStateSignal"
QT_MOC_LITERAL(6, 55, 22), // "pcTcpPortControlSignal"
QT_MOC_LITERAL(7, 78, 2), // "ip"
QT_MOC_LITERAL(8, 81, 22), // "pcSshPortControlSignal"
QT_MOC_LITERAL(9, 104, 22), // "pcVncPortControlSignal"
QT_MOC_LITERAL(10, 127, 22), // "pcFtpPortControlSignal"
QT_MOC_LITERAL(11, 150, 25), // "pcKilitStateControlSignal"
QT_MOC_LITERAL(12, 176, 11), // "_kilitstate"
QT_MOC_LITERAL(13, 188, 35), // "pcKilitTransparanStateControl..."
QT_MOC_LITERAL(14, 224, 21), // "_transparankilitstate"
QT_MOC_LITERAL(15, 246, 24), // "pcIconStateControlSignal"
QT_MOC_LITERAL(16, 271, 10), // "_iconstate"
QT_MOC_LITERAL(17, 282, 12), // "pcMenuSignal"
QT_MOC_LITERAL(18, 295, 5), // "_slot"
QT_MOC_LITERAL(19, 301, 6), // "setMac"
QT_MOC_LITERAL(20, 308, 4), // "_mac"
QT_MOC_LITERAL(21, 313, 2), // "_w"
QT_MOC_LITERAL(22, 316, 2), // "_h"
QT_MOC_LITERAL(23, 319, 5), // "_font"
QT_MOC_LITERAL(24, 325, 7), // "setSize"
QT_MOC_LITERAL(25, 333, 10), // "setCaption"
QT_MOC_LITERAL(26, 344, 3), // "cap"
QT_MOC_LITERAL(27, 348, 10), // "setDisplay"
QT_MOC_LITERAL(28, 359, 4), // "_dis"
QT_MOC_LITERAL(29, 364, 7), // "setUser"
QT_MOC_LITERAL(30, 372, 3), // "_os"
QT_MOC_LITERAL(31, 376, 5), // "setOs"
QT_MOC_LITERAL(32, 382, 21), // "vncstatelabel_clicked"
QT_MOC_LITERAL(33, 404, 10), // "novncadres"
QT_MOC_LITERAL(34, 415, 20), // "setKilitControlState"
QT_MOC_LITERAL(35, 436, 5), // "state"
QT_MOC_LITERAL(36, 442, 30), // "setKilitTransparanControlState"
QT_MOC_LITERAL(37, 473, 19), // "setIconControlState"
QT_MOC_LITERAL(38, 493, 9), // "setAcount"
QT_MOC_LITERAL(39, 503, 8), // "username"
QT_MOC_LITERAL(40, 512, 8), // "password"
QT_MOC_LITERAL(41, 521, 13), // "setTcpConnect"
QT_MOC_LITERAL(42, 535, 10), // "setPcState"
QT_MOC_LITERAL(43, 546, 13), // "setSshConnect"
QT_MOC_LITERAL(44, 560, 13), // "setVncConnect"
QT_MOC_LITERAL(45, 574, 13), // "setFtpConnect"
QT_MOC_LITERAL(46, 588, 14), // "slotMouseClick"
QT_MOC_LITERAL(47, 603, 20), // "slotMouseDoubleClick"
QT_MOC_LITERAL(48, 624, 12), // "slotSelectPc"
QT_MOC_LITERAL(49, 637, 14), // "slotUnselectPc"
QT_MOC_LITERAL(50, 652, 6), // "pcMenu"
QT_MOC_LITERAL(51, 659, 20), // "timerPortControlSlot"
QT_MOC_LITERAL(52, 680, 26), // "timerPortControlOnlineSlot"
QT_MOC_LITERAL(53, 707, 10), // "listRemove"
QT_MOC_LITERAL(54, 718, 4), // "list"
QT_MOC_LITERAL(55, 723, 4), // "data"
QT_MOC_LITERAL(56, 728, 10), // "fileToList"
QT_MOC_LITERAL(57, 739, 8), // "filename"
QT_MOC_LITERAL(58, 748, 10), // "listToFile"
QT_MOC_LITERAL(59, 759, 11), // "listGetLine"
QT_MOC_LITERAL(60, 771, 11), // "listReplace"
QT_MOC_LITERAL(61, 783, 7), // "oldData"
QT_MOC_LITERAL(62, 791, 7), // "newData"
QT_MOC_LITERAL(63, 799, 5), // "index"
QT_MOC_LITERAL(64, 805, 15), // "getIpPortStatus"
QT_MOC_LITERAL(65, 821, 3), // "ip_"
QT_MOC_LITERAL(66, 825, 4), // "port"
QT_MOC_LITERAL(67, 830, 8), // "slotVnc0"
QT_MOC_LITERAL(68, 839, 8), // "slotVnc1"
QT_MOC_LITERAL(69, 848, 8), // "slotVnc2"
QT_MOC_LITERAL(70, 857, 11), // "slotVncFlip"
QT_MOC_LITERAL(71, 869, 15), // "slotVncFlipStop"
QT_MOC_LITERAL(72, 885, 7), // "slotRdp"
QT_MOC_LITERAL(73, 893, 7), // "slotFtp"
QT_MOC_LITERAL(74, 901, 9), // "slotKilit"
QT_MOC_LITERAL(75, 911, 11), // "slotKilitAc"
QT_MOC_LITERAL(76, 923, 9), // "slotLogin"
QT_MOC_LITERAL(77, 933, 10), // "slotLogout"
QT_MOC_LITERAL(78, 944, 10), // "slotReboot"
QT_MOC_LITERAL(79, 955, 9), // "slotKapat"
QT_MOC_LITERAL(80, 965, 9), // "slotMesaj"
QT_MOC_LITERAL(81, 975, 11), // "slotCommand"
QT_MOC_LITERAL(82, 987, 13), // "slotEkranIzle"
QT_MOC_LITERAL(83, 1001, 19), // "slotEkranIzleDurdur"
QT_MOC_LITERAL(84, 1021, 17), // "slotServisControl"
QT_MOC_LITERAL(85, 1039, 10) // "slotPcAyar"

    },
    "Pc\0pcClickSignal\0\0mac\0pcListeSignal\0"
    "pcListeStateSignal\0pcTcpPortControlSignal\0"
    "ip\0pcSshPortControlSignal\0"
    "pcVncPortControlSignal\0pcFtpPortControlSignal\0"
    "pcKilitStateControlSignal\0_kilitstate\0"
    "pcKilitTransparanStateControlSignal\0"
    "_transparankilitstate\0pcIconStateControlSignal\0"
    "_iconstate\0pcMenuSignal\0_slot\0setMac\0"
    "_mac\0_w\0_h\0_font\0setSize\0setCaption\0"
    "cap\0setDisplay\0_dis\0setUser\0_os\0setOs\0"
    "vncstatelabel_clicked\0novncadres\0"
    "setKilitControlState\0state\0"
    "setKilitTransparanControlState\0"
    "setIconControlState\0setAcount\0username\0"
    "password\0setTcpConnect\0setPcState\0"
    "setSshConnect\0setVncConnect\0setFtpConnect\0"
    "slotMouseClick\0slotMouseDoubleClick\0"
    "slotSelectPc\0slotUnselectPc\0pcMenu\0"
    "timerPortControlSlot\0timerPortControlOnlineSlot\0"
    "listRemove\0list\0data\0fileToList\0"
    "filename\0listToFile\0listGetLine\0"
    "listReplace\0oldData\0newData\0index\0"
    "getIpPortStatus\0ip_\0port\0slotVnc0\0"
    "slotVnc1\0slotVnc2\0slotVncFlip\0"
    "slotVncFlipStop\0slotRdp\0slotFtp\0"
    "slotKilit\0slotKilitAc\0slotLogin\0"
    "slotLogout\0slotReboot\0slotKapat\0"
    "slotMesaj\0slotCommand\0slotEkranIzle\0"
    "slotEkranIzleDurdur\0slotServisControl\0"
    "slotPcAyar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Pc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      59,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  309,    2, 0x06 /* Public */,
       4,    0,  312,    2, 0x06 /* Public */,
       5,    0,  313,    2, 0x06 /* Public */,
       6,    2,  314,    2, 0x06 /* Public */,
       8,    2,  319,    2, 0x06 /* Public */,
       9,    2,  324,    2, 0x06 /* Public */,
      10,    2,  329,    2, 0x06 /* Public */,
      11,    3,  334,    2, 0x06 /* Public */,
      13,    3,  341,    2, 0x06 /* Public */,
      15,    3,  348,    2, 0x06 /* Public */,
      17,    3,  355,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    4,  362,    2, 0x0a /* Public */,
      24,    3,  371,    2, 0x0a /* Public */,
      25,    1,  378,    2, 0x0a /* Public */,
      27,    1,  381,    2, 0x0a /* Public */,
      29,    1,  384,    2, 0x0a /* Public */,
      31,    1,  387,    2, 0x0a /* Public */,
      32,    1,  390,    2, 0x0a /* Public */,
      34,    1,  393,    2, 0x0a /* Public */,
      36,    1,  396,    2, 0x0a /* Public */,
      37,    1,  399,    2, 0x0a /* Public */,
      38,    2,  402,    2, 0x0a /* Public */,
      41,    1,  407,    2, 0x0a /* Public */,
      42,    1,  410,    2, 0x0a /* Public */,
      43,    1,  413,    2, 0x0a /* Public */,
      44,    1,  416,    2, 0x0a /* Public */,
      45,    1,  419,    2, 0x0a /* Public */,
      46,    0,  422,    2, 0x0a /* Public */,
      47,    0,  423,    2, 0x0a /* Public */,
      48,    0,  424,    2, 0x0a /* Public */,
      49,    0,  425,    2, 0x0a /* Public */,
      50,    0,  426,    2, 0x08 /* Private */,
      51,    0,  427,    2, 0x08 /* Private */,
      52,    0,  428,    2, 0x08 /* Private */,
      53,    2,  429,    2, 0x08 /* Private */,
      56,    1,  434,    2, 0x08 /* Private */,
      58,    2,  437,    2, 0x08 /* Private */,
      59,    2,  442,    2, 0x08 /* Private */,
      60,    5,  447,    2, 0x08 /* Private */,
      64,    2,  458,    2, 0x08 /* Private */,
      67,    0,  463,    2, 0x08 /* Private */,
      68,    0,  464,    2, 0x08 /* Private */,
      69,    0,  465,    2, 0x08 /* Private */,
      70,    0,  466,    2, 0x08 /* Private */,
      71,    0,  467,    2, 0x08 /* Private */,
      72,    0,  468,    2, 0x08 /* Private */,
      73,    0,  469,    2, 0x08 /* Private */,
      74,    0,  470,    2, 0x08 /* Private */,
      75,    0,  471,    2, 0x08 /* Private */,
      76,    0,  472,    2, 0x08 /* Private */,
      77,    0,  473,    2, 0x08 /* Private */,
      78,    0,  474,    2, 0x08 /* Private */,
      79,    0,  475,    2, 0x08 /* Private */,
      80,    0,  476,    2, 0x08 /* Private */,
      81,    0,  477,    2, 0x08 /* Private */,
      82,    0,  478,    2, 0x08 /* Private */,
      83,    0,  479,    2, 0x08 /* Private */,
      84,    0,  480,    2, 0x08 /* Private */,
      85,    0,  481,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    7,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    7,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    7,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    7,   18,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::QString,   20,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   21,   22,   23,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   39,   40,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString,   54,   55,
    QMetaType::QStringList, QMetaType::QString,   57,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,   54,   57,
    QMetaType::QString, QMetaType::QStringList, QMetaType::QString,   54,   55,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,   54,   61,   62,   63,   20,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   65,   66,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Pc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Pc *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pcClickSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pcListeSignal(); break;
        case 2: _t->pcListeStateSignal(); break;
        case 3: _t->pcTcpPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->pcSshPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->pcVncPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->pcFtpPortControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->pcKilitStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 8: _t->pcKilitTransparanStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 9: _t->pcIconStateControlSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 10: _t->pcMenuSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->setMac((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 12: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: _t->setCaption((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->setDisplay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->setUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->setOs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->vncstatelabel_clicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->setKilitControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setKilitTransparanControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->setIconControlState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setAcount((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: _t->setTcpConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->setPcState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setSshConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->setVncConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->setFtpConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->slotMouseClick(); break;
        case 28: _t->slotMouseDoubleClick(); break;
        case 29: _t->slotSelectPc(); break;
        case 30: _t->slotUnselectPc(); break;
        case 31: _t->pcMenu(); break;
        case 32: _t->timerPortControlSlot(); break;
        case 33: _t->timerPortControlOnlineSlot(); break;
        case 34: { QStringList _r = _t->listRemove((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 35: { QStringList _r = _t->fileToList((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->listToFile((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 37: { QString _r = _t->listGetLine((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 38: { QStringList _r = _t->listReplace((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 39: { QString _r = _t->getIpPortStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->slotVnc0(); break;
        case 41: _t->slotVnc1(); break;
        case 42: _t->slotVnc2(); break;
        case 43: _t->slotVncFlip(); break;
        case 44: _t->slotVncFlipStop(); break;
        case 45: _t->slotRdp(); break;
        case 46: _t->slotFtp(); break;
        case 47: _t->slotKilit(); break;
        case 48: _t->slotKilitAc(); break;
        case 49: _t->slotLogin(); break;
        case 50: _t->slotLogout(); break;
        case 51: _t->slotReboot(); break;
        case 52: _t->slotKapat(); break;
        case 53: _t->slotMesaj(); break;
        case 54: _t->slotCommand(); break;
        case 55: _t->slotEkranIzle(); break;
        case 56: _t->slotEkranIzleDurdur(); break;
        case 57: _t->slotServisControl(); break;
        case 58: _t->slotPcAyar(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Pc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcClickSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Pc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcListeSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Pc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcListeStateSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcTcpPortControlSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcSshPortControlSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcVncPortControlSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcFtpPortControlSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcKilitStateControlSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcKilitTransparanStateControlSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcIconStateControlSignal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Pc::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Pc::pcMenuSignal)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Pc::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Pc.data,
    qt_meta_data_Pc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Pc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Pc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Pc.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Pc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 59)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 59;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 59)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 59;
    }
    return _id;
}

// SIGNAL 0
void Pc::pcClickSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Pc::pcListeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Pc::pcListeStateSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Pc::pcTcpPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Pc::pcSshPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Pc::pcVncPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Pc::pcFtpPortControlSignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Pc::pcKilitStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Pc::pcKilitTransparanStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Pc::pcIconStateControlSignal(QString _t1, QString _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Pc::pcMenuSignal(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
