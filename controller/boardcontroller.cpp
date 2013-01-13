#include "controller/boardcontroller.h"

BoardController::BoardController(unsigned int width, unsigned int height) :
    GameController(this->createSizeByDimensionVector(width, height), false, 2),
    _width(width),
    _height(height)
{
    /*std::vector<unsigned int> sizeByDimension;
    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    _matrix = new HyperCube(sizeByDimension, false);*/
}

BoardController::~BoardController()
{
    //GameController::~GameController();
}

unsigned int BoardController::getWidth()
{
    return _width;
}

unsigned int BoardController::getHeight()
{
    return _height;
}



std::vector<unsigned int> BoardController::createSizeByDimensionVector(unsigned int width, unsigned int height)
{
    std::vector<unsigned int> sizeByDimension;

    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    return sizeByDimension;
}

void BoardController::movePacman()
{
    _pacman++;
    if(_pacman >= this->getVertexNumber())
    {
        _pacman = 0;
    }
}

void BoardController::moveGhost()
{
    _ghosts[0]++;
    if(_ghosts[0] >= this->getVertexNumber())
    {
        _ghosts[0] = 0;
    }
}
