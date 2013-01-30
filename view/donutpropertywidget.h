#ifndef DONUTPROPERTYWIDGET_H
#define DONUTPROPERTYWIDGET_H

// --- Omicron --- //
#include "view/propertywidget.h"
#include "view/gameoption.h"

class DonutPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit DonutPropertyWidget(GameOption &option, QWidget *parent);
    virtual ~DonutPropertyWidget();

    virtual void updateIHM();
    virtual void updateOption();
    
signals:
    
public slots:
    
};

#endif // DONUTPROPERTYWIDGET_H
