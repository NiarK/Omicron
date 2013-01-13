#include "tesseractwidget.h"

TesseractWidget::TesseractWidget(QWidget *parent) :
    GameWidget(parent)
{
    this->setController(new TesseractController());
}

void TesseractWidget::positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const
{
    QTime t = QTime::currentTime();
    if(t.second() % 2 == 0)
    {
        unsigned int spacing = GameWidget::SPACING * 7;
        unsigned int offset = GameWidget::SPACING * 4.8;

        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacing + offset,
                                 i / 2 * spacing);
        }

        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacing,
                                 i / 2 * spacing + offset);
        }

        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacing + offset * 2,
                                 i / 2 * spacing + offset);
        }

        for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacing + offset,
                                 i / 2 * spacing + offset * 2);
        }
    }
    else
    {
        //*
        float spacingRatio = 1.3;
        unsigned int offsetD3 = GameWidget::SPACING * 1.4;
        unsigned int offsetD4 = offsetD3 * 3;
        unsigned int ratioD3 = 4;
        unsigned int ratioD4 = ratioD3 * 3;
        unsigned int spacingD3 = GameWidget::SPACING * ratioD3;
        unsigned int spacingD4 = GameWidget::SPACING * ratioD4;
        unsigned int internalOffset = ( spacingD4 - spacingD3
                                      + offsetD4 - offsetD3 )
                                      / 2;

        // affichage du petit cube
        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacingD3 + internalOffset * spacingRatio + offsetD3,
                                 i / 2 * spacingD3 + internalOffset);
        }

        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacingD3 + internalOffset * spacingRatio,
                                 i / 2 * spacingD3 + internalOffset + offsetD3);
        }

        // affichage du gros cube
        for(int i = 0; i < 4 && vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacingD4 * spacingRatio + offsetD4,
                                 i / 2 * spacingD4);
        }

        for(int i = 0; vertexIt != endVertexIt; ++vertexIt, ++i)
        {
            (*vertexIt)->setPos( i % 2 * spacingD4 * spacingRatio,
                                 i / 2 * spacingD4 + offsetD4);
        }
        //*/
    }
}
