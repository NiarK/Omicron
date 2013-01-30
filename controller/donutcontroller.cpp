#include "donutcontroller.h"

DonutController::DonutController() :
    GameController(std::vector<unsigned int>(2,8), true, 4),
    _width(8),
    _height(8),
    _chase(false),
    _optimumPosition(),
    _ghostPlaced(1)
{
    _optimumPosition.push_back(_ghosts[0]);
    _optimumPosition.push_back(0);
    _optimumPosition.push_back(0);
    _optimumPosition.push_back(0);

    if(_optimumPosition[0] >= _height / 2 * _width) // en bas
    {
        _optimumPosition[1] = _optimumPosition[0] - ( _width * _height / 2 );
    }
    else // en haut
    {
        _optimumPosition[1] = _optimumPosition[0] + ( _width * _height / 2 );
    }

    if(_optimumPosition[0] % _width < _width / 2)// à gauche
    {
        _optimumPosition[2] = _optimumPosition[0] + _width / 2;
        _optimumPosition[3] = _optimumPosition[1] + _width / 2;
    }
    else // à droite
    {
        _optimumPosition[2] = _optimumPosition[0] - _width / 2;
        _optimumPosition[3] = _optimumPosition[1] - _width / 2;
    }

}

DonutController::~DonutController()
{
}

unsigned int DonutController::range(unsigned int v0, unsigned int v1)
{
    unsigned int middleX = _width / 2;
    unsigned int middleY = _height / 2;
    unsigned int rangeX = (unsigned int)abs( (int)(v1 % _width) - (int)(v0 % _width) );
    unsigned int rangeY = (unsigned int)abs( (int)(v1 / _width) - (int)(v0 / _width) );

    if ( rangeX > middleX )
    {
        rangeX = _width - rangeX;
    }

    if ( rangeY > middleY )
    {
        rangeY = _height - rangeY;
    }

    return rangeX + rangeY;
}

void DonutController::movePacman()
{
    ++_pacman;
    if(_pacman >= this->getVertexNumber())
    {
        _pacman = 0;
    }
}

bool DonutController::diagonalTest(unsigned int place)
{
    if(range(place,_pacman) == 2
            && _pacman % _width != place % _width
            && _pacman / _width != place / _width)
        return true;
    return false;
}

void DonutController::moveGhost()
{
    unsigned int ghostNumber = _ghosts.size();
    // verification si un ghost peu manger le pacman.
    for(unsigned int g = 0; g < ghostNumber; ++g)
    {
        if( range(_pacman, _ghosts[g]) == 1)
        {
            _ghosts[g] = _pacman;
            return;
        }
    }

    if( ! _chase )
    {


        if(_ghostPlaced == ghostNumber)
        {
            _chase = true;
        }
    }
    else
    {

    }
}
