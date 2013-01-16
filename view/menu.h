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
#include "view/propertywidget.h"

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

private:

    QRadioButton * _rbBoard;
    QRadioButton * _rbCube;
    QRadioButton * _rbTesseract;
    QRadioButton * _rbDonut;

    
};


#endif // MENU_H
