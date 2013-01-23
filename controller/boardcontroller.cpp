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
    GameController::reset();

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

unsigned int BoardController::calculateEsperance(int vertical, int horizontal, int numGhost)
{
    if(vertical < 0)
    {
        vertical *= -1;
    }
    if(horizontal < 0)
    {
        horizontal *= -1;
    }
    bool parityG = parityTest(_ghosts[numGhost]);
    bool parityP = parityTest(_pacman);
    int par;
    if(parityG == parityP)
    {
        par = 1;
    }
    else
    {
        par = 0;
    }
    return vertical + horizontal + par;
}

unsigned int BoardController::esperance(int place, unsigned int GhostNumber)
{
    int vert, hori;
    unsigned int w = getWidth();

    if(place == 0) // haut droite
    {
        vert = _ghosts[GhostNumber] / w - 1;
        hori = _ghosts[GhostNumber] % w - 6;
        return calculateEsperance(vert, hori, GhostNumber);
    }
    else if(place == 1) // haut gauche
    {
        vert = _ghosts[GhostNumber] / w - 1;
        hori = _ghosts[GhostNumber] % w - 1;
        return calculateEsperance(vert, hori, GhostNumber);
    }
    else if(place == 2) // bas gauche
    {
        vert = _ghosts[GhostNumber] / w - 6;
        hori = _ghosts[GhostNumber] % w - 1;
        return calculateEsperance(vert, hori, GhostNumber);
    }
    else // bas droite
    {
        vert = _ghosts[GhostNumber] / w - 6;
        hori = _ghosts[GhostNumber] % w - 6;
        return calculateEsperance(vert, hori, GhostNumber);
    }
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
                _selected = false;
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
                _selected = false;
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
            if( _ghosts[nb] - 1 == _ghosts[nb2] )
            {
                _selected = false;
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
            if( _ghosts[nb] + 1 == _ghosts[nb2] )
            {
                _selected = false;
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
    else if( value == (int)-w )
        test = _pacman >= w;
    else if( value == (int)w )
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

void BoardController::movePacman()
{
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
}

unsigned int BoardController::bestDiagonalGhost()
{
    unsigned int width = this->getWidth();
    unsigned int xp = _pacman % width;
    unsigned int yp = _pacman / width;
    unsigned int xg, yg;
    int xgp, ygp;
    int ratio;
    unsigned int ghost = 0;
    int bestRatio = 0;

    unsigned int size = _ghosts.size();
    for(unsigned int i = 0; i < size; ++i)
    {
        xg = _ghosts[i] % width;
        yg = _ghosts[i] / width;
        xgp = xg - xp;
        if(xgp < 0)
        {
            xgp *= -1;
        }
        ygp = yg - yp;
        if(ygp < 0)
        {
            ygp *= -1;
        }

        ratio = xgp - ygp;
        if(ratio < 0)
        {
            ratio = -ratio;
        }

        if(bestRatio > ratio || i == 0)
        {
            bestRatio = ratio;
            ghost = i;
        }
    }

    return ghost;
}

unsigned int BoardController::abs(int nb)
{
    if(nb < 0)
        nb *= -1;
    return nb;
}

std::vector<int> BoardController::lookEsperance(unsigned int ghostNumber)
{
    std::vector<int> tabRet;
    unsigned int w = getWidth();
    int horiG = _ghosts[ghostNumber] % w;
    int horiP = _pacman % w;
    int vertG = _ghosts[ghostNumber] / w;
    int vertP = _pacman / w;
    int vertGP = vertG - vertP;
    int horiGP = horiG - horiP;
    int espe1, espe2;
    int test;
    test = abs(vertGP) - abs(horiGP);
    if(test > 0)// pacman dans le sablier vertical
    {
        if(vertGP < 0) // pacman en dessous
        {
            espe1 = esperance(2,ghostNumber);
            espe2 = esperance(3,ghostNumber);
        }
        else
        {
            espe1 = esperance(0,ghostNumber);
            espe2 = esperance(1,ghostNumber);
        }
    }
    else if(test < 0)
    {
        if(horiGP < 0) // pacman à droite
        {
            espe1 = esperance(0,ghostNumber);
            espe2 = esperance(3,ghostNumber);
        }
        else
        {
            espe1 = esperance(1,ghostNumber);
            espe2 = esperance(2,ghostNumber);
        }
    }
    else // alors dans la diago
    {
        if(horiGP < 0) // pacman à droite
        {
            if(vertGP < 0) // pacman en dessous
            {
                espe1 = esperance(3,ghostNumber);
            }
            else
            {
                espe1 = esperance(0,ghostNumber);
            }
            espe2 = -1;
        }
        else
        {
            if(vertGP < 0) // pacman en dessous
            {
                espe1 = esperance(2,ghostNumber);
            }
            else
            {
                espe1 = esperance(1,ghostNumber);
            }
            espe2 = -1;
        }
    }
    tabRet.push_back(espe1);
    tabRet.push_back(espe2);
    return tabRet;
}

void BoardController::moveGhost()
{
    std::vector<int> espeG0;
    std::vector<int> espeG1;

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
            espeG0 = lookEsperance(0);
            espeG1 = lookEsperance(1);
            if(espeG0[1] == -1)
            {
                if(espeG0[0] < espeG1[0] || espeG0[0] < espeG1[1])
                    _runner = 0;
                else
                    _runner = 1;
            }
            else if(espeG1[1] == -1)
            {
                if(espeG1[0] < espeG0[0] || espeG1[0] < espeG0[1])
                    _runner = 1;
                else
                    _runner = 0;
            }
            else
            {
                if(espeG0[0] + espeG0[1] < espeG1[0] + espeG1[1])
                    _runner = 0;
                else if(espeG0[0] + espeG0[1] > espeG1[0] + espeG1[1])
                    _runner = 1;
                else
                    _runner = bestDiagonalGhost();
            }
            _selected = true;

            if(parityTest(_ghosts[_runner]) != parityTest(_pacman))
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
