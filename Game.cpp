#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "float.h"
#include "Queue.h"

#include <math.h>
#include <iostream>
#include <String>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QTAlgorithms>

using namespace std;

Game::Game(QWidget *parent) : QGraphicsView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 4000 ,WIN_HEIGHT);
    scene->setBackgroundBrush(QBrush(QColor("#82f4ff")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    for (int i = 0; i <= 4000/64; ++i){
        Block* brick = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
        brick->setPos(i*64, getWinHeight() - 64);
        scene->addItem(brick);
    }
    Queue<Block>* q_block= new Queue<Block>();
    Block* bricka = new Block(img_brick, 64 ,64);
    bricka->setPos(10*64, getWinHeight() - 64 * 2);
    Block* brickb = new Block(img_brick, 64 ,64);
    brickb->setPos(10*64, getWinHeight() - 64 * 3);
    Block* brickc = new Block(img_brick, 64 ,64);
    brickc->setPos(7*64, getWinHeight() - 64 * 2);
    Block* brickd = new Block(img_brick, 64 ,64);
    brickd->setPos(14*64, getWinHeight() - 64 * 4);
    scene->addItem(bricka);
    scene->addItem(brickb);
    scene->addItem(brickc);
    scene->addItem(brickd);

    //Player Init
    player_array.resize(4);
    for(int i = 0; i < 4; ++i){
        player_array[i] = QPixmap(QString::fromStdString(":/images/res/sprite_" + to_string(i)+ ".png"));
    }
    player = new Player(QPixmap(":/images/res/player.png"), 64, 64);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(200, scene->height()/2);
    scene->addItem(player);

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/120);
    centerOn(player);
}

Game::~Game(){
    scene->clear();

}

void Game::gravity()
{
    if(!player->isOnGround()){
        // in air:
        if(player->getVerticalVelocity() < 0){
            //upward
            if (player->collide(UPWARD)) {

            } else {
                player->setPos(player->x(),player->y() + player->getVerticalVelocity());
                //cout << player->getVerticalVelocity() << endl;
            }
            player->setVerticalVelocity(player->getVerticalVelocity() + player->getVerticalAcceleration());

        } else if (player->getVerticalVelocity() >= 0){
            if (player->collide(DOWNWARD)){

            } else {
                player->setPos(player->x(),player->y() + player->getVerticalVelocity());
            }
            player->setVerticalVelocity(player->getVerticalVelocity() + player->getVerticalAcceleration());
        }
        /*if (player->y() + player->getVerticalSpeed() + player->getHeight() >= getWinHeight()){
            player->setPos(player->x(), getWinHeight()-player->getHeight());
            player->setVerticalSpeed(0.0);
            player->setVerticalVelocity(0.0);
            player->setInAir(false);
        } else {
            player->setPos(player->x(), player->y()+player->getVerticalSpeed());
            player->setVerticalSpeed(player->getVerticalSpeed() + player->getVerticalVelocity());
            player->setVerticalVelocity(player->getVerticalVelocity() + player->getVerticalAcceleration());
            //cout << "verticalSpeed: " << verticalSpeed << endl;
        }*/
    }
}

void Game::update(){
    gravity();
    if(keys[Qt::Key_W]) {
        player->jump();
    }
    if(keys[Qt::Key_A]) {

        if (!goingBack){                                                //Player is going back, lock the screen
            prev_x = player->x() + player->getWidth() / 2;
            prev_y = player->y();
            centerOn(prev_x, prev_y);
            goingBack = true;
        }

        //Cant go back if the player touches the leftmost part of the screen
        if (player->x() >= this->horizontalScrollBar()->value()) player->move(LEFT);
        int count = anim_count;
        if (count % (anim_ratio * 4) == 0) {
            player->setPixmap(player_array[count / (anim_ratio * 4)]);
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    if(keys[Qt::Key_D]) {
        if (goingBack){
            if (player->x()+ player->getWidth() / 2 >= prev_x){
                centerOn(player);
                goingBack = false;
            }
        }else centerOn(player);
        player->move(RIGHT);
        int count = anim_count;
        if (count % (anim_ratio * 4) == 0) {
            player->setPixmap(player_array[count / (anim_ratio * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    if(keys[Qt::Key_Space]){
        cout << "x:" << player->x() << endl;
        cout << "y:" << player->y() << endl;
        cout << "prevx:" << prev_x << endl;
        //cout << "velocity:" << player->getVerticalVelocity() << endl;
        //cout << "isOnGround:" << (player->isOnGround() ? "true" : "false") << endl;
        cout << "goingBack:" << goingBack << endl;
    }

}

void Game::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    keys[e->key()] = true; //QGraphicsPixmapItem::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
   keys[e->key()] = false; //QGraphicsPixmapItem::keyReleaseEvent(e);
}

double Game::getWinHeight(){
    return WIN_HEIGHT;
}

double Game::getWinWidth(){
    return WIN_HEIGHT;
}
