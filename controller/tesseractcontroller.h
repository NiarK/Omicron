#ifndef TESSERACTCONTROLLER_H
#define TESSERACTCONTROLLER_H

#include "controller/gamecontroller.h"

class TesseractController : public GameController
{
public:
    TesseractController();
    virtual ~TesseractController();

private:
    /**
     * @brief movePacman Gère les mouvement du pacman.
     */
    virtual void movePacman();

    /**
     * @brief moveGhost Gère les mouvement des ghosts.
     */
    virtual void moveGhost();
};

#endif // TESSERACTCONTROLLER_H
