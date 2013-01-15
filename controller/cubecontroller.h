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
    virtual void movePacman();
    virtual void moveGhost();
    virtual int range(int pos1,int pos2, int dist,int dimension);
    virtual int rangeMin(int pacman);
};

#endif // CUBECONTROLLER_H
