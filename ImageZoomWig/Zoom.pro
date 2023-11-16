TEMPLATE = lib
DEFINES += ZOOM_LIBRARY
CONFIG += qt warn_on release shared
QT += gui widgets

HEADERS += Zoom.h \
           zoom_global.h
SOURCES += Zoom.cpp

TARGET = Zoom
DESTDIR = output/path

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    Zoom.ui
