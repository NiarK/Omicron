#ifndef TESSERACTOPTION_H
#define TESSERACTOPTION_H

// --- Omicron --- //
#include "view/gameoption.h"

enum class Display
{
    IN_3D,
    IN_2D
};

class TesseractOption : public GameOption
{
public:
    TesseractOption(Field f, GameType gt, PacmanAI ai, Display d);

    void setDisplay(Display d);
    Display getDisplay();

private:
    Display _display;
};

#endif // TESSERACTOPTION_H
