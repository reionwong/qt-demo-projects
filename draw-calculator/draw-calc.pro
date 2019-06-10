#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T18:43:56
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draw-calc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    expressionlist.cpp \
    buttonlist.cpp \
    listview.cpp \
    listitem.cpp \
    utils.cpp \
    titlebar.cpp

HEADERS += \
        mainwindow.h \
    expressionlist.h \
    buttonlist.h \
    listitem.h \
    listview.h \
    utils.h \
    titlebar.h

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/icon.svg

