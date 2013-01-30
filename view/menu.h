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
//#include "view/field.h"
#include "view/gameoption.h"
#include "view/boardpropertywidget.h"
#include "view/cubepropertywidget.h"
#include "view/tesseractpropertywidget.h"
#include "view/donutpropertywidget.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(GameOption & option, QWidget *parent = 0);
    virtual  ~Menu();

    virtual void updateIHM();
    void setPropertyWidget();
    
signals:
    void fieldChoosed(Field f);
    void benchmarkLaunched();
    void gameLaunched();
    
public slots:
    void emitFieldChoosed();
    void emitBenchmarkLaunched();
    void emitGameLaunched();
    virtual void updateOption();

private:
    GameOption & _option;

    QRadioButton * _rbBoard;
    QRadioButton * _rbCube;
    QRadioButton * _rbTesseract;
    QRadioButton * _rbDonut;

    QRadioButton * _rbAI;
    QRadioButton * _rbPlayerPacman;
    QRadioButton * _rbPlayerGhost;

    QRadioButton * _rbRandomAI;
    QRadioButton * _rbWiseAI;

    PropertyWidget * _property;
    QBoxLayout * _lytProperty;

    
};


#endif // MENU_H
