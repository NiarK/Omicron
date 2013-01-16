#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// --- Include Qt --- //
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <QVBoxLayout>

// --- Include std --- //
#include <vector>

// --- Include Omicron --- //
#include "view/field.h"
#include "view/menu.h"
#include "view/gamewidget.h"
#include "view/boardwidget.h"
#include "view/cubewidget.h"
#include "view/tesseractwidget.h"

// --- Temporaire --- //
#include "controller/boardcontroller.h"
#include "controller/cubecontroller.h"
#include "controller/tesseractcontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void initializeMenu();
    void initializeGame(Field field);
    void initializeGame();
    void lanchBenchmark(Field f);

protected:

private:

    Menu* _menu;
    GameWidget* _game;

    Field _field;

};

#endif // MAINWINDOW_H
