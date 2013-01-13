#ifndef BOARD_H
#define BOARD_H

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class BoardController : public GameController
{
public:
    BoardController(unsigned int width, unsigned int height);
    virtual ~BoardController();


    // --- Accessor --- //
    unsigned int getWidth();
    unsigned int getHeight();

protected:

private:
    virtual void movePacman();
    virtual void moveGhost();
    std::vector<unsigned int> createSizeByDimensionVector(unsigned int width, unsigned int height);

    unsigned int _width;
    unsigned int _height;
};

#endif // BOARD_H
