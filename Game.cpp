#include "Game.h"
#include "Player.h"
#include "Block.h"

#include <iostream>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QTAlgorithms>

using namespace std;

Game::Game(QWidget *parent) : QGraphicsView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 2000 ,WIN_HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    for (int i = 0; i <= 2000/64; ++i){
        Block* brick = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
        brick->setPos(i*64, getWinHeight() - 64);
        scene->addItem(brick);
    }

    player = new Player(QPixmap(":/images/res/player.png"), 64, 64);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(scene->width()/2, scene->height()/2);
    scene->addItem(player);

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/120);
}

Game::~Game(){
    scene->clear();

}

void Game::update(){
    centerOn(player);
    mapToScene(QRect(point, QSize(2, 2)))
    if(keys[Qt::Key_A]) {
        if (player->getDirection() != 0) player->flipDirection();
        if (player->x() - 4 < 0)  player->setPos(0, player->y());
        else player->setPos(player->x()-4, player->y());

    }
    if(keys[Qt::Key_D]) {
        if (player->getDirection() != 1) player->flipDirection();
        if (player->x() + player->getWidth() + 4 > scene->width())  player->setPos(scene->width() - player->getWidth(), player->y());
        else player->setPos(player->x()+4, player->y());
    }
    if(keys[Qt::Key_W]) {
        if (!player->getInAir()){
            player->setVerticalSpeed(-500.0/120);
            player->setVerticalVelocity(0.0);
            player->setInAir();
        }
    }
    player->gravity();
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
