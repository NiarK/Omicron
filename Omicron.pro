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
    view/game.cpp \
    view/boardwidget.cpp \
    controller/GameController.cpp \
    view/cubewidget.cpp

HEADERS  += \
    model/hypercube.h \
    view/mainwindow.h \
    view/menu.h \
    view/game.h \
    view/boardwidget.h \
    controller/GameController.h \
    view/cubewidget.h
