#ifndef CUBECONTROLLER_H
#define CUBECONTROLLER_H

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class CubeController : public GameController
{
public:
    CubeController();
    virtual ~CubeController();

private:
    /**
     * @brief moveGhost Gère le mouvement du pacman
     */
    virtual void movePacman();
    /**
     * @brief moveGhost Gère le mouvement des ghosts
     */
    virtual void moveGhost();

    virtual int range(int pos1,int pos2, int dist,int dimension);

    /**
     * @brief rangeMin Calcule quel ghost est le plus proche du pacman.
     * @return
     */
    virtual unsigned int rangeMin(unsigned int _pacman);
};

#endif // CUBECONTROLLER_H
