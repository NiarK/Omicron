
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    _btnReturn(0),
    _btnNextMove(0),
    _lblMovementGhostCounter(0),
    _vertex(),
    _pacman(0),
    _ghosts(),
    _gameController(0),
    _scene(0),
    _view(0),
    _layout(0)
{
    //_gameController = new GameController(10,10);

    _scene = new QGraphicsScene();
    _scene->setBackgroundBrush(QBrush(QColor("black")));


    _view = new QGraphicsView(_scene);
    _view->setGeometry(0,0,800,600);

    _btnReturn = new QPushButton("Retour", this);
    _btnNextMove = new QPushButton("Movement suivant", this);
    _lblMovementGhostCounter = new QLabel();

    QHBoxLayout * controlLayout = new QHBoxLayout();
    controlLayout->addWidget(_btnReturn);
    controlLayout->addWidget(_lblMovementGhostCounter);
    controlLayout->addWidget(_btnNextMove);

    _layout = new QVBoxLayout();
    _layout->addLayout(controlLayout);
    _layout->addWidget(_view);

    this->setLayout(_layout);

    QObject::connect(_btnReturn, SIGNAL(clicked()), this, SLOT(emitReturnClicked()));
}

GameWidget::~GameWidget()
{
    delete _scene;
    delete _view;
    delete _layout;

    delete _gameController;
}



void GameWidget::emitReturnClicked() const
{
    emit returnClicked();
}


void GameWidget::setController(GameController *gc)
{
    _gameController = gc;

    // creation de la map
    unsigned int vertexNumber = _gameController->getVertexNumber();
    for(unsigned int i = 0; i < vertexNumber; ++i)
    {
        QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -GameWidget::RADIUS,
                                                               -GameWidget::RADIUS,
                                                               GameWidget::RADIUS * 2,
                                                               GameWidget::RADIUS * 2 );
        ell->setPen( QPen( QColor( "red" ) ) );
        ell->setZValue(1);

        _vertex.push_back( ell );
        _scene->addItem( _vertex.back() );
    }

    positionVertex(_vertex.begin(), _vertex.end());

    linkVertex(_scene, _vertex);

    // creation du pacman et des ghosts
    _pacman = new QGraphicsEllipseItem( -GameWidget::RADIUS + GameWidget::THICK * 2,
                                        -GameWidget::RADIUS + GameWidget::THICK * 2,
                                        GameWidget::RADIUS * 2 - GameWidget::THICK * 4,
                                        GameWidget::RADIUS * 2 - GameWidget::THICK * 4
                                        );
    _pacman->setPen(QPen(QColor("yellow")));
    _scene->addItem(_pacman);
    this->updatePacman();

    std::vector<unsigned int> ghostsPos = _gameController->getGhost();
    unsigned int ghostNumber = ghostsPos.size();
    for( unsigned int i = 0; i < ghostNumber; ++i )
    {
        QGraphicsEllipseItem * ghost = new QGraphicsEllipseItem( -GameWidget::RADIUS + GameWidget::THICK,
                                                                 -GameWidget::RADIUS + GameWidget::THICK,
                                                                 GameWidget::RADIUS * 2 - GameWidget::THICK * 2,
                                                                 GameWidget::RADIUS * 2 - GameWidget::THICK * 2
                                                                 );
        ghost->setPen(QPen(QColor("cyan")));
        _scene->addItem(ghost);
        _ghosts.push_back(ghost);
    }
    this->updateGhost();

    QObject::connect(_btnNextMove, SIGNAL(clicked()), this, SLOT(nextMove()));
}

GameController *GameWidget::getController() const
{
    return _gameController;
}

void GameWidget::linkVertex(QGraphicsScene * _scene,
                            const std::vector<QGraphicsEllipseItem *> &vertex) const
{
    unsigned int vertexNumber = vertex.size();
    for(unsigned int v = 0; v != vertexNumber; ++v)
    {
        std::vector<unsigned int> edge(this->getController()->getEdges(v));
        QPointF v1 = vertex[v]->pos();

        unsigned int edgeNumber = edge.size();
        for(unsigned int e = 0; e < edgeNumber; ++e)
        {
            if( edge[e] > v )
            {
                QPointF v2 = vertex[edge[e]]->pos();
                _scene->addLine( v1.x(), v1.y(), v2.x(), v2.y(), QPen( QColor( 150,0,0 ) ) );
            }
        }
    }
}

void GameWidget::updatePacman()
{
    _pacman->setPos(_vertex[_gameController->getPacman()]->pos());
}

void GameWidget::updateGhost()
{
    unsigned int ghostNumber = _ghosts.size();
    std::vector<unsigned int> ghostsPos = _gameController->getGhost();
    for( unsigned int i = 0; i < ghostNumber; ++i )
    {
        _ghosts[i]->setPos(_vertex[ghostsPos[i]]->pos());
    }
}

void GameWidget::updateActor()
{
    this->updatePacman();
    this->updateGhost();
}

void GameWidget::keyPressEvent ( QKeyEvent * event )
{
    switch (event->key())
    {
    case Qt::Key_Space:
        event->accept();
        this->nextMove();
        break;
    default:
        event->ignore();
        break;
    }
}

void GameWidget::nextMove()
{
    bool gameFinished = _gameController->nextMove();
    this->updateActor();

    std::string text("Nombre de coup pour la capture : ");
    // text += _gameController->getMovementCounter();
    _lblMovementGhostCounter->setText("Nombre de coup pour la capture : ");

    if(gameFinished)
    {
        QMessageBox msgBox;
        msgBox.setText("Le Pacman a été attrapé !");
        msgBox.setDetailedText("Le Pacman a été attrapé !");

        QPushButton *btnRestart = msgBox.addButton(tr("Recommener"), QMessageBox::AcceptRole);
        QPushButton *btnMenu = msgBox.addButton(tr("Revenir au menu"), QMessageBox::RejectRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnRestart)
        {
            emit restartClicked();
        }
        else if (msgBox.clickedButton() == btnMenu)
        {
            emit returnClicked();
        }
    }
}
