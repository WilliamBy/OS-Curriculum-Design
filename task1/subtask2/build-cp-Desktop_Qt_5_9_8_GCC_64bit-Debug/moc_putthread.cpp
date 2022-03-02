/****************************************************************************
** Meta object code from reading C++ file 'putthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cp/putthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'putthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PutThread_t {
    QByteArrayData data[6];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PutThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PutThread_t qt_meta_stringdata_PutThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PutThread"
QT_MOC_LITERAL(1, 10, 4), // "rate"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "err"
QT_MOC_LITERAL(4, 20, 8), // "complete"
QT_MOC_LITERAL(5, 29, 9) // "errHandle"

    },
    "PutThread\0rate\0\0err\0complete\0errHandle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PutThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    0,   37,    2, 0x06 /* Public */,
       4,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PutThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PutThread *_t = static_cast<PutThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->err(); break;
        case 2: _t->complete(); break;
        case 3: _t->errHandle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PutThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PutThread::rate)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PutThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PutThread::err)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PutThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PutThread::complete)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject PutThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PutThread.data,
      qt_meta_data_PutThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PutThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PutThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PutThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PutThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PutThread::rate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PutThread::err()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PutThread::complete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
