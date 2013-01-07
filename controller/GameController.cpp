#include "controller/GameController.h"

GameController::GameController(unsigned int width, unsigned int height) :
    _width(width),
    _height(height),
    _matrix(0)
{
    std::vector<unsigned int> sizeByDimension;
    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    _matrix = new HyperCube(sizeByDimension, false);
}

GameController::~GameController()
{
    delete _matrix;
}
//TODO enlever ça !
HyperCube *GameController::getAdjacencyMatrix() const
{
    return _matrix;
}

unsigned int GameController::getWidth()
{
    return _width;
}

unsigned int GameController::getHeight()
{
    return _height;
}

unsigned int GameController::getVertexNumber()
{
    return _height * _width;
}

std::vector<unsigned int> GameController::getEdge(unsigned int vertex)
{
    if(vertex >= _matrix->size1())
    {
        throw std::bad_alloc();
    }

    unsigned int size = _matrix->size1();
    std::vector<unsigned int> edge;

    for( unsigned int i = 0; i < size; ++i )
    {
        if( (*_matrix)( vertex, i ) == 1 )
        {
            edge.push_back(i);
        }
    }

    return edge;
}
