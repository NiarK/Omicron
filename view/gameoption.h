#ifndef GAMEOPTION_H
#define GAMEOPTION_H

#include "view/option.h"

class GameOption
{
public:
    GameOption();
    GameOption(Field f, GameType gt, PacmanAI ai);

    Field getField() const;
    void setField(Field f);

    GameType getGameType() const;
    void setGameType(GameType gt);

    PacmanAI getPacmanAI() const;
    void setPacmanAI(PacmanAI ai);

    unsigned int getWidth() const;
    void setWidth(unsigned int w);

    unsigned int getHeight() const;
    void setHeight(unsigned int h);

    TesseractDisplay getDisplay() const;
    void setDisplay(TesseractDisplay d);

private:
    Field _field;
    GameType _gameType;
    PacmanAI _pacmanAI;

    unsigned int _width;
    unsigned int _height;

    TesseractDisplay _display;
};

#endif // GAMEOPTION_H
