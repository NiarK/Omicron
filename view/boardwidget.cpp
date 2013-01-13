#include "boardwidget.h"

BoardWidget::BoardWidget(unsigned int width, unsigned int height, QWidget *parent) :
    GameWidget(parent),
    _width(width),
    _height(height)
{
    this->setController(new BoardController(width, height));

    /*std::vector<QGraphicsEllipseItem*>::iterator it = this->getVertexIterator();
    std::vector<QGraphicsEllipseItem*>::iterator end = this->getVertexEndIterator();

    for(int i = 0; it != end; ++it, ++i)
    {
        (*it)->setPos( i % width * Game::SPACING, i / width * Game::SPACING );
    }*/
}

/*void BoardWidget::initializeVertex(const std::vector<QGraphicsEllipseItem *> &vertex) const
{
    for(unsigned int y = 0; y < _board->getHeight(); ++y)
    {
        for(unsigned int x = 0; x < _board->getWidth(); ++x)
        {
            QGraphicsEllipseItem * ell = new QGraphicsEllipseItem( -10, -10, 20, 20 );
            ell->setPos(x*40,y*40);
            ell->setZValue(y);
            ell->setPen( QPen( QColor( "red" ) ) );

            _vertex.push_back( ell );
            _scene->addItem( _vertex.back() );
        }
    }

    unsigned int vertexNumber = vertex.size();
    for(unsigned int i = 0; i < vertexNumber; ++i)
    {
        vertex[i]->setPos( i % 10, i / 10 );
    }

    std::cout << "board" << std::endl;
}*/

void BoardWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                 std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{


    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % _width * (GameWidget::SPACING + GameWidget::RADIUS), i / _width * (GameWidget::SPACING + GameWidget::RADIUS) );
    }
}


