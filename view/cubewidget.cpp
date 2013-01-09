#include "cubewidget.h"

CubeWidget::CubeWidget(QWidget *parent) :
    Game(parent)
{

    this->setController(new CubeController());
}

void CubeWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{
    for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * Game::SPACING * CubeWidget::SPACING, i / 2 * Game::SPACING * CubeWidget::SPACING);
    }

    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * Game::SPACING * CubeWidget::SPACING / 2 + Game::SPACING * CubeWidget::SPACING / 4 ,
                             i / 2 * Game::SPACING * CubeWidget::SPACING / 2 + Game::SPACING * CubeWidget::SPACING / 4 );
    }
}
