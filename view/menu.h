#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);
    virtual  ~Menu();
    
signals:
    void boardClicked();
    
public slots:
    void emitBoardClicked();

private:
    QPushButton* _btnBoard;
    QPushButton* _btnDonut;
    QPushButton* _btnCube;
    QPushButton* _btnTesseract;

    
};


#endif // MENU_H
