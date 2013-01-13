#ifndef TESSERACTCONTROLLER_H
#define TESSERACTCONTROLLER_H

#include "controller/gamecontroller.h"

class TesseractController : public GameController
{
public:
    TesseractController();
    virtual ~TesseractController();

private:
    virtual void movePacman();
    virtual void moveGhost();
};

#endif // TESSERACTCONTROLLER_H
