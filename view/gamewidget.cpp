
#include "gamewidget.h"

GameWidget::GameWidget(const GameOption &option, QWidget *parent) :
    QWidget(parent),
    _option(option),
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

    _btnReturn = new QPushButton("&Retour", this);
    _btnNextMove = new QPushButton("Movement &suivant", this);
    _lblMovementGhostCounter = new QLabel();

    QHBoxLayout * controlLayout = new QHBoxLayout();
    controlLayout->addWidget(_btnReturn);
    controlLayout->addStretch();
    controlLayout->addWidget(_btnNextMove);

    QLabel * lblTextCounter = new QLabel("Nombre de coup(s) joué : ");
    QLabel * lblShortcut = new QLabel("Mouvement suivant : espace");

    QHBoxLayout * lytCounter = new QHBoxLayout();
    lytCounter->addWidget(lblTextCounter);
    lytCounter->addWidget(_lblMovementGhostCounter);
    lytCounter->addStretch();
    lytCounter->addWidget(lblShortcut);

    _layout = new QVBoxLayout();
    _layout->addLayout(lytCounter);
    _layout->addWidget(_view);
    _layout->addLayout(controlLayout);

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

void GameWidget::wheelEvent(QWheelEvent *event)
{
    qreal d = (qreal)event->delta() / 1000 + 1;
    _view->scale(d,d);
}

void GameWidget::emitReturnClicked() const
{
    emit terminated();
}


void GameWidget::setController(GameController *gc)
{
    _gameController = gc;

    QBrush brush(QColor("red"));
    QPen pen(brush, 2);
    QPen pacmanPen(QBrush(QColor("yellow")), 2);
    QPen ghostPen(QBrush(QColor("cyan")), 2);

    // creation de la map
    unsigned int vertexNumber = _gameController->getVertexNumber();
    for(unsigned int i = 0; i < vertexNumber; ++i)
    {
        QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -GameWidget::RADIUS,
                                                               -GameWidget::RADIUS,
                                                               GameWidget::RADIUS * 2,
                                                               GameWidget::RADIUS * 2 );
        ell->setPen( pen );
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
    _pacman->setPen(pacmanPen);
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
        ghost->setPen(ghostPen);
        _scene->addItem(ghost);
        _ghosts.push_back(ghost);
    }
    this->updateGhost();

    QObject::connect(_btnNextMove, SIGNAL(clicked()), this, SLOT(nextMove()));


    _gameController->setPacmanAI(_option.getPacmanAI());
    //_gameController->benchmark(1000);
    //_gameController->reset();

    _view->setFocus();
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
    _gameController->nextMove();
    bool gameFinished = _gameController->gameOver();
    this->updateActor();

    _lblMovementGhostCounter->setText(QString::number(_gameController->getGhostMovementCounter()));

    if(gameFinished)
    {
        QMessageBox msgBox;
        msgBox.setText("Le Pacman a été attrapé !");
        QString text = "Les ghosts ont mis ";
        text += QString("%1").arg( _gameController->getGhostMovementCounter() );
        text += " coups pour attraper le Pacman.\n";

        msgBox.setDetailedText(text);

        QPushButton *btnRestart = msgBox.addButton(tr("&Recommener"), QMessageBox::AcceptRole);
        QPushButton *btnMenu = msgBox.addButton(tr("Revenir au &menu"), QMessageBox::RejectRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnRestart)
        {
            emit restarted();
        }
        else if (msgBox.clickedButton() == btnMenu)
        {
            emit terminated();
        }
    }
}
