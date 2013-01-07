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
#include "view/menu.h"
#include "view/game.h"
#include "view/boardwidget.h"
#include "view/cubewidget.h"

enum class Map
{
    BOARD,
    DONUT,
    CUBE,
    TESSERACT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void initializeMenu();
    void initializeGameBoard();

private:
    void initializeGame(Map map);

    Menu* _menu;
    Game* _game;

};

#endif // MAINWINDOW_H
