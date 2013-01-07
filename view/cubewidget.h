#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include "view/game.h"

class CubeWidget : public Game
{
    Q_OBJECT
public:
    explicit CubeWidget(QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:
    
};

#endif // CUBEWIDGET_H
