#include "menu.h"


Menu::Menu(GameOption & option, QWidget *parent) :
    QWidget(parent),
    _option(option),
    _rbBoard(0),
    _rbCube(0),
    _rbTesseract(0),
    _rbDonut(0),
    _rbAI(0),
    _rbPlayerPacman(0),
    _rbPlayerGhost(0),
    _rbRandomAI(0),
    _rbWiseAI(0),
    _property(0),
    _lytProperty(0)
{

    // --- --- Layout principale
    // --- Propriétés de la partie
    // Terrain
    _rbBoard = new QRadioButton("Plateau", this);
    _rbCube = new QRadioButton("Cube", this);
    _rbTesseract = new QRadioButton("Tesseract", this);
    _rbDonut = new QRadioButton("Donut", this);
    _rbBoard->setChecked(true);
    //_rbDonut->setEnabled(false);

    QVBoxLayout * lytField = new QVBoxLayout();
    lytField->addWidget(_rbBoard);
    lytField->addWidget(_rbCube);
    lytField->addWidget(_rbTesseract);
    lytField->addWidget(_rbDonut);
    lytField->addStretch();

    QGroupBox * gbField = new QGroupBox("Terrain", this);
    gbField->setLayout(lytField);
    // ! Terrain

    // Type de jeu
    _rbAI = new QRadioButton("IA", this);
    _rbPlayerPacman = new QRadioButton("Joueur Pacman", this);
    _rbPlayerGhost = new QRadioButton("Joueur ghosts", this);
    //_rbAI->setChecked(true);
    _rbPlayerPacman->setEnabled(false);
    _rbPlayerGhost->setEnabled(false);

    QVBoxLayout * lytGameType = new QVBoxLayout();
    lytGameType->addWidget(_rbAI);
    lytGameType->addWidget(_rbPlayerPacman);
    lytGameType->addWidget(_rbPlayerGhost);
    lytGameType->addStretch();

    QGroupBox * gbGameType = new QGroupBox("Type de jeu", this);
    gbGameType->setLayout(lytGameType);
    // ! Type de jeu

    // Pacman IA
    _rbRandomAI = new QRadioButton("Al�atoire", this);
    _rbWiseAI = new QRadioButton("Sens�", this);
    //_rbWiseAI->setChecked(true);
    //_rbRandomAI->setEnabled(false);

    QVBoxLayout * lytPacmanAI = new QVBoxLayout();
    lytPacmanAI->addWidget(_rbRandomAI);
    lytPacmanAI->addWidget(_rbWiseAI);
    lytPacmanAI->addStretch();

    QGroupBox * gbPacmanAI = new QGroupBox("IA du Pacman", this);
    gbPacmanAI->setLayout(lytPacmanAI);
    // ! Pacman IA

    // Partie normale
    QPushButton * btnNormalGame = new QPushButton("&Partie normale",this);
    QPushButton * btnBenchmark = new QPushButton("&Benchmark !", this);

    QVBoxLayout * lytGbGameLauncher = new QVBoxLayout();
    lytGbGameLauncher->addWidget(btnNormalGame);
    lytGbGameLauncher->addWidget(btnBenchmark);
    lytGbGameLauncher->addStretch();

    QGroupBox * gbGameLauncher = new QGroupBox("Lancement du jeu", this);
    gbGameLauncher->setLayout(lytGbGameLauncher);
    // !  Partie normale

    QVBoxLayout * lytGameProperty = new QVBoxLayout();
    lytGameProperty->addWidget(gbField);
    lytGameProperty->addWidget(gbGameType);
    lytGameProperty->addWidget(gbPacmanAI);
    lytGameProperty->addWidget(gbGameLauncher);
    // --- --- Propriétés de la partie

    // --- --- Propriétés du terrain
    QLabel * imgPacman = new QLabel();
    imgPacman->setPixmap(QPixmap(":/Pictures/pacman.png"));

    QLabel * lblPacman = new QLabel("Pacman");

    QLabel * imgGhost = new QLabel();
    imgGhost->setPixmap(QPixmap(":/Pictures/ghost.png"));

    QLabel * lblGhost = new QLabel("Ghost");

    QHBoxLayout * lytLegend = new QHBoxLayout();
    lytLegend->addStretch();
    lytLegend->addWidget(imgPacman);
    lytLegend->addWidget(lblPacman);
    lytLegend->addStretch();
    //lytLegend->addSpacing(200);
    lytLegend->addWidget(imgGhost);
    lytLegend->addWidget(lblGhost);
    lytLegend->addStretch();


    _lytProperty = new QVBoxLayout();
    _lytProperty->addLayout(lytLegend);

    QVBoxLayout * lytPropertySup = new QVBoxLayout();
    lytPropertySup->addLayout(_lytProperty);
    lytPropertySup->addStretch();

    QGroupBox * gbFieldProperty = new QGroupBox("Proprietes", this);
    gbFieldProperty->setLayout(lytPropertySup);
    // --- --- ! Prorpiétés du terrain

    QHBoxLayout * lytMain = new QHBoxLayout();
    lytMain->addLayout(lytGameProperty);
    lytMain->addWidget(gbFieldProperty);
    // --- --- ! Layout principale

    // --- ---


    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addLayout(lytMain);
    //layout->addLayout(lytGameLauncher);
    this->setLayout(layout);

    this->setPropertyWidget();
    this->updateIHM();

    //QObject::connect(btnNormalGame, SIGNAL(clicked()), this, SLOT(emitFieldChoosed()));
    QObject::connect(btnNormalGame, SIGNAL(clicked()), this, SLOT(emitGameLaunched()));
    QObject::connect(btnBenchmark, SIGNAL(clicked()), this, SLOT(emitBenchmarkLaunched()));

    QObject::connect(_rbBoard, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbCube, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbTesseract, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbDonut, SIGNAL(clicked()), this, SLOT(updateOption()));

    QObject::connect(_rbRandomAI, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbWiseAI, SIGNAL(clicked()), this, SLOT(updateOption()));

    QObject::connect(_rbAI, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbPlayerGhost, SIGNAL(clicked()), this, SLOT(updateOption()));
    QObject::connect(_rbPlayerPacman, SIGNAL(clicked()), this, SLOT(updateOption()));
}

