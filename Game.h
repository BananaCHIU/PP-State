#ifndef GAME_H
#define GAME_H

#include "Player.h"

#include <QGraphicsView>


class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    signals:
    void keyInputReceived(int movement);
private:
    QGraphicsScene *scene;
    Player *player;
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 600;
    bool keyPressed = false;
};

#endif // GAME_H
