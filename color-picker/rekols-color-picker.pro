#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T16:13:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rekols-color-picker
TEMPLATE = app

RESOURCES += rekols-color-picker.qrc

SOURCES += main.cpp\
        mainwindow.cpp \
    colorview.cpp \
    pickerwindow.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    colorview.h \
    pickerwindow.h \
    utils.h
