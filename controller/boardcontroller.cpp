#include "controller/boardcontroller.h"
#include <cmath>
#include <cstdlib>

BoardController::BoardController(unsigned int width, unsigned int height) :
    GameController(this->createSizeByDimensionVector(width, height), false, 2),
    _width(width),
    _height(height),
    _runner(0),
    _selected(false)
{
    /*std::vector<unsigned int> sizeByDimension;
    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    _matrix = new HyperCube(sizeByDimension, false);*/
}

void BoardController::reset()
{
    _runner = 0;
    _selected = false;
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

//fonction qui test si la position est au bord de la map
//renvoi true si c'est un bord
bool BoardController::borderTest(int pos){
    int w = getWidth();
    int h = getHeight();
    return (pos < w || pos >= w * h - w || pos % w ==0 || pos % w == w - 1);
}

int BoardController::range(int pos1, int pos2){
    int dist=0;
    int temp=0;
    int w = getWidth();
    dist = pos1 % w - pos2 % w;
    if(dist < 0)
        dist = dist * -1;
    temp = pos1 / w - pos2 / w;
    if(temp < 0)
        temp = temp * -1;
    return dist + temp;
}

std::vector<unsigned int> BoardController::createSizeByDimensionVector(unsigned int width, unsigned int height)
{
    std::vector<unsigned int> sizeByDimension;

    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    return sizeByDimension;
}

bool BoardController::parityTest(int nb){
    int w = getWidth();
    nb = nb / w + nb % w;
    if( nb % 2 )
        return true;
    else return false;
}

void BoardController::calculateMovement(unsigned int nb){
    //Définition des variables
    int vertical;
    int verticalabs;
    int horizontal;
    int horizontalabs;
    unsigned int nb2;
    int w = getWidth();
    if( nb==1 )
        nb2=0;
    else
        nb2=1;
    //calcul du vertical
    vertical = _ghosts[nb] / w - _pacman / w;
    if( vertical < 0 )// on passe le vertical en absolu pour le comparer
        verticalabs = -vertical;
    else
        verticalabs = vertical;
    //calcul de l'horizontal
    horizontal = _ghosts[nb] % w - _pacman % w;
    if(horizontal < 0)// on passe l'horizontal en absolu pour le comparer
        horizontalabs = -horizontal;
    else
        horizontalabs = horizontal;
    //On compare les valeurs
    //si il y a plus de distance dans la vertical on va rapprocher
    //dans la verticale pour se rapprocher de la diagonale
    //sinon on se rapproche dans l'horizontale pour se rapprocher
    //de la diagonale
    if( verticalabs > horizontalabs )
    {
        //si vertical est positif alors le pacman est au dessus du ghost
        //il faut donc faire remonter le ghost
        if( vertical > 0 )
        {
            if( _ghosts[nb] - w == _ghosts[nb2] )
            {
                if( horizontal > 0 )
                    _ghosts[nb] -= 1;
                else
                    _ghosts[nb] += 1;
            }
            else
                _ghosts[nb] -= w;
        }
        else
        {
            if( _ghosts[nb] + w == _ghosts[nb2] )
            {
                if( horizontal > 0 )
                    _ghosts[nb] -= 1;
                else
                    _ghosts[nb] += 1;
            }
            else
                _ghosts[nb] += w;
        }
    }
    else
    {
        //si horizontal est positif alors le pacman est à gauche du ghost
        //il faut donc faire partir à gauche le ghost
        if( horizontal > 0 )
        {
            if( _ghosts[nb] - 1 == _ghosts[nb2] ){
                if( vertical > 0 )
                    _ghosts[nb] -= w;
                else
                    _ghosts[nb] += w;
            }
            else
                _ghosts[nb] -= 1;
        }
        else
        {
            if( _ghosts[nb] + 1 == _ghosts[nb2] ){
                if( vertical > 0 )
                    _ghosts[nb] -= w;
                else
                    _ghosts[nb] += w;
            }
            else
                _ghosts[nb] += 1;
        }
    }
}

int BoardController::rangeMin(int value){
    bool test;
    int dist, dist2;
    unsigned int w = getWidth();
    unsigned int h = getHeight();
    //On prépare le test en fonction de la valeur en paramètre
    if( value == -1 )
        test = _pacman % w != 0;
    else if( value == 1 )
        test = _pacman % w != ( w - 1 );
    else if( value == -w )
        test = _pacman >= w;
    else if( value == w )
        test = _pacman < w * h - w;
    else
        test = false;
    if(test)
    {
        dist = range(_pacman + value, _ghosts[0]);
        dist2 = range(_pacman + value, _ghosts[1]);
        if( dist < dist2 )
            return dist;
        else
            return dist2;
    }
    else
    {
        return 0;
    }
}

void BoardController::randomPacman()
{
    bool move = false;
    int random = rand() % 4;
    int w = getWidth();
    while(move == false)
    {
        switch(random)
        {
        case 0:
            if(_pacman >= w && _pacman - w != _ghosts[0] && _pacman - w != _ghosts[1])
            {
                _pacman = _pacman - w;
                move = true;
            }
            else
            {
                random++;
                random = random % 4;
            }
            break;
        case 1:
            if(_pacman % 8 != 7 && _pacman + 1 != _ghosts[0] && _pacman + 1 != _ghosts[1])
            {
                _pacman = _pacman + 1;
                move = true;
            }
            else
            {
                random++;
                random = random % 4;
            }
            break;
        case 2:
            if(_pacman < w * getHeight() - w && _pacman + w != _ghosts[0] && _pacman + w != _ghosts[1])
            {
                _pacman = _pacman + w;
                move = true;
            }
            else
            {
                random++;
                random = random % 4;
            }
            break;
        case 3:
            if(_pacman % 8 != 0 && _pacman - 1 != _ghosts[0] && _pacman - 1 != _ghosts[1])
            {
                _pacman = _pacman - 1;
                move = true;
            }
            else
            {
                random++;
                random = random % 4;
            }
            break;
        }
    }
}

void BoardController::movePacman()
{
    randomPacman();
    /*
    int left, right, up, down;
    unsigned int w = getWidth();
    left = rangeMin(-1);
    right = rangeMin(1);
    up = rangeMin(-w);
    down = rangeMin(w);
    //On évite d'aller sur les bords.
    //On va vers la valeur la plus élevée
    if( left > 1
            && ( left >= down || ( down != 0 && borderTest(_pacman + w)))
            && ( left >= right || ( right!= 0 && borderTest(_pacman + 1)))
            && ( left >= up || ( up != 0 && borderTest(_pacman - w)))
            && !borderTest(_pacman - 1)){
        _pacman -= 1;
    }
    else if( down > 1
            && ( down >= left || ( left != 0 && borderTest(_pacman - 1)))
            && ( down >= right || ( right != 0 && borderTest(_pacman + 1)))
            && ( down >= up || ( up != 0 && borderTest(_pacman - w)))
            && !borderTest(_pacman + w)){
        _pacman += w;
    }
    else if( right > 1
            && ( right >= left || ( left != 0 && borderTest(_pacman - 1)))
            && ( right >= down || ( down !=0 && borderTest(_pacman + w)))
            && ( right >= up || ( up !=0 && borderTest(_pacman - w)))
            && !borderTest(_pacman + 1 )){
        _pacman += 1;
    }
    else if( up > 1
            && ( up >= left || ( left != 0 && borderTest(_pacman - 1)))
            && ( up >= down || ( down != 0 && borderTest(_pacman + w)))
            && ( up >= right || ( right != 0 && borderTest(_pacman + 1)))
            && !borderTest(_pacman - w)){
        _pacman -= w;
    }
    //Les valeurs qui ne sont pas sur les bords font que le pacman est mangé
    //par un fantome. donc maintenant on ne prend que la valeur la plus élevée
    else if( left > 1 && left >= down && left >= right && left >= up ){
        _pacman -= 1;
    }
    else if( down > 1 && down >= right && down >= up ){
        _pacman += w;
    }
    else if( right > 1 && right >= up ){
        _pacman += 1;
    }
    else if( up > 1 ){
        _pacman-=w;
    }
    //On sait maintenant qu'on va forcément perdre donc il faut ne pas bouger
    //dans un mur
    else if( left != 0 ){
        _pacman -= 1;
    }else if( right != 0 ){
        _pacman += 1;
    }else if( up != 0 ){
        _pacman -= w;
    }else if( down != 0 ){
        _pacman += w;
    }
    */
}

void BoardController::moveGhost()
{
    bool parity;
    int range1 = range(_pacman, _ghosts[0]);
    int range2 = range(_pacman, _ghosts[1]);
    if( range1 == 1 )
        _ghosts[0] = _pacman;
    else if( range2 == 1 )
        _ghosts[1] = _pacman;
    else
    {
        if(_selected == false)
        {
            parity = parityTest(_pacman);
            if(range1 < range2)
                _runner = 0;
            else if(range1 > range2)
                _runner = 1;
            else // alors les distances sont égales
            {
                if(parityTest(_ghosts[0]) != parity)
                    _runner = 0;
                else
                    _runner = 1;
            }
            _selected = true;
            if(parityTest(_ghosts[_runner]) != parity)
                calculateMovement(_runner);
            else
            {
                if(_runner == 1)
                    calculateMovement(0);
                else
                    calculateMovement(1);
            }
        }
        else
            calculateMovement(_runner);
    }
}
