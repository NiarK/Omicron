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

    QObject::connect(_menu, SIGNAL(fieldChoosed(Field)), this, SLOT(initializeGame(Field)));
}

void MainWindow::initializeGame(Field field)
{
    if(!_game)
    {
        switch(field)
        {
        case Field::BOARD:
            _game = new BoardWidget(8,8,this);
            break;
        case Field::CUBE:
            _game = new CubeWidget(this);
            break;
        case Field::TESSERACT:
            _game = new CubeWidget(this);
            break;

        }
    }

    if(_menu)
    {
        delete _menu;
        _menu = 0;
    }

    this->setCentralWidget(_game);

    QObject::connect(_game, SIGNAL(returnClicked()), this, SLOT(initializeMenu()));
}

