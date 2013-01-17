#ifndef BOARDPROPERTYWIDGET_H
#define BOARDPROPERTYWIDGET_H

// --- Qt --- //
#include <QLineEdit>
#include <QIntValidator>

// --- Omicron --- //
#include "view/propertywidget.h"
#include "view/gameoption.h"

class BoardPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit BoardPropertyWidget(GameOption & option, QWidget *parent = 0);

    virtual void updateIHM();
    
signals:
    
public slots:
    virtual void updateOption();

private:
    GameOption & _option;

    QLineEdit * _txtHeight;
    QLineEdit * _txtWidth;
    
};

#endif // BOARDPROPERTYWIDGET_H
