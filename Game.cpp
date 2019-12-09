#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Dog.h"

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
    scene->setSceneRect(0, 0, 2000 ,WIN_HEIGHT);
    scene->setBackgroundBrush(QBrush(QColor("#82f4ff")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    player = new Player(QPixmap(":/images/res/player.png"));
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(player->getWidth(), scene->height()/2);
    scene->addItem(player);

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/120);

    // testing purpose:
    // temp map drawing
    for (int i = 0; i <= 2000/64; ++i){
        Block* brick = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
        brick->setPos(i*64, getWinHeight() - 64);
        scene->addItem(brick);
    }

    Block* bricka = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
    bricka->setPos(6*64, getWinHeight() - 64 * 2);
    Block* brickb = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
    brickb->setPos(10*64, getWinHeight() - 64 * 3);
    Block* brickc = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
    brickc->setPos(13*64, getWinHeight() - 64 * 4);
    Block* brickd = new Block(QPixmap(":/background/res/brick_1.png"), 64 ,64);
    brickd->setPos(18*64, getWinHeight() - 64 * 2);
    scene->addItem(bricka);
    scene->addItem(brickb);
    scene->addItem(brickc);
    scene->addItem(brickd);

    // temp enemy spawning
    dog = new Dog(QPixmap(":/images/res/dog.png"));
    dog->setPos(scene->width()/2-102*3, scene->height()-64-60*3);
    scene->addItem(dog);

    raptor = new Raptor(QPixmap(":/images/res/green_raptor_0.png"));
    raptor->setPos(-60, scene->height()-64- raptor->getHeight());
    scene->addItem(raptor);
}

Game::~Game(){
    scene->clear();

}

void Game::gravity()
{
    // temp data structure to hold characters:
    QList<Character*> characters = {player, dog, raptor};
    // change player to the list/data structure that holds all the characters
    for (int i = 0; i < characters.size(); ++i){
        if(!characters[i]->isOnGround()){
            // in air:
            if(characters[i]->getVerticalVelocity() < 0){
                //upward
                if (characters[i]->collide(UPWARD)) {

                } else {
                    characters[i]->setPos(characters[i]->x(),characters[i]->y() + characters[i]->getVerticalVelocity());
                    //cout << player->getVerticalVelocity() << endl;
                }
                characters[i]->setVerticalVelocity(characters[i]->getVerticalVelocity() + verticalAcceleration);

            } else if (characters[i]->getVerticalVelocity() >= 0){
                if (characters[i]->collide(DOWNWARD)){

                } else {
                    characters[i]->setPos(characters[i]->x(),characters[i]->y() + characters[i]->getVerticalVelocity());
                }
                characters[i]->setVerticalVelocity(characters[i]->getVerticalVelocity() + verticalAcceleration);
            }
        }
    }
}

void Game::update(){
    scene->advance();
    centerOn(player);
    gravity();

    // debug purpose, remove later:
    cout << "" << player->shape().boundingRect().left() + 1 << endl;
    if(player->getKeyMap().value(Qt::Key_Space)){
        scene->removeItem(dog);
        delete dog;
        dog = new Dog(QPixmap(":/images/res/dog.png"));
        dog->setPos(scene->width()/2-102*3, scene->height()-64-60*3);
        scene->addItem(dog);

        scene->removeItem(raptor);
        delete raptor;
        raptor = new Raptor(QPixmap(":/images/res/green_raptor_0.png"), LEFT);
        raptor->setPos(scene->width() - raptor->getWidth(), scene->height()-64- raptor->getHeight());
        scene->addItem(raptor);
    }

}

void Game::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    player->setKeyValue(e->key(), true); //QGraphicsPixmapItem::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    player->setKeyValue(e->key(), false); //QGraphicsPixmapItem::keyReleaseEvent(e);
}

double Game::getWinHeight(){
    return WIN_HEIGHT;
}

double Game::getWinWidth(){
    return WIN_HEIGHT;
}

double Game::getVerticalAcceleration()
{
    return verticalAcceleration;
}
