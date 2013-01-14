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
    virtual int rangeMin(int value);
    virtual bool boardTest(int pos);
    virtual int range(int pos1, int pos2);
    virtual bool parityTest(int nb);
    virtual void calculateMovement(int nb);
    std::vector<unsigned int> createSizeByDimensionVector(unsigned int width, unsigned int height);

    unsigned int _width;
    unsigned int _height;
};

#endif // BOARD_H
