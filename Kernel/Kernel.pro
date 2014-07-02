#-------------------------------------------------
#
# Project created by QtCreator 2014-07-02T11:25:43
#
#-------------------------------------------------

QT       -= gui

TARGET = Kernel
TEMPLATE = lib
CONFIG += staticlib

SOURCES += kernel.cpp

HEADERS += kernel.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
