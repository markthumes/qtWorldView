QT          += widgets uiplugin openglwidgets

CONFIG      += plugin
TEMPLATE     = lib
LIBS        += -lGL -lGLEW -lassimp

QMAKE_CXXFLAGS += -ggdb -O0
QMAKE_CXXFLAGS_RELEASE -= -O2

INCLUDEPATH += 

TARGET = $$qtLibraryTarget($$TARGET)

target.path = /home/humes/Qt/Tools/QtCreator/lib/Qt/plugins/designer
INSTALLS += target

HEADERS     = worldwidget.h \
              worldplugin.h \
              sphere.h \
              mesh.h \
              camera.h \
              light.h \
              conversions.h

SOURCES     = worldwidget.cpp \
              worldplugin.cpp \
              sphere.cpp \
              mesh.cpp \
              camera.cpp \
              light.cpp \
              conversions.cpp
