#include "cubewidget.h"

CubeWidget::CubeWidget(const GameOption &option, QWidget *parent) :
    GameWidget(option, parent)
{
    this->setController(new CubeController());
}

void CubeWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{
    /*for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * GameWidget::SPACING * 10, i / 2 * GameWidget::SPACING * 10);
    }

    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * GameWidget::SPACING * 5 / 2 + GameWidget::SPACING * 5 / 4 ,
                             i / 2 * GameWidget::SPACING * 5 / 2 + GameWidget::SPACING * 5 / 4 );
    }*/

    unsigned int offset = GameWidget::SPACING * 4;
    for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * GameWidget::SPACING * 10 + offset, i / 2 * GameWidget::SPACING * 10);
    }

    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % 2 * GameWidget::SPACING * 10, i / 2 * GameWidget::SPACING * 10 + offset);
    }
}
