#ifndef DONUTCONTROLLER_H
#define DONUTCONTROLLER_H

// --- std --- //
#include <cmath>

// --- Omicron --- //
#include "controller/gamecontroller.h"

class DonutController : public GameController
{
public:
    DonutController();
    virtual ~DonutController();

    virtual unsigned int range(unsigned int v1, unsigned int v2);

private:

    /**
     * @brief diagonalTest test si la case passée en paramètre est dans la diagonale (sans case entre) du pacman
     * @param place numéro case à tester
     * @return vrai si c'est dans la case en diagonale
     */
    bool diagonalTest(unsigned int place);

    virtual void movePacman();
    virtual void moveGhost();

    unsigned int _width;
    unsigned int _height;

    /**
     * @brief _chase Si les ghosts ne chassent pas, ils doivent se mettre en position optimale.
     */
    bool _chase;

    /**
     * @brief _pivot Tableau contenant les positions optimales
     */
    std::vector<unsigned int> _optimumPosition;

    /**
     * @brief _ghostPlaced Nombre de ghosts placé en position optimale.
     */
    unsigned int _ghostPlaced;

    std::vector<unsigned int> _ghostPositionTable;

    unsigned int _lastPlayed;
};

#endif // DONUTCONTROLLER_H
