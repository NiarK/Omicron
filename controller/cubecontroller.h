#ifndef CUBECONTROLLER_H
#define CUBECONTROLLER_H

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class CubeController : public GameController
{
public:
    CubeController();
    virtual ~CubeController();

    virtual void movePacman();
    virtual void moveGhost();
private:

};

#endif // CUBECONTROLLER_H
