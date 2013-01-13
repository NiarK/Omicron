#include "menu.h"


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    _btnBoard(0),
    //_btnDonut(0),
    _btnCube(0),
    _btnTesseract(0)
{
    _btnBoard     = new QPushButton("->", this);
    //_btnDonut     = new QPushButton("->", this);
    _btnCube      = new QPushButton("->", this);
    _btnTesseract = new QPushButton("->", this);

    //_btnDonut->setEnabled(false);
    //_btnCube->setEnabled(false);
    //_btnTesseract->setEnabled(false);

    QLabel *lblBoard = new QLabel("Plateau", this);
    lblBoard->setFont(QFont("Verdana", 30));

    /*
    QLabel *lblDonut = new QLabel("Donut", this);
    lblDonut->setFont(QFont("Verdana", 30));
    //*/

    QLabel *lblCube = new QLabel("Cube", this);
    lblCube->setFont(QFont("Verdana", 30));

    QLabel *lblTesseract = new QLabel("Tesseract", this);
    lblTesseract->setFont(QFont("Verdana", 30));

    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout * lytBoard = new QHBoxLayout();
    lytBoard->addWidget(lblBoard);
    lytBoard->addWidget(line);
    lytBoard->addWidget(_btnBoard);

    /*
    QHBoxLayout * lytDonut = new QHBoxLayout();
    lytDonut->addWidget(lblDonut);
    lytDonut->addWidget(line);
    lytDonut->addWidget(_btnDonut);
    //*/

    QHBoxLayout * lytCube = new QHBoxLayout();
    lytCube->addWidget(lblCube);
    lytCube->addWidget(line);
    lytCube->addWidget(_btnCube);

    QHBoxLayout * lytTesseract = new QHBoxLayout();
    lytTesseract->addWidget(lblTesseract);
    lytTesseract->addWidget(line);
    lytTesseract->addWidget(_btnTesseract);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addLayout(lytBoard);
    //layout->addLayout(lytDonut);
    layout->addLayout(lytCube);
    layout->addLayout(lytTesseract);

    this->setLayout(layout);

    QObject::connect(_btnBoard, SIGNAL(clicked()), this, SLOT(emitFieldChoosed()));
    QObject::connect(_btnCube, SIGNAL(clicked()), this, SLOT(emitFieldChoosed()));
    QObject::connect(_btnTesseract, SIGNAL(clicked()), this, SLOT(emitFieldChoosed()));
}

Menu::~Menu()
{
    delete _btnBoard;
    //delete _btnDonut;
    delete _btnCube;
    delete _btnTesseract;
}

void Menu::emitFieldChoosed()
{
    if(QObject::sender() == _btnBoard)
    {
        emit fieldChoosed(Field::BOARD);
    }
    else if(QObject::sender() == _btnCube)
    {
        emit fieldChoosed(Field::CUBE);
    }
    else if(QObject::sender() == _btnTesseract)
    {
        emit fieldChoosed(Field::TESSERACT);
    }
}
