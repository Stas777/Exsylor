#-------------------------------------------------
#
# Project created by QtCreator 2014-07-02T11:27:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutexylor.cpp \
    expertwidget.cpp \
    newfile.cpp \
    knowledgedialogue.cpp \
    datadialogue.cpp \
    iftab.cpp \
    thentab.cpp \
    treecheckboxwidget.cpp

HEADERS  += \
    aboutexylor.h \
    mainwindow.h \
    expertwidget.h \
    newfile.h \
    knowledgedialogue.h \
    datadialogue.h \
    iftab.h \
    thentab.h \
    treecheckboxwidget.h

FORMS    += mainwindow.ui \
    aboutexylor.ui \
    expertwidget.ui \
    newfile.ui \
    knowledgedialogue.ui \
    datadialogue.ui \
    iftab.ui \
    thentab.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/release/ -lKernel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/debug/ -lKernel
else:unix: LIBS += -L$$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/ -lKernel

INCLUDEPATH += $$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug
DEPENDPATH += $$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/release/Kernel.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/debug/Kernel.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-Kernel-Desktop_Qt_5_1_1_GCC_32bit-Debug/libKernel.a

RESOURCES += \
    resources/Images.qrc
