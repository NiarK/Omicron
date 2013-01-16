#include "menu.h"


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    _rbBoard(0),
    _rbCube(0),
    _rbTesseract(0),
    _rbDonut(0)
{

    // --- --- Layout principale
    // --- Propriétés de la partie
    // Terrain
    _rbBoard = new QRadioButton("Plateau", this);
    _rbCube = new QRadioButton("Cube", this);
    _rbTesseract = new QRadioButton("Tesseract", this);
    _rbDonut = new QRadioButton("Donut", this);
    _rbBoard->setChecked(true);
    _rbDonut->setEnabled(false);

    QVBoxLayout * lytField = new QVBoxLayout();
    lytField->addWidget(_rbBoard);
    lytField->addWidget(_rbCube);
    lytField->addWidget(_rbTesseract);
    lytField->addWidget(_rbDonut);

    QGroupBox * gbField = new QGroupBox("Terrain", this);
    gbField->setLayout(lytField);
    // ! Terrain

    // Type de jeu
    QRadioButton * rbIA = new QRadioButton("IA", this);
    QRadioButton * rbPlayerPacman = new QRadioButton("Joueur Pacman", this);
    QRadioButton * rbPlayerGhost = new QRadioButton("Joueur ghosts", this);
    rbIA->setChecked(true);
    rbPlayerPacman->setEnabled(false);
    rbPlayerGhost->setEnabled(false);

    QVBoxLayout * lytGameType = new QVBoxLayout();
    lytGameType->addWidget(rbIA);
    lytGameType->addWidget(rbPlayerPacman);
    lytGameType->addWidget(rbPlayerGhost);

    QGroupBox * gbGameType = new QGroupBox("Type de jeu", this);
    gbGameType->setLayout(lytGameType);
    // ! Type de jeu

    // Pacman IA
    QRadioButton * rbRandomAI = new QRadioButton("Aleatoire", this);
    QRadioButton * rbWiseAI = new QRadioButton("Sense", this);
    rbWiseAI->setChecked(true);
    rbRandomAI->setEnabled(false);

    QVBoxLayout * lytPacmanAI = new QVBoxLayout();
    lytPacmanAI->addWidget(rbRandomAI);
    lytPacmanAI->addWidget(rbWiseAI);

    QGroupBox * gbPacmanAI = new QGroupBox("IA du Pacman", this);
    gbPacmanAI->setLayout(lytPacmanAI);
    // ! Pacman IA

    QVBoxLayout * lytGameProperty = new QVBoxLayout();
    lytGameProperty->addWidget(gbField);
    lytGameProperty->addWidget(gbGameType);
    lytGameProperty->addWidget(gbPacmanAI);
    // --- --- Propriétés de la partie

    // --- --- Propriétés du terrain
    QLabel * imgPacman = new QLabel();
    imgPacman->setPixmap(QPixmap(":/Pictures/pacman.png"));

    QLabel * lblPacman = new QLabel("Pacman");

    QLabel * imgGhost = new QLabel();
    imgGhost->setPixmap(QPixmap(":/Pictures/ghost.png"));

    QLabel * lblGhost = new QLabel("Ghost");

    QHBoxLayout * lytLegend = new QHBoxLayout();
    lytLegend->addWidget(imgPacman);
    lytLegend->addWidget(lblPacman);
    lytLegend->addSpacing(200);
    lytLegend->addWidget(lblGhost);
    lytLegend->addWidget(imgGhost);

    PropertyWidget * property = new PropertyWidget(this);

    QVBoxLayout * lytProperty = new QVBoxLayout();
    lytProperty->addLayout(lytLegend);
    lytProperty->addWidget(property);

    QGroupBox * gbFieldProperty = new QGroupBox("Proprietes", this);
    gbFieldProperty->setLayout(lytProperty);
    // --- --- ! Prorpiétés du terrain

    QHBoxLayout * lytMain = new QHBoxLayout();
    lytMain->addLayout(lytGameProperty);
    lytMain->addWidget(gbFieldProperty);
    // --- --- ! Layout principale

    // --- --- Partie normale
    QPushButton * btnNormalGame = new QPushButton("Partie normale",this);

    QHBoxLayout * lytGbGameLauncher = new QHBoxLayout();
    lytGbGameLauncher->addWidget(btnNormalGame);
    lytGbGameLauncher->addSpacing(50);

    QGroupBox * gbGameLauncher = new QGroupBox("Lancement du jeu", this);
    gbGameLauncher->setLayout(lytGbGameLauncher);

    // Benchmark
    QLabel * lblBenchmark = new QLabel("Nombre de partie : ");
    QLineEdit * txtBenchmark = new QLineEdit("10000", this);
    QPushButton * btnBenchmark = new QPushButton("Benchmark !", this);
    //btnBenchmark->setEnabled(false);

    QHBoxLayout * lytGbBenchmark = new QHBoxLayout();
    lytGbBenchmark->addWidget(lblBenchmark);
    lytGbBenchmark->addWidget(txtBenchmark);
    lytGbBenchmark->addWidget(btnBenchmark);
    lytGbBenchmark->addSpacing(50);

    QGroupBox * gbBenchmark = new QGroupBox("Benchmark", this);
    gbBenchmark->setLayout(lytGbBenchmark);
    // ! Benchmark

    // Lancement du jeu
    QHBoxLayout * lytGameLauncher = new QHBoxLayout();
    lytGameLauncher->addWidget(gbGameLauncher);
    lytGameLauncher->addWidget(gbBenchmark);
    // ! Lancement du jeu

    // ---!  Partie normale

    // --- ---


    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addLayout(lytMain);
    layout->addLayout(lytGameLauncher);
    this->setLayout(layout);

    QObject::connect(btnNormalGame, SIGNAL(clicked()), this, SLOT(emitFieldChoosed()));
    QObject::connect(btnBenchmark, SIGNAL(clicked()), this, SLOT(emitBenchmarkLaunched()));
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
}

void Menu::emitBenchmarkLaunched()
{
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
}
