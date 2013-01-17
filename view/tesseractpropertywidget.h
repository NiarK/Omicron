#ifndef TESSERACTPROPERTYWIDGET_H
#define TESSERACTPROPERTYWIDGET_H

// --- Qt --- //
#include <QRadioButton>

// --- Omicron --- //
#include "view/propertywidget.h"
#include "view/gameoption.h"


class TesseractPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit TesseractPropertyWidget(GameOption & option, QWidget *parent = 0);
    virtual void updateIHM();
    
signals:
    
public slots:
    virtual void updateOption();
    
private:
    GameOption & _option;

    QRadioButton * _rb3D;
    QRadioButton * _rb2D;
};

#endif // TESSERACTPROPERTYWIDGET_H
