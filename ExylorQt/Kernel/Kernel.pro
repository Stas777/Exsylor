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
    ScrDocExpImp.cpp \
    Proof.cpp \
    Induct.cpp \
    Gener.cpp \
    Bv.cpp \
    Bm.cpp \
    Archive.cpp \
    Model.cpp \
    data.cpp \
    knowledge.cpp \
    datatemplate.cpp \
    modelmanager.cpp

HEADERS += \
    ScrDoc.h \
    BaseBool.h \
    CoverDoc.h \
    Archive.h \
    resouces.h \
    Model.h \
    data.h \
    knowledge.h \
    datatemplate.h \
    modelmanager.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
