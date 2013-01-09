#ifndef GAME_H
#define GAME_H

// --- Include Qt --- //
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <QVBoxLayout>
#include <QPushButton>

// --- Include std --- //
#include <vector>

// --- Include Omicron --- //
#include "controller/gamecontroller.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    virtual ~Game();


    virtual void positionVertex(std::vector<QGraphicsEllipseItem*>::iterator vertexIt,
                                std::vector<QGraphicsEllipseItem*>::iterator endVertexIt) const = 0;
    virtual void linkVertex(QGraphicsScene * _scene,
                            const std::vector<QGraphicsEllipseItem*> & vertex) const;

    static const int SPACING = 10;
    static const int RADIUS = 40;

signals:
    void returnClicked() const;

public slots:
    void emitReturnClicked() const;

protected:
    GameController *getController() const;
    void setController(GameController * gc);

private:

    virtual void updatePacman();
    virtual void updateGhost();

    QPushButton* _return;

    std::vector<QGraphicsEllipseItem*> _vertex;
    QGraphicsEllipseItem* _pacman;
    std::vector<QGraphicsEllipseItem*> _ghosts;

    GameController * _gameController;

    QGraphicsScene* _scene;
    QGraphicsView* _view;
    QVBoxLayout* _layout;

};

#endif // GAME_H
