#include "cubecontroller.h"

CubeController::CubeController() :
    GameController(std::vector<unsigned int>(3,2), false, 2)
{

}


CubeController::~CubeController()
{

}

void CubeController::movePacman()
{
    _pacman++;
    if(_pacman >= this->getVertexNumber())
    {
        _pacman = 0;
    }
}

void CubeController::moveGhost()
{
    _ghosts[0]++;
    if(_ghosts[0] >= this->getVertexNumber())
    {
        _ghosts[0] = 0;
    }
}
