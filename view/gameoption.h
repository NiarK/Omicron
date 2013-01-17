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

enum class TesseractDisplay
{
    IN_3D,
    IN_2D
};

class GameOption
{
public:
    GameOption();
    GameOption(Field f, GameType gt, PacmanAI ai);

    Field getField();
    void setField(Field f);

    GameType getGameType();
    void setGameType(GameType gt);

    PacmanAI getPacmanAI();
    void setPacmanAI(PacmanAI ai);

    unsigned int getWidth() const;
    void setWidth(unsigned int w);

    unsigned int getHeight() const;
    void setHeight(unsigned int h);

    void setDisplay(TesseractDisplay d);
    TesseractDisplay getDisplay() const;

private:
    Field _field;
    GameType _gameType;
    PacmanAI _pacmanAI;

    unsigned int _width;
    unsigned int _height;

    TesseractDisplay _display;
};

#endif // GAMEOPTION_H
