#-------------------------------------------------
#
# Project created by QtCreator 2018-10-31T13:34:11
#
#-------------------------------------------------

QT       += core gui svg concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = PinYinTextObject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    chinesecharacterobject.cpp \
    svgobject.cpp \
    UIDialog/phoneticdialog.cpp \
    UIDialog/phoneticpreview.cpp \
    UIDialog/phoneticedit.cpp \
    UIDialog/phonetictitle.cpp \
    UIDialog/PhoneticEdit/chinesecharacterobject.cpp \
    UIDialog/PhoneticEdit/phonetictextedit.cpp

HEADERS += \
        widget.h \
    chinesecharacterobject.h \
    svgobject.h \
    UIDialog/phoneticdialog.h \
    UIDialog/phoneticpreview.h \
    UIDialog/phoneticedit.h \
    UIDialog/phonetictitle.h \
    UIDialog/PhoneticEdit/chinesecharacterobject.h \
    UIDialog/PhoneticEdit/phonetictextedit.h

FORMS += \
        widget.ui

RESOURCES += \
    resources.qrc
