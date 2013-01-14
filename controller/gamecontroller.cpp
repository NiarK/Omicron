#include "gamecontroller.h"

GameController::GameController(const std::vector<unsigned int> &sizeByDimension, bool infinite, unsigned int ghost) :
    _pacman(0),
    _ghosts(),
    _pacmanMoved(false),
    _movementCounter(0),
    _matrix(0)
    //_vertexNumber(0)
{
    // Initialisation du random
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    _matrix = new HyperCube(sizeByDimension, infinite);

    _pacman = this->generatePosition();
    for(unsigned int i = 0; i < ghost; ++i)
    {
        _ghosts.push_back(this->generatePosition());
    }

    /*
    for(unsigned int y = 0; y < _matrix->size1(); ++y)
    {
        for(unsigned int x = 0; x < _matrix->size2(); ++x)
        {
            std::cout << (*_matrix)(y,x);
        }
        std::cout << std::endl;
    }
    //*/
}

GameController::~GameController()
{
    delete _matrix;
}

HyperCube *GameController::getAdjacencyMatrix()
{
    return _matrix;
}

std::vector<unsigned int> GameController::getEdges(unsigned int vertex) const
{
    if(vertex >= _matrix->size1())
    {
        throw std::bad_alloc();
    }

    unsigned int size = _matrix->size1();
    std::vector<unsigned int> edges;

    for( unsigned int i = 0; i < size; ++i )
    {
        if( (*_matrix)( vertex, i ) == 1 )
        {
            edges.push_back(i);
        }
    }

    return edges;
}

unsigned int GameController::getVertexNumber() const
{
    return _matrix->size1();

}

unsigned int GameController::generatePosition()
{
    // génération de la position aléatoire
    unsigned int high = this->getVertexNumber();
    //unsigned int low = 0;

    bool isSamePosition;
    unsigned int ghostNumber = _ghosts.size();

    unsigned int pos;

    do
    {
        isSamePosition = false;

        pos = qrand() % high;//((high + 1) - low) + low;

        if( pos == _pacman )
        {
            isSamePosition = true;
        }

        for( unsigned int i = 0; !isSamePosition && i < ghostNumber; ++i )
        {
            if( pos == _ghosts[i] )
            {
                isSamePosition = true;
            }
        }

    }while(isSamePosition);

    return pos;
}

unsigned int GameController::getPacman() const
{
    return _pacman;
}

std::vector<unsigned int> GameController::getGhost() const
{
    return _ghosts;
}


bool GameController::nextMove()
{
    //Actor a;
    bool gameOver = false;

    if(!_pacmanMoved)
    {
        this->movePacman();
        //a = Actor::PACMAN;
    }
    else
    {
        this->moveGhost();
        ++_movementCounter;
        gameOver = pacmanIsCatched();
        //a = Actor::GHOST;
    }

    _pacmanMoved = !_pacmanMoved;

    return gameOver;
}

unsigned int GameController::getGhostMovementCounter() const
{
    return _movementCounter;
}

bool GameController::pacmanIsCatched()
{
    //TODO : ameliorer l'algo
    unsigned int ghostNumber = _ghosts.size();

    for(unsigned int i = 0; i < ghostNumber; ++i)
    {
        if( _ghosts[i] == _pacman )
        {
            return true;
        }
    }

    return false;
}
