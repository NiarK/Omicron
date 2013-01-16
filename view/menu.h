#ifndef MENU_H
#define MENU_H

// --- Include Qt --- //
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>

// --- include Omicron --- //
#include "view/field.h"
#include "view/boardpropertywidget.h"
#include "view/cubepropertywidget.h"
#include "view/tesseractpropertywidget.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    virtual  ~Menu();
    
signals:
    void fieldChoosed(Field f);
    void benchmarkLaunched(Field f);
    
public slots:
    void emitFieldChoosed();
    void emitBenchmarkLaunched();
    void setPropertyWidget();

private:

    QRadioButton * _rbBoard;
    QRadioButton * _rbCube;
    QRadioButton * _rbTesseract;
    QRadioButton * _rbDonut;

    PropertyWidget * _property;
    QBoxLayout * _lytProperty;
    
};


#endif // MENU_H
