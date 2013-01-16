#include "tesseractoption.h"

TesseractOption::TesseractOption(Field f, GameType gt, PacmanAI ai, Display d) :
    GameOption(f, gt, ai),
    _display(d)
{
}

void TesseractOption::setDisplay(Display d)
{
    _display = d;
}

Display TesseractOption::getDisplay()
{
    return _display;
}
