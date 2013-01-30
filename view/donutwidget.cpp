#include "donutwidget.h"

DonutWidget::DonutWidget(const GameOption & option, QWidget *parent) :
    GameWidget(option, parent),
    _width(8),
    _height(8)
{
    this->setController(new DonutController());
}

void DonutWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                 std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{
    for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
    {
        (*vertexIt)->setPos( i % _width * (GameWidget::SPACING + GameWidget::RADIUS), i / _width * (GameWidget::SPACING + GameWidget::RADIUS) );
    }
}

void DonutWidget::linkVertex(QGraphicsScene * _scene,
                             const std::vector<QGraphicsEllipseItem*> & vertex) const
{
    unsigned int spacing = GameWidget::SPACING + GameWidget::RADIUS;

    QPen pen( QColor( 100,0,0 ) );

    GameWidget::linkVertex(_scene, vertex);

    unsigned int vertexNumber = vertex.size();
    for(unsigned int v = 0; v != vertexNumber; ++v)
    {
        // en haut !
        if(v / _width == 0)
        {
            QPointF p = vertex[v]->pos();
            _scene->addLine( p.x(), p.y(), p.x(), p.y() - spacing, pen );
        }

        // En bas !
        if(v / _width == _height - 1)
        {
            QPointF p = vertex[v]->pos();
            _scene->addLine( p.x(), p.y(), p.x(), p.y() + spacing, pen );
        }

        // a droite !
        if(v % _width == _width - 1)
        {
            QPointF p = vertex[v]->pos();
            _scene->addLine( p.x(), p.y(), p.x() + spacing, p.y(), pen );
        }

        // a gauche !
        if(v % _width == 0)
        {
            QPointF p = vertex[v]->pos();
            _scene->addLine( p.x(), p.y(), p.x() - spacing, p.y(), pen );
        }
    }
}
