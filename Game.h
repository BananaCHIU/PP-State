#ifndef GAME_H
#define GAME_H

#include "Dog.h"
#include "Player.h"
#include "Block.h"
#include "Queue.h"

#include "Raptor.h"

#include <QTimer>
#include <QGraphicsView>
#include <QMediaPlayer>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    const double verticalAcceleration = 8/120.0;

    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void loadBrick();
    void placeAllBlock();

    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 800;
    const int GAME_WIDTH = 40000;
    enum gameResult {WIN, LOSE, NOPE} result = NOPE;

    //Store the player's xy when it move to the left
    qreal prev_x = -1, prev_y = -1;
    bool goingBack = false;

    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
    QMediaPlayer* gwMusic;
    QPixmap img_brick{":/background/res/brick_1.png"};
<<<<<<< HEAD
    Queue<Block>* q_block, *q_baseBrick;
=======
    Queue<Block>* q_block;
    Queue<Character>* q_char;


    // testing purpose:
    Bullet *bullet;
>>>>>>> data_structure

public:
    Game(QWidget *parent = nullptr);
    ~Game();
<<<<<<< HEAD
    double getWinHeight();
    double getWinWidth();
=======

    Queue<Character>* getCharQueue();
    static double getWinHeight();
    static double getWinWidth();
>>>>>>> data_structure
    double getVerticalAcceleration();
public slots:
    void update();
    void gameOver();
    void gameWin();
};

#endif // GAME_H
