#ifndef GAMEOPTION_H
#define GAMEOPTION_H

enum class Field
{
    BOARD,
    DONUT,
    CUBE,
    TESSERACT
};

enum class GameType
{
    AI,
    GHOST_PLAYER,
    PACMAN_PLAYER
};

enum class PacmanAI
{
    RANDOM,
    WISE
};

class GameOption
{
public:
    GameOption(Field f, GameType gt, PacmanAI ai);

    Field getField();
    void setField(Field f);

    GameType getGameType();
    void setGameType(GameType gt);

    PacmanAI getPacmanAI();
    void setPacmanAI(PacmanAI ai);

private:
    Field _field;
    GameType _gameType;
    PacmanAI _pacmanAI;
};

#endif // GAMEOPTION_H
