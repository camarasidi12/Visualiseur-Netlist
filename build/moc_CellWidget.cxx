/****************************************************************************
** Meta object code from reading C++ file 'CellWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CellWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CellWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Netlist__CellWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      30,   20,   20,   20, 0x0a,
      40,   20,   20,   20, 0x0a,
      47,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Netlist__CellWidget[] = {
    "Netlist::CellWidget\0\0goLeft()\0goRight()\0"
    "goUp()\0goDown()\0"
};

void Netlist::CellWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CellWidget *_t = static_cast<CellWidget *>(_o);
        switch (_id) {
        case 0: _t->goLeft(); break;
        case 1: _t->goRight(); break;
        case 2: _t->goUp(); break;
        case 3: _t->goDown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Netlist::CellWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Netlist::CellWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Netlist__CellWidget,
      qt_meta_data_Netlist__CellWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Netlist::CellWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Netlist::CellWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Netlist::CellWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Netlist__CellWidget))
        return static_cast<void*>(const_cast< CellWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Netlist::CellWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
