
#include "game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    _return(0),
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

    _return = new QPushButton("Retour", this);

    _layout = new QVBoxLayout();
    _layout->addWidget(_view);
    _layout->addWidget(_return);

    this->setLayout(_layout);

    QObject::connect(_return, SIGNAL(clicked()), this, SLOT(emitReturnClicked()));
}

Game::~Game()
{
    delete _scene;
    delete _view;
    delete _layout;

    delete _gameController;
}



void Game::emitReturnClicked() const
{
    emit returnClicked();
}


void Game::setController(GameController *gc)
{
    _gameController = gc;

    // creation de la map
    unsigned int vertexNumber = _gameController->getVertexNumber();
    for(unsigned int i = 0; i < vertexNumber; ++i)
    {
        QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -Game::RADIUS/2, -Game::RADIUS/2, Game::RADIUS, Game::RADIUS );
        ell->setPen( QPen( QColor( "red" ) ) );
        ell->setZValue(1);

        _vertex.push_back( ell );
        _scene->addItem( _vertex.back() );
    }

    positionVertex(_vertex.begin(), _vertex.end());

    linkVertex(_scene, _vertex);

    // creation du pacman et des ghosts
    _pacman = new QGraphicsEllipseItem( -Game::RADIUS/4, -Game::RADIUS/4, Game::RADIUS/2, Game::RADIUS/2 );
    _pacman->setPen(QPen(QColor("yellow")));
    _scene->addItem(_pacman);
    this->updatePacman();

    std::vector<unsigned int> ghostsPos = _gameController->getGhost();
    unsigned int ghostNumber = ghostsPos.size();
    for( unsigned int i = 0; i < ghostNumber; ++i )
    {
        QGraphicsEllipseItem * ghost = new QGraphicsEllipseItem( -Game::RADIUS/4, -Game::RADIUS/4, Game::RADIUS/2, Game::RADIUS/2 );
        ghost->setPen(QPen(QColor("cyan")));
        _scene->addItem(ghost);
        _ghosts.push_back(ghost);
    }
    this->updateGhost();
}

GameController *Game::getController() const
{
    return _gameController;
}

void Game::linkVertex(QGraphicsScene * _scene,
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

void Game::updatePacman()
{
    _pacman->setPos(_vertex[_gameController->getPacman()]->pos());
}

void Game::updateGhost()
{
    unsigned int ghostNumber = _ghosts.size();
    std::vector<unsigned int> ghostsPos = _gameController->getGhost();
    for( unsigned int i = 0; i < ghostNumber; ++i )
    {
        _ghosts[i]->setPos(_vertex[ghostsPos[i]]->pos());
    }
}
