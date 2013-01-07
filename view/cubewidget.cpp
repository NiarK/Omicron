#include "cubewidget.h"

CubeWidget::CubeWidget(QWidget *parent) :
    Game(parent)
{

    this->setController(new GameController(4, 2));
}

void CubeWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{
    for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * Game::SPACING * 5, i / 2 * Game::SPACING * 5);
    }

    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * Game::SPACING * 3 + Game::SPACING , i / 2 * Game::SPACING * 3 + Game::SPACING );
    }
}
