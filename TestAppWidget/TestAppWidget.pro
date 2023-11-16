QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 moc

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ZoomLib/include/Zoom_global.h \
    ZoomLib/include/zoom.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ZoomLib/release/ -lZoom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ZoomLib/debug/ -lZoom
else:unix: LIBS += -L$$PWD/ZoomLib/ -lZoom

INCLUDEPATH += $$PWD/ZoomLib/include
DEPENDPATH += $$PWD/ZoomLib/include
DEFINES += ZOOM_LIBRARY
