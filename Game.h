#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QTimer>
#include <QGraphicsView>


class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 600;
public slots:
    void update();
private:
    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
};

#endif // GAME_H
