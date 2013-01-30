#include "boardwidget.h"

BoardWidget::BoardWidget(const GameOption & option, QWidget *parent) :
    GameWidget(option, parent),
    _width(option.getWidth()),
    _height(option.getHeight())
{
    this->setController(new BoardController(_width, _height));
}

void BoardWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                 std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{


    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % _width * (GameWidget::SPACING + GameWidget::RADIUS), i / _width * (GameWidget::SPACING + GameWidget::RADIUS) );
    }
}


