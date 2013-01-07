#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _menu(0),
      _game(0)
{

    this->initializeMenu();

    this->setGeometry(100,100,800,600);

}

MainWindow::~MainWindow()
{
    delete _menu;
    delete _game;
}


void MainWindow::initializeMenu()
{

    if(!_menu)
    {
        _menu = new Menu(this);
    }

    if(_game)
    {
        delete _game;
        _game = 0;
    }

    this->setCentralWidget(_menu);

    QObject::connect(_menu, SIGNAL(boardClicked()), this, SLOT(initializeGameBoard()));
}

void MainWindow::initializeGameBoard()
{
    initializeGame(Map::BOARD);
}

void MainWindow::initializeGame(Map map)
{
    if(!_game)
    {
        _game = new BoardWidget(8,8,this);
        //_game = new CubeWidget(this);
    }

    if(_menu)
    {
        delete _menu;
        _menu = 0;
    }

    this->setCentralWidget(_game);

    QObject::connect(_game, SIGNAL(returnClicked()), this, SLOT(initializeMenu()));
}

