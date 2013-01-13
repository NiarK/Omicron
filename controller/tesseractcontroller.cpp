#include "tesseractcontroller.h"

TesseractController::TesseractController() :
    GameController(std::vector<unsigned int>(4,2), false, 2)
{
}

TesseractController::~TesseractController()
{

}

void TesseractController::movePacman()
{
    _pacman++;
    if(_pacman >= this->getVertexNumber())
    {
        _pacman = 0;
    }
}

void TesseractController::moveGhost()
{
    _ghosts[0]++;
    if(_ghosts[0] >= this->getVertexNumber())
    {
        _ghosts[0] = 0;
    }
}
