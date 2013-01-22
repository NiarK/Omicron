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
    /*
    unsigned int rangePG0 = _matrix->range( _pacman, _ghosts[0] );
    unsigned int rangePG1 = _matrix->range( _pacman, _ghosts[1] );
//*/
    std::vector<unsigned int> edges = this->getEdges(_pacman);
    unsigned int edgeNumber = edges.size();
    unsigned int secondPossibility = _pacman;

    // on cherche a fuir les ghosts
    for(unsigned int i = 0; i < edgeNumber; ++i)
    {
        unsigned int rangeGE0 = _matrix->range( _ghosts[0], edges[i] );
        unsigned int rangeGE1 = _matrix->range( _ghosts[1], edges[i] );
        /*
        unsigned int rangeGE = rangeGE0 + rangeGE1;
        unsigned int rangePG = rangePG0 + rangePG1;
        //*/

        // on cherche quel noeuds est le plus loin des ghosts
        /*
        if( rangeGE > rangePG )
        {
            _pacman = edges[i];
            return;
        }
        //*/
        if( rangeGE0 > 1 && rangeGE1 > 1 )
        {
            _pacman = edges[i];
            return;
        }

        // on cherche quel noeuds ne se rapproche pas d'un noeud
        else if( secondPossibility == _pacman && rangeGE0 > 0 && rangeGE1 > 0 )
        {
            secondPossibility = edges[i];
        }
    }
    _pacman = secondPossibility;
    return;
}

void TesseractController::moveGhost()
{
    //unsigned int ghostNumber = _ghosts.size();
    unsigned int rangePG0 = _matrix->range( _pacman, _ghosts[0] );
    unsigned int rangePG1 = _matrix->range( _pacman, _ghosts[1] );
    unsigned int rangeGG = _matrix->range( _ghosts[0], _ghosts[1] );

    // test si le pacman est à coté d'un ghost, si oui, on le bouffe !
    if( rangePG0 == 1 )
    {
        _ghosts[0] = _pacman;
        return;
    }
    else if( rangePG1 == 1 )
    {
        _ghosts[1] = _pacman;
        return;
    }
    // on test si les ghosts ont une distance de 3 (de chaque coté d'un cube, distance optimal, pour manger le Pacman),
    // alors on bouge le ghost qui est a une distance différente de 2 du pacman pour l'éloigner de l'autre ghost.
    // Ainsi tous les sommets seront bloqué correctement.
    else if( rangeGG == 3 )
    {
        std::vector<unsigned int> edges;
        unsigned int edgeNumber;

        // si un ghost n'est pas a une distance de 2 du Pacman il faut l'eloigner d'une distance de 4 du ghost
        if( rangePG0 != 2 )
        {
            edges = this->getEdges(_ghosts[0]);
            edgeNumber = edges.size();

            // on cherche quel noeuds adjacent est a une distance de 4 de l'autre ghost
            for(unsigned int i = 0; i < edgeNumber; ++i)
            {
                if( _matrix->range( _ghosts[1], edges[i] ) == 4 )
                {
                    _ghosts[0] = edges[i];
                    return;
                }
            }
        }
        else if( rangePG1 != 2 )
        {
            edges = this->getEdges(_ghosts[1]);
            edgeNumber = edges.size();

            // on cherche quel noeuds adjacent est a une distance de 4 de l'autre ghost
            for(unsigned int i = 0; i < edgeNumber; ++i)
            {
                if( _matrix->range( _ghosts[0], edges[i] ) == 4 )
                {
                    _ghosts[1] = edges[i];
                    return;
                }
            }
        }
    }
    // sinon on ecarte un ghost
    else
    {
        std::vector<unsigned int> edges = this->getEdges(_ghosts[0]);
        unsigned int edgeNumber = edges.size();

        for(unsigned int i = 0; i < edgeNumber; ++i)
        {
            unsigned int rangeGE = _matrix->range( _ghosts[1], edges[i] );
            if( rangeGE > rangeGG || rangeGE == 3 )
            {
                _ghosts[0] = edges[i];
                return;
            }
        }
    }
}
