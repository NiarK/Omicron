#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// --- Include Qt --- //
#include <QTime>

// --- Include std --- //
#include <vector>
#include <stdexcept>

// --- Include Omicron --- //
#include "model/hypercube.h"

/*
enum class Actor
{
    PACMAN,
    GHOST
};
//*/

class GameController
{
public:
    GameController(const std::vector<unsigned int> & sizeByDimension, bool infinite, unsigned int ghost);
    virtual ~GameController();

    virtual std::vector<unsigned int>   getEdges(unsigned int vertex)   const;
    virtual unsigned int                getVertexNumber()               const;
            unsigned int                getPacman()                     const;
            std::vector<unsigned int>   getGhost()                      const;
            unsigned int                getMovementCounter()            const;

            void                        nextMove();

protected:
    HyperCube * getAdjacencyMatrix();

    unsigned int _pacman;
    std::vector<unsigned int> _ghosts;

private:
    virtual void movePacman() = 0;
    virtual void moveGhost() = 0;
    unsigned int generatePosition();

    bool _pacmanMoved;
    unsigned int _movementCounter;

    HyperCube * _matrix;
    //unsigned int _vertexNumber;
};

#endif // GAMECONTROLLER_H
