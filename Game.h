#ifndef GAME_H
#define GAME_H

#include "Block.h"
#include "Bullet.h"
#include "Dog.h"
#include "House.h"
#include "Player.h"
#include "Queue.h"
#include "Raptor.h"
#include "Trigger.h"

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>

/*
 * Game class inherits QGraphicsView.
 * It controls everything in the game.
 * load blocks & trigger, controls camera, updates characters,
 * update game result, accepts keyevents, etc.
 */
class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructor
    Game(QWidget *parent = nullptr);
    // destructor
    ~Game();
    // accessors
    QList<Bullet*>* getBulletList();
    Queue<Character>* getCharQueue();
    double getVerticalAcceleration();
    static int getWinHeight();
    static int getWinWidth();

public slots:
    // slots
    void startTimer();
    void update();
    void gameOver();
    void gameWin();

private:
    // other methods
    const double verticalAcceleration = 13/120.0;
    void checkForDelete();
    void gameSoundInit();
    void gravity();     // pulling all not on ground characters downwards
    void keyPressEvent(QKeyEvent * event);  // handle key events
    void keyReleaseEvent(QKeyEvent * event);// handle key events
    void loadBrick();   // load blocks from file
    void loadTrigChar(QString trigData);// load character data associated with triggers
    void loadTrigger(); // load triggers from file
    void placeAllBlock();
    // data members
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
};

#endif // GAME_H
