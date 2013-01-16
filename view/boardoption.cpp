#include "boardoption.h"

BoardOption::BoardOption(Field f, GameType gt, PacmanAI ai, unsigned int w, unsigned int h) :
    GameOption(f, gt, ai),
    _width(w),
    _height(h)
{
}

unsigned int BoardOption::getWidth()
{
    return _width;
}

void BoardOption::setWidth(unsigned int w)
{
    _width = w;
}

unsigned int BoardOption::getHeight()
{
    return _height;
}

void BoardOption::setHeight(unsigned int h)
{
    _height = h;
}
