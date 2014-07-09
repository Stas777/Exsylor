#-------------------------------------------------
#
# Project created by QtCreator 2014-07-02T11:25:43
#
#-------------------------------------------------

QT       -= gui

TARGET = Kernel
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ScrObj.cpp \
    ScrDocSM.cpp \
    ScrDocRg.cpp \
    ScrDocEx.cpp \
    ScrDocExpImp.cpp \
    ScrDoc.cpp \
    Proof.cpp \
    Induct.cpp \
    Gener.cpp \
    Bv.cpp \
    Bm.cpp \
    Archive.cpp \
    ScrInit.cpp

HEADERS += \
    ScrDoc.h \
    BaseBool.h \
    CoverDoc.h \
    Archive.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}