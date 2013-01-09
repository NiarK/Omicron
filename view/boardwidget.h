#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

// --- Include Omicron --- //
#include "game.h"
#include "controller/boardcontroller.h"

class BoardWidget : public Game
{
    Q_OBJECT
public:
    explicit BoardWidget(unsigned int width, unsigned int height, QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:

private:
    unsigned int _width;
    unsigned int _height;

    
};

#endif // BOARDWIDGET_H
