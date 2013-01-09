#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdexcept>

#include "model/hypercube.h"

class GameController
{
public:
    GameController(unsigned int width, unsigned int height);
    ~GameController();

    // --- Accessor --- //
    HyperCube * getAdjacencyMatrix() const;
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getVertexNumber();
    std::vector<unsigned int> getEdge(unsigned int vertex);

private:
    unsigned int _width;
    unsigned int _height;
    HyperCube * _matrix;
};

#endif // BOARD_H
