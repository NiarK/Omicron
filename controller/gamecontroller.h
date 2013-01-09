#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// --- Include Qt --- //
#include <QTime>

// --- Include std --- //
#include <vector>
#include <stdexcept>

// --- Include Omicron --- //
#include "model/hypercube.h"

class GameController
{
public:
    GameController(const std::vector<unsigned int> & sizeByDimension, bool infinite, unsigned int ghost);
    virtual ~GameController();

    virtual std::vector<unsigned int> getEdges(unsigned int vertex);
    virtual unsigned int getVertexNumber() const;
    unsigned int getPacman() const;
    std::vector<unsigned int> getGhost() const;

    virtual void updatePacman() = 0;
    virtual void updateGhost() = 0;

protected:
    HyperCube * getAdjacencyMatrix();

    unsigned int _pacman;
    std::vector<unsigned int> _ghosts;

private:
    unsigned int generatePosition();

    HyperCube * _matrix;
    unsigned int _vertexNumber;
};

#endif // GAMECONTROLLER_H
