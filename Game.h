#ifndef GAME_H
#define GAME_H

#include "Dog.h"
#include "Player.h"
<<<<<<< HEAD
#include "Queue.h"
=======
#include "Raptor.h"
>>>>>>> monster
#include <QTimer>
#include <QGraphicsView>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    const double verticalAcceleration = 8/120.0;

    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
<<<<<<< HEAD
    QMap <int, bool> getKeyMap();
    void loadBrick();
    void placeAllBlock();

    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 800;
    const int GAME_WIDTH = 40000;

    const int ANIM_RATIO = 2;
    int anim_count = 0;


    //Store the player's xy when it move to the left
    qreal prev_x = -1, prev_y = -1;
    bool goingBack = false;

    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
    QMap <int, bool> keys;
=======
>>>>>>> monster

    QPixmap img_brick{":/background/res/brick_1.png"};
    Queue<Block>* q_block;

    QPixmap player_array[4];
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

    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
    //test purpose:
    Dog *dog;
    Raptor *raptor;
};

#endif // GAME_H
