/****************************************************************************
** Meta object code from reading C++ file 'worldplugin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "worldplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worldplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WorldPlugin_t {
    const uint offsetsAndSize[2];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_WorldPlugin_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_WorldPlugin_t qt_meta_stringdata_WorldPlugin = {
    {
QT_MOC_LITERAL(0, 11) // "WorldPlugin"

    },
    "WorldPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorldPlugin[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void WorldPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject WorldPlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WorldPlugin.offsetsAndSize,
    qt_meta_data_WorldPlugin,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_WorldPlugin_t
, QtPrivate::TypeAndForceComplete<WorldPlugin, std::true_type>



>,
    nullptr
} };


const QMetaObject *WorldPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorldPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WorldPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QDesignerCustomWidgetInterface"))
        return static_cast< QDesignerCustomWidgetInterface*>(this);
    if (!strcmp(_clname, "org.qt-project.QDesignerCustomWidgetInterface"))
        return static_cast< QDesignerCustomWidgetInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int WorldPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_WorldPlugin[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x30,  'o',  'r',  'g',  '.',  'q', 
    't',  '-',  'p',  'r',  'o',  'j',  'e',  'c', 
    't',  '.',  'Q',  't',  '.',  'Q',  'D',  'e', 
    's',  'i',  'g',  'n',  'e',  'r',  'C',  'u', 
    's',  't',  'o',  'm',  'W',  'i',  'd',  'g', 
    'e',  't',  'I',  'n',  't',  'e',  'r',  'f', 
    'a',  'c',  'e', 
    // "className"
    0x03,  0x6b,  'W',  'o',  'r',  'l',  'd',  'P', 
    'l',  'u',  'g',  'i',  'n', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(WorldPlugin, WorldPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
