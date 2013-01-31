#include "donutcontroller.h"

DonutController::DonutController() :
    GameController(std::vector<unsigned int>(2,8), true, 4),
    _width(8),
    _height(8),
    _chase(false),
    _optimumPosition(4,0),
    _ghostPlaced(1),
    _ghostPositionTable(4,0),
    _lastPlayed(0)
{
    this->reset();
}

void DonutController::reset()
{
    GameController::reset();
    //initialisation des paramètres
    _chase = false;
    _ghostPlaced = 1;
    _lastPlayed = 0;

    _optimumPosition.clear();
    _optimumPosition.push_back(0);
    _optimumPosition.push_back(0);
    _optimumPosition.push_back(0);
    _optimumPosition.push_back(0);

    _ghostPositionTable.clear();
    _ghostPositionTable.push_back(0);
    _ghostPositionTable.push_back(0);
    _ghostPositionTable.push_back(0);
    _ghostPositionTable.push_back(0);

    _optimumPosition[0] = _ghosts[0];
    _optimumPosition[0] = _ghosts[this->pivot()];

    std::vector<unsigned int> ghostUnplaced;
    std::vector<unsigned int> positionUnused;

    unsigned int opSize = _optimumPosition.size();
    unsigned int ghostNumber = _ghosts.size();

    // Calcule des position optimales
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

    // on crée un tableau pour savoir quels ghosts on doit déplacer pour arriver à la position voulue
    for(unsigned int g = 0; g < ghostNumber; ++g)
    {
        bool isPlaced = false;
        unsigned int op;

        for(op = 0; op < opSize && !isPlaced; ++op)
        {
            isPlaced |= ( _ghosts[g] == _optimumPosition[op] );
        }
        if( !isPlaced )
        {
            ghostUnplaced.push_back(g);
        }
    }

    // on crée un tableau contenant les positions que les ghosts à déplacer doivent atteindre
    for(unsigned int op = 0; op < opSize; ++op)
    {
        bool isPlaced = false;
        unsigned int g;

        for(g = 0; g < ghostNumber && !isPlaced; ++g)
        {
            isPlaced |= ( _ghosts[g] == _optimumPosition[op] );
        }
        if( !isPlaced )
        {
            positionUnused.push_back(op);
        }
        else if(isPlaced)
        {
            _ghostPositionTable[op] = g - 1;
        }
    }



    unsigned int guSize;
    unsigned int puSize = positionUnused.size();
    unsigned int r;
    unsigned int rangeMin, opti;
    // On attribut le bon ghost à la position qu'il doit rejoindre dans les pivots
    for( unsigned int pu = 0; pu < puSize; ++pu )
    {
        guSize = ghostUnplaced.size();
        rangeMin = this->getVertexNumber();
        for( unsigned int gu = 0; gu < guSize; ++gu){
            r = range(_optimumPosition[positionUnused[pu]],_ghosts[ghostUnplaced[gu]]);
            if(r < rangeMin)
            {
                rangeMin = r;
                opti = gu;
            }
        }
        _ghostPositionTable[positionUnused[pu]] = ghostUnplaced[opti];

        unsigned int temp = ghostUnplaced[opti];
        ghostUnplaced[opti] = ghostUnplaced[guSize-1];
        ghostUnplaced[guSize-1] = temp;

        ghostUnplaced.pop_back();
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
    // Si la distance calculée est supérieure à la moitié, alors il est plus
    // rapide de passer par l'extérieur de la map
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
    unsigned int currentRange = 0, minRange, maxRange = 0, vertexNumber = this->getVertexNumber();

    std::vector<unsigned int> edges = this->getEdges(_pacman);

    unsigned int edgeNumber = edges.size();
    unsigned int ghostNumber = _ghosts.size();
    //Parcourt des différents edges, ça vas sur celui qui est le moins proche des gendarmes
    for(unsigned int e = 0; e < edgeNumber; ++e)
    {
        minRange = vertexNumber;
        for(unsigned int g = 0; g < ghostNumber; ++g)
        {
            currentRange = this->range(edges[e], _ghosts[g]);
            if(currentRange < minRange)
            {
                minRange = currentRange;
            }
        }
        if(minRange > maxRange)
        {
            maxRange = minRange;
            _pacman = edges[e];
        }
    }

}

bool DonutController::isInPacmanDiagonal(unsigned int vertex)
{
    // si il est à deux de distance et qu'il est pas dans la même ligne ou même colonne
    // alors il est en diagonale directe
    if(range(vertex,_pacman) == 2
            && _pacman % _width != vertex % _width
            && _pacman / _width != vertex / _width)
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

    // gestion de focus par rapport aux ghosts déjà en place
    if( ! _chase )
    {
        // Si le ghost est déjà placé
        while(_ghostPlaced < _ghostPositionTable.size() && _optimumPosition[_ghostPlaced] == _ghosts[_ghostPositionTable[_ghostPlaced]])
        {
            ++_ghostPlaced;
        }

        if(_ghostPlaced == ghostNumber)
        {
            _chase = true;
        }
    }

    unsigned int minRange = this->getVertexNumber();
    unsigned int range;
    // gestion de deplacement
    if( !_chase )
    {
        // Déplacement des ghosts vers les positions du pivot
        std::vector<unsigned int> edges = this->getEdges(_ghosts[_ghostPositionTable[_ghostPlaced]]);
        unsigned int size = edges.size();
        bool isAnOccupedPosition;

        for(unsigned int e = 0; e < size; ++e)
        {
            range = this->range(edges[e], _optimumPosition[_ghostPlaced]);
            isAnOccupedPosition = false;

            for(unsigned int g = 0; g < ghostNumber && !isAnOccupedPosition; ++g)
            {
                isAnOccupedPosition = ( edges[e] == _ghosts[g] );
            }
            if(minRange > range && ! isAnOccupedPosition)
            {
                minRange = range;
                _ghosts[_ghostPositionTable[_ghostPlaced]] = edges[e];
            }
        }
    }
    else
    {
        unsigned int minGhost = ghostNumber;
        unsigned int rangeLast = 0;
        bool moved = false;
        bool diagoPossible = false;
        minRange = this->getVertexNumber();
        // permet d'obtenir le ghost le plus près sans qu'il soit à deux de distance du pacman
        for(unsigned int g = 0; g < ghostNumber; ++g)
        {
            range = this->range(_ghosts[g], _pacman);
            if(minRange >= range && g != _lastPlayed && range > 2)
            {
                // On test si il peut se mettre dans la diagonale du pacman ou non
                if(range == 3 && ( _ghosts[g] % _width != _pacman % _width)
                        && ( _ghosts[g] / _width != _pacman / _width))
                {
                    diagoPossible = true;
                }
                unsigned int r = 0;
                r = this->range(_ghosts[_lastPlayed],_ghosts[g]);
                // On garde le plus proche du pacman et si il y en a à même distance
                // on prend le plus loin du dernier ghost à avoir joué
                if(minRange > range || r > rangeLast)
                {
                    minRange = range;
                    minGhost = g;
                    rangeLast = r;
                    moved = true;
                }
            }
        }
        unsigned int rangeLastPacman = this->range(_ghosts[_lastPlayed], _pacman);
        // Si aucun n'a bougé c'est qu'ils sont tous à deux du pacman donc on bouge le last
        if(!moved)
        {
            minRange = rangeLastPacman;
            minGhost = _lastPlayed;
        }
        // Si aucun autre ne peut se mettre en diagonale et que le last peut
        // il le fait
        if(!diagoPossible && rangeLastPacman == 3 && ( _ghosts[_lastPlayed] % _width != _pacman % _width)
                && ( _ghosts[_lastPlayed] / _width != _pacman / _width))
        {
            minRange = rangeLastPacman;
            minGhost = _lastPlayed;
        }


        std::vector<unsigned int> edges = this->getEdges(_ghosts[minGhost]);
        unsigned int size = edges.size();
        moved = false;

        // Parcourt des possibilitées (on stop dès qu'on a la diagonale)
        for(unsigned int e = 0; e < size && moved == false; ++e)
        {
            // Si la case est dans la diagonale direct du pacman il y va
            if(isInPacmanDiagonal(edges[e]))
            {
                _ghosts[minGhost] = edges[e];
                moved = true;
            }
        }
        // Parcourt des possibilitées siaucun n'est en diagonale
        for(unsigned int e = 0; e < size && moved == false; ++e)
        {
            // On calcule la distance du pacman à la possibilitée
            range = this->range(edges[e], _pacman);
            // pour calculer si on est dans la diagonale (pas forcément collée)
            int w = (int)(edges[e] % _width) - (int)(_pacman % _width);
            int h = (int)(edges[e] / _width) - (int)(_pacman / _width);
            w = abs(w);
            h = abs(h);
            float val = (float) w / (float) h ;
            //On met le ghost dans la position si c'est plus proche qu'avant
            if(minRange > range)
            {
                _ghosts[minGhost] = edges[e];
                // on arrête la boucle que si c'est dans la diagonale, sinon on test quand même les autres
                if( val == 1 )
                    moved = true;
            }
        }

        _lastPlayed = minGhost;
    }
}

unsigned int DonutController::pivot()
{
    unsigned int ghostNumber = _ghosts.size();

    for(unsigned int g = 0; g < ghostNumber; ++g)
    {
        // Il n'est pas utile de parcourir tous les ghosts ici, seulement ceux qui n'ont pas encore
        // été testé
        for(unsigned int gh = g + 1; gh < ghostNumber; ++gh)
        {
            bool sameLine = ( _ghosts[g] / _width == _ghosts[gh] / _width );
            bool sameColumn = ( _ghosts[g] % _width == _ghosts[gh] % _width );

            bool rangeLine4 = ( abs( (int)(_ghosts[g] % _width) - (int)(_ghosts[gh] % _width) ) == 4 );
            bool rangeColumn4 = ( abs( (int)(_ghosts[g] / _width) - (int)(_ghosts[gh] / _width) ) == 4 );
            // Si deux au moins sont dans les conditions on met le pivot sur l'un des deux.
            // On peut savoir facilement si ils le sont avec le test suivant (il vérifie
            // les trois autres positions)
            if( ( rangeLine4 || sameLine ) && ( rangeColumn4 || sameColumn ) )
            {
                return g;
            }
        }
    }

    return 0;
}
