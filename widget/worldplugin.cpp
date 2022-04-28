#include <QtPlugin>

#include "worldwidget.h"
#include "worldplugin.h"

WorldPlugin::WorldPlugin(QObject *parent) : QObject(parent), initialized(false){
}

void WorldPlugin::initialize(QDesignerFormEditorInterface * /* core */){
    if (initialized)
        return;

    initialized = true;
}
bool WorldPlugin::isInitialized() const{
    return initialized;
}
QWidget *WorldPlugin::createWidget(QWidget *parent){
    return new WorldWidget(parent);
}
QString WorldPlugin::name() const{
    return "WorldWidget";
}
QString WorldPlugin::group() const{
    return "QTUI Widgets";
}
QIcon WorldPlugin::icon() const{
    return QIcon();
}
QString WorldPlugin::toolTip() const{
    return "";
}
QString WorldPlugin::whatsThis() const{
    return "";
}
bool WorldPlugin::isContainer() const{
    return false;
}
QString WorldPlugin::domXml() const{
    return "<ui language=\"c++\">\n"
           " <widget class=\"WorldWidget\" name=\"worldwidget\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>WorldWidget</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>Filler.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}
QString WorldPlugin::includeFile() const{
    return "worldwidget.h";
}
