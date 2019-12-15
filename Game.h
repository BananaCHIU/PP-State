#ifndef GAME_H
#define GAME_H

#include "Dog.h"
#include "Player.h"
#include "Block.h"
#include "Queue.h"
#include "Trigger.h"
#include "Bullet.h"
#include "Raptor.h"
#include "House.h"

#include <QTimer>
#include <QGraphicsView>
#include <QMediaPlayer>

class Game: public QGraphicsView{
    Q_OBJECT
private:
    const double verticalAcceleration = 13/120.0;

    void checkForDelete();
    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void gameSoundInit();
    void loadBrick();
    void loadTrigger();
    void loadTrigChar(QString trigData);
    void placeAllBlock();

    enum gameResult {WIN, LOSE, NOPE} result = NOPE;

    static const int WIN_WIDTH = 1400;
    static const int WIN_HEIGHT = 800;
    const int GAME_WIDTH = 6000;

    //Store the player's xy when it move to the left
    qreal prev_x = -1, prev_y = -1;
    bool goingBack = false;

    QGraphicsScene *scene;
    Player *player;
    House* house;
    QTimer * timer;
    QMediaPlayer* gwMusic, *goMusic,*gameMusic;
    QPixmap img_brick{":/background/res/brick_1.png"};
    Queue<Block>* q_block, *q_baseBrick;
    Queue<Character>* q_char;
    QList<Bullet*>* list_bullet;

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    Queue<Character>* getCharQueue();
    QList<Bullet*>* getBulletList();
    static int getWinHeight();
    static int getWinWidth();

    double getVerticalAcceleration();
public slots:
    void startTimer();
    void update();
    void gameOver();
    void gameWin();
};

#endif // GAME_H
