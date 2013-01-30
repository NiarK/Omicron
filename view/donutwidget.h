#ifndef DONUTWIDGET_H
#define DONUTWIDGET_H

// --- Oicron --- //
#include "view/gamewidget.h"
#include "controller/donutcontroller.h"
#include "view/gameoption.h"

class DonutWidget : public GameWidget
{
    Q_OBJECT
public:
    explicit DonutWidget(const GameOption & option, QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;

    virtual void linkVertex(QGraphicsScene * _scene,
                            const std::vector<QGraphicsEllipseItem*> & vertex) const;
    
signals:
    
public slots:

private:
    unsigned int _width;
    unsigned int _height;
    
};

#endif // DONUTWIDGET_H
