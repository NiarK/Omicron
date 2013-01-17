#ifndef CUBEPROPERTYWIDGET_H
#define CUBEPROPERTYWIDGET_H

// --- Qt --- //
#include <QWidget>

// --- Omicron --- //
#include "view/propertywidget.h"
#include "view/gameoption.h"

class CubePropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit CubePropertyWidget(GameOption & option, QWidget *parent = 0);

    virtual void updateIHM();
    virtual void updateOption();
    
signals:
    
public slots:
    
};

#endif // CUBEPROPERTYWIDGET_H