Menu::~Menu()
{

}

void Menu::emitFieldChoosed()
{
    if( _rbBoard->isChecked() )
    {
        emit fieldChoosed(Field::BOARD);
    }
    else if( _rbCube->isChecked() )
    {
        emit fieldChoosed(Field::CUBE);
    }
    else if( _rbTesseract->isChecked() )
    {
        emit fieldChoosed(Field::TESSERACT);
    }
    else if( _rbDonut->isChecked() )
    {
        emit fieldChoosed(Field::DONUT);
    }
}

void Menu::emitBenchmarkLaunched()
{
    /*
    if( _rbBoard->isChecked() )
    {
        emit benchmarkLaunched(Field::BOARD);
    }
    else if( _rbCube->isChecked() )
    {
        emit benchmarkLaunched(Field::CUBE);
    }
    else if( _rbTesseract->isChecked() )
    {
        emit benchmarkLaunched(Field::TESSERACT);
    }
    */
    emit benchmarkLaunched();
}

void Menu::emitGameLaunched()
{
    emit gameLaunched();
}

void Menu::setPropertyWidget()
{
    if( _property )
    {
        delete _property;
    }

    if( _rbBoard->isChecked() )
    {
        _property = new BoardPropertyWidget(_option, this);
    }
    else if( _rbCube->isChecked() )
    {
        _property = new CubePropertyWidget(_option, this);
    }
    else if( _rbTesseract->isChecked() )
    {
        _property = new TesseractPropertyWidget(_option, this);
    }
    else if( _rbDonut->isChecked() )
    {
        _property = new DonutPropertyWidget(_option, this);
    }

    _lytProperty->addWidget(_property);
}

void Menu::updateOption()
{
    if( _rbAI->isChecked() )
    {
        _option.setGameType(GameType::AI);
    }
    else if( _rbPlayerGhost->isChecked() )
    {
        _option.setGameType(GameType::GHOST_PLAYER);
    }
    else if( _rbPlayerPacman->isChecked() )
    {
        _option.setGameType(GameType::PACMAN_PLAYER);
    }

    if( _rbRandomAI->isChecked() )
    {
        _option.setPacmanAI(PacmanAI::RANDOM);
    }
    else if( _rbWiseAI->isChecked() )
    {
        _option.setPacmanAI(PacmanAI::WISE);
    }


    if( _rbBoard->isChecked() )
    {
        _option.setField(Field::BOARD);
    }
    else if( _rbCube->isChecked() )
    {
        _option.setField(Field::CUBE);
    }
    else if( _rbTesseract->isChecked() )
    {
        _option.setField(Field::TESSERACT);
    }
    else if( _rbDonut->isChecked() )
    {
        _option.setField(Field::DONUT);
    }

    this->setPropertyWidget();
}

void Menu::updateIHM()
{
    switch(_option.getField())
    {
    case Field::BOARD:
        _rbBoard->setChecked(true);
        break;
    case Field::CUBE:
        _rbCube->setChecked(true);
        break;
    case Field::TESSERACT:
        _rbTesseract->setChecked(true);
        break;
    case Field::DONUT:
        _rbDonut->setChecked(true);
        break;
    }

    this->setPropertyWidget();

    switch(_option.getGameType())
    {
    case GameType::AI:
        _rbAI->setChecked(true);
        break;
    case GameType::PACMAN_PLAYER:
        _rbPlayerPacman->setChecked(true);
        break;
    case GameType::GHOST_PLAYER:
        _rbPlayerGhost->setChecked(true);
        break;
    }

    switch(_option.getPacmanAI())
    {
    case PacmanAI::RANDOM:
        _rbRandomAI->setChecked(true);
        break;
    case PacmanAI::WISE:
        _rbWiseAI->setChecked(true);
        break;
    }

    _property->updateIHM();
}
