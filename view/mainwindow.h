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
#include "view/game.h"
#include "view/boardwidget.h"
#include "view/cubewidget.h"

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

private:

    Menu* _menu;
    Game* _game;

};

#endif // MAINWINDOW_H
