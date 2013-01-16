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
    QObject::connect(_menu, SIGNAL(benchmarkLaunched(Field)), this, SLOT(lanchBenchmark(Field)));
}

void MainWindow::initializeGame(Field field)
{
    _field = field;

    this->initializeGame();
}

void MainWindow::initializeGame()
{
    if(_game)
    {
        delete _game;
        _game = 0;
    }

    if(_menu)
    {
        delete _menu;
        _menu = 0;
    }

    switch(_field)
    {
    case Field::BOARD:
        _game = new BoardWidget(8,8,this);
        break;
    case Field::CUBE:
        _game = new CubeWidget(this);
        break;
    case Field::TESSERACT:
        _game = new TesseractWidget(this);
        break;
    }


    this->setCentralWidget(_game);
    this->centralWidget()->setFocus();

    QObject::connect(_game, SIGNAL(returnClicked()), this, SLOT(initializeMenu()));
    QObject::connect(_game, SIGNAL(restartClicked()), this, SLOT(initializeGame()));
}

void MainWindow::lanchBenchmark(Field f)
{
    if(f == Field::BOARD)
    {
        BoardController b(8,8);
        b.benchmark(10000);
    }
    else if(f == Field::CUBE)
    {
        CubeController c;
        c.benchmark(10000);
    }
    else if(f == Field::TESSERACT)
    {
        TesseractController t;
        t.benchmark(10000);
    }
    /*
    switch(f)
    {
    case Field::BOARD:
        BoardController b(8,8);
        b.benchmark(10000);
        break;
    case Field::CUBE:
        CubeController c;
        c.benchmark(10000);
        break;
    case Field::TESSERACT:
        TesseractController t;
        t.benchmark(10000);
        break;
    }
//*/
}


