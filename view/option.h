#ifndef OPTION_H
#define OPTION_H


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

#endif // OPTION_H
