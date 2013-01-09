#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

// --- Include Omicron --- //
#include "view/game.h"
#include "controller/cubecontroller.h"

class CubeWidget : public Game
{
    Q_OBJECT
public:
    const unsigned int SPACING = 30;

    explicit CubeWidget(QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:
    
};

#endif // CUBEWIDGET_H
