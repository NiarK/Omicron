#include "gamecontroller.h"

GameController::GameController(const std::vector<unsigned int> &sizeByDimension, bool infinite, unsigned int ghost) :
    _pacman(0),
    _ghosts()
{
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

std::vector<unsigned int> GameController::getEdges(unsigned int vertex)
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
    unsigned int high = this->getVertexNumber();
    unsigned int low = 0;
    return qrand() % ((high + 1) - low) + low;
}

unsigned int GameController::getPacman() const
{
    return _pacman;
}

std::vector<unsigned int> GameController::getGhost() const
{
    return _ghosts;
}
