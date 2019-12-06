#ifndef GAME_H
#define GAME_H

#include "Dog.h"
#include "Player.h"
#include "Raptor.h"
#include <QTimer>
#include <QGraphicsView>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    const double verticalAcceleration = 8/120.0;

    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QMap <int, bool> getKeyMap();

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    double getWinHeight();
    double getWinWidth();
    double getVerticalAcceleration();
public slots:
    void update();

private:
    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 800;
    const int anim_ratio = 2;
    int anim_count = 0;

    QMap <int, bool> keys;

    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
    //test purpose:
    Dog *dog;
    Raptor *raptor;
};

#endif // GAME_H
