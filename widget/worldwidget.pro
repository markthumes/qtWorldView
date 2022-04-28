QT          += widgets uiplugin openglwidgets

CONFIG      += plugin
TEMPLATE     = lib
LIBS        += -lGL -lGLEW -lassimp

INCLUDEPATH += htoolkit/file htoolkit/conversions stb

TARGET = $$qtLibraryTarget($$TARGET)

target.path = /home/humes/Qt/Tools/QtCreator/lib/Qt/plugins/designer
INSTALLS += target

HEADERS     = worldwidget.h \
              worldplugin.h \
              mesh.h \
              shader.h \
              cubesphere.h \
              texture.h \
              terrainface.h \
              htoolkit/file/file.h \
              htoolkit/conversions/conversions.h 
SOURCES     = worldwidget.cpp \
              worldplugin.cpp \
              mesh.cpp \
              shader.cpp \
              cubesphere.cpp \
              texture.cpp \
              terrainface.cpp \
              htoolkit/file/file.cpp \
              htoolkit/conversions/conversions.cpp 
