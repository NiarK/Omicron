#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

// --- Include Omicron --- //
#include "view/gamewidget.h"
#include "controller/boardcontroller.h"
#include "view/gameoption.h"

class BoardWidget : public GameWidget
{
    Q_OBJECT
public:
    //explicit BoardWidget(unsigned int width, unsigned int height, QWidget *parent = 0);
    explicit BoardWidget(const GameOption & option, QWidget *parent = 0);

    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:

private:
    unsigned int _width;
    unsigned int _height;

    
};

#endif // BOARDWIDGET_H
