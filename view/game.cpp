
#include "game.h"

Game::Game(QWidget *parent) :
    QWidget(parent),
    _return(0),
    _vertex(),
    _gameController(0),
    _scene(0),
    _view(0),
    _layout(0)
{
    //_gameController = new GameController(10,10);

    _scene = new QGraphicsScene();
    _scene->setBackgroundBrush(QBrush(QColor("black")));
    /*
    for(unsigned int y = 0; y < _board->getHeight(); ++y)
    {
        for(unsigned int x = 0; x < _board->getWidth(); ++x)
        {
            QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -10, -10, 20, 20 );
            ell->setPos(x*40,y*40);
            ell->setZValue(y);
            ell->setPen( QPen( QColor( "red" ) ) );

            _vertex.push_back( ell );
            _scene->addItem( _vertex.back() );
        }
    }
    //*/
    /*
    unsigned int vertexNumber = _gameController->getVertexNumber();
    for(unsigned int i = 0; i < vertexNumber; ++i)
    {
        QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -10, -10, 20, 20 );
        ell->setPen( QPen( QColor( "red" ) ) );

        _vertex.push_back( ell );
        _scene->addItem( _vertex.back() );
    }
    //*/
    //TODO: initialize vertex
    //this->initializeVertex(_vertex);

    //unsigned int vertexNumber = _board->getVertexNumber();
    /*
    for(unsigned int v = 0; v < vertexNumber; ++v)
    {
        std::vector<unsigned int> edge(_board->getEdge(v));
        QPointF v1 = _vertex[v]->pos();

        unsigned int edgeNumber = edge.size();
        for(unsigned int e = 0; e < edgeNumber; ++e)
        {
            if( edge[e] > v )
            {
                QPointF v2 = _vertex[edge[e]]->pos();
                _scene->addLine( v1.x(), v1.y(), v2.x(), v2.y(), QPen( QColor( 50,0,0 ) ) );
            }
        }
    }
    //*/

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
/*
void Game::initializeVertex(const std::vector<QGraphicsEllipseItem*> & vertex) const
{
    std::cout << "game" << std::endl;
}
*/
/*std::vector<QGraphicsEllipseItem*>::iterator Game::getVertexIterator()
{
    return _vertex.begin();
}

std::vector<QGraphicsEllipseItem*>::iterator Game::getVertexEndIterator()
{
    return _vertex.end();
}*/

void Game::setController(GameController *gc)
{
    _gameController = gc;

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
}

GameController * Game::getController() const
{
    return _gameController;
}

void Game::linkVertex(QGraphicsScene * _scene,
                             const std::vector<QGraphicsEllipseItem *> &vertex) const
{
    unsigned int vertexNumber = vertex.size();
    for(unsigned int v = 0; v != vertexNumber; ++v)
    {
        std::vector<unsigned int> edge(this->getController()->getEdge(v));
        QPointF v1 = vertex[v]->pos();

        unsigned int edgeNumber = edge.size();
        for(unsigned int e = 0; e < edgeNumber; ++e)
        {
            if( edge[e] > v )
            {
                QPointF v2 = vertex[edge[e]]->pos();
                _scene->addLine( v1.x(), v1.y(), v2.x(), v2.y(), QPen( QColor( 50,0,0 ) ) );
            }
        }
    }
}
