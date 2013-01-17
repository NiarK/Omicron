#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

// --- Include Omicron --- //
#include "view/gamewidget.h"
#include "controller/cubecontroller.h"
#include "view/gameoption.h"

class CubeWidget : public GameWidget
{
    Q_OBJECT
public:
    const unsigned int SPACING = 30;

    explicit CubeWidget(const GameOption & option, QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;

signals:
    
public slots:
    
};

#endif // CUBEWIDGET_H
