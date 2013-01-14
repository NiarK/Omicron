#ifndef TESSERACTWIDGET_H
#define TESSERACTWIDGET_H

// --- include Qt --- //
#include <QTime>

// --- Include Omicron --- //
#include "view/gamewidget.h"
#include "controller/tesseractcontroller.h"

class TesseractWidget : public GameWidget
{
    Q_OBJECT
public:
    explicit TesseractWidget(QWidget *parent = 0);


    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:
    
};

#endif // TESSERACTWIDGET_H
