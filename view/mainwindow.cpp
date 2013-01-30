#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _option(),
      _menu(0),
      _game(0),
      _benchmark(0)
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
    this->deleteCentralWidget();

    _menu = new Menu(_option, this);

    this->setCentralWidget(_menu);

    //QObject::connect(_menu, SIGNAL(fieldChoosed(Field)), this, SLOT(initializeGame(Field)));
    QObject::connect(_menu, SIGNAL(gameLaunched()), this, SLOT(initializeGame()));
    QObject::connect(_menu, SIGNAL(benchmarkLaunched()), this, SLOT(initializeBenchmark()));
}

void MainWindow::initializeGame()
{
    this->deleteCentralWidget();

    Field field = _option.getField();

    switch(field)
    {
    case Field::BOARD:
    {
        //BoardOption * opt = (BoardOption*)option;
        _game = new BoardWidget( _option, this );
        break;
    }
    case Field::CUBE:
    {
        _game = new CubeWidget( _option, this );
        break;
    }
    case Field::TESSERACT:
    {
        _game = new TesseractWidget( _option, this);
        break;
    }
    case Field::DONUT:
        _game = new DonutWidget(_option, this);
        break;
    }

    this->setCentralWidget(_game);
    this->centralWidget()->setFocus();

    QObject::connect(_game, SIGNAL(terminated()), this, SLOT(initializeMenu()));
    QObject::connect(_game, SIGNAL(restarted()), this, SLOT(initializeGame()));

}

void MainWindow::initializeBenchmark()
{
    this->deleteCentralWidget();

    _benchmark = new BenchmarkWidget(_option, this);

    this->setCentralWidget(_benchmark);
    this->centralWidget()->setFocus();

    QObject::connect(_benchmark, SIGNAL(terminated()), this,SLOT(initializeMenu()));
}
/*
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
}
*/

void MainWindow::deleteCentralWidget()
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

    if(_benchmark)
    {
        delete _benchmark;
        _benchmark = 0;
    }
}
