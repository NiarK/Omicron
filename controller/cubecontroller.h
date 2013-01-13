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
};

#endif // CUBECONTROLLER_H
