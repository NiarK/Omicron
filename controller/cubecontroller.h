#ifndef CUBECONTROLLER_H
#define CUBECONTROLLER_H

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class CubeController : public GameController
{
public:
    CubeController();
    virtual ~CubeController();

    virtual void updatePacman();
    virtual void updateGhost();
private:

};

#endif // CUBECONTROLLER_H
