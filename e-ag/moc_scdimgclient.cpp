/****************************************************************************
** Meta object code from reading C++ file 'scdimgclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "scdimgclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scdimgclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SCDImgClient_t {
    QByteArrayData data[26];
    char stringdata0[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SCDImgClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SCDImgClient_t qt_meta_stringdata_SCDImgClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SCDImgClient"
QT_MOC_LITERAL(1, 13, 15), // "notifyConnected"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "notifyMess"
QT_MOC_LITERAL(4, 41, 4), // "host"
QT_MOC_LITERAL(5, 46, 4), // "port"
QT_MOC_LITERAL(6, 51, 16), // "notifyDisconnect"
QT_MOC_LITERAL(7, 68, 7), // "success"
QT_MOC_LITERAL(8, 76, 11), // "notifyError"
QT_MOC_LITERAL(9, 88, 11), // "errorString"
QT_MOC_LITERAL(10, 100, 8), // "finished"
QT_MOC_LITERAL(11, 109, 6), // "errMsg"
QT_MOC_LITERAL(12, 116, 14), // "deleteFinished"
QT_MOC_LITERAL(13, 131, 14), // "uploadFinished"
QT_MOC_LITERAL(14, 146, 16), // "downloadFinished"
QT_MOC_LITERAL(15, 163, 8), // "fileName"
QT_MOC_LITERAL(16, 172, 9), // "rcvBuffer"
QT_MOC_LITERAL(17, 182, 12), // "fileReceived"
QT_MOC_LITERAL(18, 195, 8), // "filePath"
QT_MOC_LITERAL(19, 204, 10), // "fileSaving"
QT_MOC_LITERAL(20, 215, 11), // "onConnected"
QT_MOC_LITERAL(21, 227, 14), // "onDisconnected"
QT_MOC_LITERAL(22, 242, 7), // "onError"
QT_MOC_LITERAL(23, 250, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(24, 279, 11), // "socketError"
QT_MOC_LITERAL(25, 291, 11) // "onReadyRead"

    },
    "SCDImgClient\0notifyConnected\0\0notifyMess\0"
    "host\0port\0notifyDisconnect\0success\0"
    "notifyError\0errorString\0finished\0"
    "errMsg\0deleteFinished\0uploadFinished\0"
    "downloadFinished\0fileName\0rcvBuffer\0"
    "fileReceived\0filePath\0fileSaving\0"
    "onConnected\0onDisconnected\0onError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SCDImgClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   84,    2, 0x06 /* Public */,
       6,    2,   91,    2, 0x06 /* Public */,
       8,    1,   96,    2, 0x06 /* Public */,
      10,    2,   99,    2, 0x06 /* Public */,
      12,    2,  104,    2, 0x06 /* Public */,
      13,    2,  109,    2, 0x06 /* Public */,
      14,    2,  114,    2, 0x06 /* Public */,
      14,    4,  119,    2, 0x06 /* Public */,
      17,    1,  128,    2, 0x06 /* Public */,
      19,    1,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  134,    2, 0x0a /* Public */,
      21,    0,  135,    2, 0x0a /* Public */,
      22,    1,  136,    2, 0x0a /* Public */,
      25,    0,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::UShort,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,    3,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QByteArray, QMetaType::QString,    7,   15,   16,   11,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   18,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,

       0        // eod
};

void SCDImgClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SCDImgClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->notifyConnected((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 1: _t->notifyDisconnect((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->notifyError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->finished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->deleteFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->uploadFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->downloadFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->downloadFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< const QByteArray(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 8: _t->fileReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->fileSaving((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onDisconnected(); break;
        case 12: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SCDImgClient::*)(QString , QString , quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::notifyConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::notifyDisconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::notifyError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::finished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::deleteFinished)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::uploadFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::downloadFinished)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(bool , QString , const QByteArray & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::downloadFinished)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::fileReceived)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SCDImgClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SCDImgClient::fileSaving)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SCDImgClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpSocket::staticMetaObject>(),
    qt_meta_stringdata_SCDImgClient.data,
    qt_meta_data_SCDImgClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SCDImgClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SCDImgClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SCDImgClient.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int SCDImgClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SCDImgClient::notifyConnected(QString _t1, QString _t2, quint16 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SCDImgClient::notifyDisconnect(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SCDImgClient::notifyError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SCDImgClient::finished(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SCDImgClient::deleteFinished(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SCDImgClient::uploadFinished(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SCDImgClient::downloadFinished(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SCDImgClient::downloadFinished(bool _t1, QString _t2, const QByteArray & _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SCDImgClient::fileReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SCDImgClient::fileSaving(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
