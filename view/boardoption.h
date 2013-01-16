#ifndef BOARDOPTION_H
#define BOARDOPTION_H

// --- Omicron --- //
#include "view/gameoption.h"

class BoardOption : public GameOption
{
public:
    BoardOption(Field f, GameType gt, PacmanAI ai, unsigned int w, unsigned int h);

    unsigned int getWidth();
    void setWidth(unsigned int w);
    unsigned int getHeight();
    void setHeight(unsigned int h);

private:
    unsigned int _width;
    unsigned int _height;
};

#endif // BOARDOPTION_H
