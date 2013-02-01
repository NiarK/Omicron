#include "cubecontroller.h"
#include <iostream>

CubeController::CubeController() :
    GameController(std::vector<unsigned int>(3,2), false, 2)
{

}


CubeController::~CubeController()
{

}

int CubeController::range(int pos1,int pos2, int dist,int dimension){
    int temp;
    int value;
    if (pos1 == pos2 )
        return dist;
    value = pow( 2, ( dimension - 1 ));


    if( pos1 < pos2 ){//On change pour que dans pos 1 on ait la plus grande valeur
        temp = pos2;
        pos2 = pos1;
        pos1 = temp;
    }
    if( pos1 >= value && pos2 >= value ){
        pos1 = pos1 - value;
        pos2 = pos2 - value;
    }
    if( pos1 >= value ){
        pos1 = pos1 - value;
        dist += 1;
    }
    return range(pos1, pos2, dist, dimension - 1);
}


unsigned int CubeController::rangeMin(unsigned int vertex)
{
    int rangeGhost1 = range(vertex, _ghosts[0], 0, 3);
    int rangeGhost2 = range(vertex, _ghosts[1], 0, 3);
    if( rangeGhost1 > rangeGhost2)
        return rangeGhost2;
    else
        return rangeGhost1;
}

void CubeController::movePacman()
{
    int range1, range2, range3; //contiendra les distances des cases par rapport au premier ghost

    if(_pacman % 4 == 0 || _pacman % 4 == 3)
    {
        range1 = rangeMin(1 + ( (_pacman / 4 ) * 4) );
        range2 = rangeMin(2 + ( (_pacman / 4 ) * 4) );
    }
    else
    {
        range1 = rangeMin(0 + ( (_pacman / 4 ) * 4) );
        range2 = rangeMin(3 + ( (_pacman / 4 ) * 4) );
    }
    if(range1 > 1)
    {
        if(_pacman % 4 == 0 || _pacman % 4 == 3)
            _pacman = 1 + ( (_pacman / 4 ) * 4);
        else
            _pacman = 0 + ( (_pacman / 4 ) * 4);
    }
    else if(range2 > 1)
    {
        if(_pacman % 4 == 0 || _pacman % 4 == 3)
            _pacman = 2 + ( (_pacman / 4 ) * 4);
        else
            _pacman = 3 + ( (_pacman / 4 ) * 4);
    }
    else
    {
        if(_pacman < 4)
            range3 = rangeMin(_pacman + 4);
        else
            range3 = rangeMin(_pacman - 4);
        if(range3 > 1)
        {
            if(_pacman < 4)
                _pacman += 4;
            else
                _pacman -= 4;
        }
        // sinon c'est perdu donc il faut juste ne pas bouger sur un ghost
        else if(range3 != 0)
        {
            if(_pacman < 4)
                _pacman += 4;
            else
                _pacman -= 4;
        }
        else if(range2 != 0)
        {
            if(_pacman % 4 == 0 || _pacman % 4 == 3)
                _pacman = 2 + ( (_pacman / 4) * 4);
            else
                _pacman = 3 + ( (_pacman / 4) * 4);
        }
        else if(range1 != 0)
        {
            if(_pacman % 4 == 0 || _pacman % 4 == 3)
                _pacman = 1 + ( (_pacman / 4) * 4);
            else
                _pacman = 0 + ( (_pacman / 4) * 4);
        }
    }
}

void CubeController::moveGhost()
{
    if(range(_pacman, _ghosts[0], 0, 3) == 1)
        _ghosts[0] = _pacman;
    else if(range(_pacman, _ghosts[1], 0, 3) == 1)
        _ghosts[1] = _pacman;
    else
    {
        int rangeNow = range(_ghosts[0],_ghosts[1],0,3);
        if(_ghosts[0] % 4 == 0 || _ghosts[0] % 4 == 3)
        {
            if(range(1 + ( (_ghosts[0] / 4 ) * 4), _ghosts[1], 0, 3 ) > rangeNow)
            {
                _ghosts[0] = 1 + ( (_ghosts[0] / 4 ) * 4) ;
            }
            else if(range(2 + ( (_ghosts[0] / 4 ) * 4), _ghosts[1], 0, 3 ) > rangeNow)
            {
                _ghosts[0] = 2 + ( (_ghosts[0] / 4 ) * 4) ;
            }
            else if(_ghosts[0] < 4)
            {
                _ghosts[0] += 4;
            }
            else
            {
                _ghosts[1] -= 4;
            }
        }
        else
        {
            if(range(0 + ( (_ghosts[0] / 4 ) * 4), _ghosts[1], 0, 3 ) > rangeNow)
            {
                _ghosts[0] = 0 + ( (_ghosts[0] / 4 ) * 4) ;
            }
            else if(range(3 + ( (_ghosts[0] / 4 ) * 4), _ghosts[1], 0, 3 ) > rangeNow)
            {
                _ghosts[0] = 3 + ( (_ghosts[0] / 4 ) * 4) ;
            }
            else if(_ghosts[0] < 4)
            {
                _ghosts[0] += 4;
            }
            else
            {
                _ghosts[1] -= 4;
            }
        }
    }
}
