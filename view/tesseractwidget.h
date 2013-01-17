#ifndef TESSERACTWIDGET_H
#define TESSERACTWIDGET_H

// --- include Qt --- //
#include <QTime>

// --- Include Omicron --- //
#include "view/gamewidget.h"
#include "controller/tesseractcontroller.h"
#include "view/gameoption.h"

class TesseractWidget : public GameWidget
{
    Q_OBJECT
public:
    explicit TesseractWidget(const GameOption &option, QWidget *parent = 0);


    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const;
    
signals:
    
public slots:

private:
    TesseractDisplay _display;
    
};

#endif // TESSERACTWIDGET_H
