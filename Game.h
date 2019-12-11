#ifndef GAME_H
#define GAME_H

#include "Dog.h"
#include "Player.h"
#include "Block.h"
#include "Queue.h"

#include "Bullet.h"
#include "Raptor.h"
#include "Trigger.h"

#include <QTimer>
#include <QGraphicsView>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    const double verticalAcceleration = 8/120.0;

    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void loadTriggerData();
    void loadBrick();
    void placeAllBlock();

    static const int WIN_WIDTH = 1400;
    static const int WIN_HEIGHT = 800;
    static const int GAME_WIDTH = 40000;

    //Store the player's xy when it move to the left
    qreal prev_x = -1, prev_y = -1;
    bool goingBack = false;

    QGraphicsScene *scene;
    Player *player;
    QTimer *timer;

    QPixmap img_brick{":/background/res/brick_1.png"};
    Queue<Block>* q_block;
    // testing purpose:
    Bullet *bullet;

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    static double getWinHeight();
    static double getWinWidth();
    double getVerticalAcceleration();
public slots:
    void update();
    void gameOver();
};

#endif // GAME_H
