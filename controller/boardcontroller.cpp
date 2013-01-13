#include "controller/boardcontroller.h"
#include <cmath>

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

int BoardController::range(int pos1, int pos2){
    int dist=0;
    int temp=0;
    int l = getWidth();
    dist=pos1%l-pos2%l;
    if(dist<0)
        dist=dist*-1;
    temp=pos1/l-pos2/l;
    if(temp<0)
        temp=temp*-1;
    return dist+temp;
}

std::vector<unsigned int> BoardController::createSizeByDimensionVector(unsigned int width, unsigned int height)
{
    std::vector<unsigned int> sizeByDimension;

    sizeByDimension.push_back(width);
    sizeByDimension.push_back(height);

    return sizeByDimension;
}

bool BoardController::parityTest(int nb){
    nb=nb/8+nb%8;
    if(nb%2)
        return true;
    else return false;
}

void BoardController::calculateMovement(int nb){
    //Définition des variables
    int vertical;
    int verticalabs;
    int horizontal;
    int horizontalabs;
    //calcul du vertical
    vertical=_ghosts[nb]/8-_pacman/8;
    if(vertical<0)// on passe l'horizontal en absolu pour le comparer
        verticalabs=-vertical;
    else
        verticalabs=vertical;
    //calcul de l'horizontal
    horizontal=_ghosts[nb]%8-_pacman%8;
    if(horizontal<0)// on passe le vertical en absolu pour le comparer
        horizontalabs=-horizontal;
    else
        horizontalabs=horizontal;
    //On compare les valeurs
    //si il y a plus de distance dans la vertical on va rapprocher
    //dans la verticale pour se rapprocher de la diagonale
    //sinon on se rapproche dans l'horizontale pour se rapprocher
    //de la diagonale
    if(verticalabs>horizontalabs){
        //si vertical est positif alors le pacman est au dessus du ghost
        //il faut donc faire remonter le ghost
        if(vertical>0){
            _ghosts[nb]-=8;
        }
        else{
            _ghosts[nb]+=8;
        }
    }
    else{
        //si horizontal est positif alors le pacman est à gauche du ghost
        //il faut donc faire partir à gauche le ghost
        if(horizontal>0){
            _ghosts[nb]-=1;
        }
        else{
            _ghosts[nb]+=1;
        }
    }
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
    bool parity;
    int range1 = range(_pacman, _ghosts[0]);
    int range2 = range(_pacman, _ghosts[1]);
    if(range1==1)
        _ghosts[0]=_pacman;
    else if(range2==1)
        _ghosts[1]=_pacman;
    else{
        parity=parityTest(_pacman);
        if(range1<range2 && parityTest(_ghosts[0])!=parity){
            calculateMovement(0);
        }
        else{
            if(range1>=range2 && parityTest(_ghosts[1])!=parity){
                calculateMovement(1);
            }
            else{
                if(range1<range2 && parityTest(_ghosts[0])==parity)
                    calculateMovement(1);
                else
                    calculateMovement(0);
            }
        }
    }
}
