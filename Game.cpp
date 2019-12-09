#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "float.h"
#include "Queue.h"
#include "Dog.h"


#include <math.h>
#include <iostream>
#include <fstream>
#include <String>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QTAlgorithms>

using namespace std;

Game::Game(QWidget *parent) : QGraphicsView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GAME_WIDTH ,WIN_HEIGHT);
    scene->setBackgroundBrush(QBrush(QColor("#82f4ff")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    q_block= new Queue<Block>();

    //Game ground
    for (int i = 0; (i <= GAME_WIDTH/64); ++i){
        if(((i>=14) && (i<=16)) || ((i>=22) && (i<=25)) || ((i>=33) && (i<=35)) || ((i>=33) && (i<=35)) ||
                ((i>=43) && (i<=45)) || ((i>=54) && (i<=57)) || ((i>=59) && (i<=60)) || ((i>=62) && (i<=63))
                || ((i>=65) && (i<=66))) continue;
        Block* brick = new Block(img_brick, getWinHeight() , i, 1);
        q_block->enqueue(brick);
    }

    loadBrick();
    placeAllBlock();

    player = new Player();
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
    delete q_block;
    scene->clear();

}

void Game::gravity()
{
    // temp data structure to hold characters:
    QList<Character*> characters = {player};
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
    gravity();
    if(player->getKeyMap().value(Qt::Key_A)){

        if (!goingBack){                                                //Player is going back, lock the screen
            prev_x = player->x() + player->getWidth() / 2;
            prev_y = player->y();
            centerOn(prev_x, prev_y);
            goingBack = true;
        }

    }
    if(player->getKeyMap().value(Qt::Key_D)){

        if (goingBack){
            if (player->x()+ player->getWidth() / 2 >= prev_x){
                centerOn(player);
                goingBack = false;
            }
        }else centerOn(player);
    }
}

void Game::loadBrick(){
    //Open file
    QFile f(":/coordinates/coordinates/coorBrick.txt");
    f.open(QIODevice::ReadOnly);
    //Read Coordinates
    foreach (QString i,QString(f.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        Block* brick = new Block(img_brick, getWinHeight(), i.section(" ",0,0).toInt() , i.section(" ",1,1).toInt());
        q_block->enqueue(brick);
    }
    f.close();
}

void Game::placeAllBlock(){
    //Place all block in game
    for(Node<Block>* p = q_block->getHead(); p != nullptr; p = p->next){
        scene->addItem(p->data);
    }
}

void Game::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    player->setKeyValue(e->key(), true);
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    player->setKeyValue(e->key(), false);
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
