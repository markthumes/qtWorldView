QT          += widgets uiplugin openglwidgets

CONFIG      += plugin
TEMPLATE     = lib
LIBS        += -lGL -lGLEW -lassimp

TARGET = $$qtLibraryTarget($$TARGET)

target.path = /home/humes/Qt/Tools/QtCreator/lib/Qt/plugins/designer
INSTALLS += target

HEADERS     = worldwidget.h \
              worldplugin.h
SOURCES     = worldwidget.cpp \
              worldplugin.cpp
