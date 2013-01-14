#-------------------------------------------------
#
# Project created by QtCreator 2012-12-30T18:48:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Omicron
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    model/hypercube.cpp \
    view/mainwindow.cpp \
    view/menu.cpp \
    view/boardwidget.cpp \
    view/cubewidget.cpp \
    controller/gamecontroller.cpp \
    controller/boardcontroller.cpp \
    controller/cubecontroller.cpp \
    view/gamewidget.cpp \
    controller/tesseractcontroller.cpp \
    view/tesseractwidget.cpp

HEADERS  += \
    model/hypercube.h \
    view/mainwindow.h \
    view/menu.h \
    view/boardwidget.h \
    view/cubewidget.h \
    controller/gamecontroller.h \
    controller/boardcontroller.h \
    controller/cubecontroller.h \
    view/field.h \
    view/gamewidget.h \
    controller/tesseractcontroller.h \
    view/tesseractwidget.h