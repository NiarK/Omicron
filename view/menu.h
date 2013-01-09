#ifndef MENU_H
#define MENU_H

// --- Include Qt --- //
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

// --- include Omicron --- //
#include "view/field.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    virtual  ~Menu();
    
signals:
    void fieldChoosed(Field m);
    
public slots:
    void emitFieldChoosed();

private:
    QPushButton* _btnBoard;
    //QPushButton* _btnDonut;
    QPushButton* _btnCube;
    QPushButton* _btnTesseract;

    
};


#endif // MENU_H
