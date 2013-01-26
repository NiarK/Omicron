#ifndef GAME_H
#define GAME_H

// --- Include Qt --- //
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include <QKeyEvent>

#include <QMessageBox>

// --- Include std --- //
#include <vector>

// --- Include Omicron --- //
#include "view/gameoption.h"
#include "controller/gamecontroller.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(const GameOption &option, QWidget *parent = 0);
    virtual ~GameWidget();


    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const = 0;
    virtual void linkVertex(QGraphicsScene * _scene,
                            const std::vector<QGraphicsEllipseItem*> & vertex) const;
    virtual void wheelEvent(QWheelEvent *event);

    static const int SPACING = 30;
    static const int RADIUS = 20;
    static const int THICK = 2;

signals:
    void terminated() const;
    void restarted() const;

public slots:
    void emitReturnClicked() const;
    void nextMove();

protected:
    GameController *getController() const;
    void setController(GameController * gc);
    virtual void keyPressEvent ( QKeyEvent * event );

private:

    virtual void updatePacman();
    virtual void updateGhost();
    virtual void updateActor();

    const GameOption & _option;

    QPushButton* _btnReturn;
    QPushButton* _btnNextMove;
    QLabel * _lblMovementGhostCounter;

    std::vector<QGraphicsEllipseItem*> _vertex;
    QGraphicsEllipseItem* _pacman;
    std::vector<QGraphicsEllipseItem*> _ghosts;

    GameController * _gameController;

    QGraphicsScene* _scene;
    QGraphicsView* _view;
    QVBoxLayout* _layout;

};

#endif // GAME_H
