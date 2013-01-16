#include "gameoption.h"

GameOption::GameOption(Field f, GameType gt, PacmanAI ai) :
    _field(f),
    _gameType(gt),
    _pacmanAI(ai)
{

}


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
