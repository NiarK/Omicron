#include "gameoption.h"

GameOption::GameOption() :
    _field(Field::BOARD),
    _gameType(GameType::AI),
    _pacmanAI(PacmanAI::WISE),
    _width(8),
    _height(8),
    _display(TesseractDisplay::IN_3D)
{

}
/*
GameOption::GameOption(Field f, GameType gt, PacmanAI ai) :
    _field(f),
    _gameType(gt),
    _pacmanAI(ai)
{

}
*/

Field GameOption::getField()
{
    return _field;
}

void GameOption::setField(Field f)
{
    _field = f;
}

GameType GameOption::getGameType()
{
    return _gameType;
}

void GameOption::setGameType(GameType gt)
{
    _gameType = gt;
}

PacmanAI GameOption::getPacmanAI()
{
    return _pacmanAI;
}

void GameOption::setPacmanAI(PacmanAI ai)
{
    _pacmanAI = ai;
}


unsigned int GameOption::getWidth() const
{
    return _width;
}

void GameOption::setWidth(unsigned int w)
{
    _width = w;
}

unsigned int GameOption::getHeight() const
{
    return _height;
}

void GameOption::setHeight(unsigned int h)
{
    _height = h;
}

void GameOption::setDisplay(TesseractDisplay d)
{
    _display = d;
}

TesseractDisplay GameOption::getDisplay() const
{
    return _display;
}

