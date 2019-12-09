#include "Game.h"
#include "Player.h"
#include "Block.h"
<<<<<<< HEAD
#include "float.h"
#include "Queue.h"
=======
#include "Dog.h"
>>>>>>> monster

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

<<<<<<< HEAD
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
    //Player Init
    for(int i = 0; i < 4; ++i){
        player_array[i] = QPixmap(QString::fromStdString(":/images/res/sprite_" + to_string(i)+ ".png"));
    }
    player = new Player(player_array[1], 64, 64);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(200, scene->height()/2);
    scene->addItem(player);

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/120);
    centerOn(player);
=======
    player = new Player();
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
    dog = new Dog();
    dog->setPos(scene->width()/2-102*3, scene->height()-64-60*3);
    scene->addItem(dog);

    raptor = new Raptor(RIGHT);
    raptor->setPos(-60, scene->height()-64- raptor->getHeight());
    scene->addItem(raptor);
>>>>>>> monster
}

Game::~Game(){
    delete q_block;
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
<<<<<<< HEAD
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

        //Anim of player
        int count = anim_count;
        if (count % (ANIM_RATIO * 4) == 0) {
            player->setPixmap(player_array[count / (ANIM_RATIO * 4)]);
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
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

        //anim of player
        int count = anim_count;
        if (count % (ANIM_RATIO * 4) == 0) {
            player->setPixmap(player_array[count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    if(keys[Qt::Key_Space]){
        cout << "x:" << player->x() << endl;
        cout << "y:" << player->y() << endl;
        cout << "prevx:" << prev_x << endl;
        //cout << "velocity:" << player->getVerticalVelocity() << endl;
        //cout << "isOnGround:" << (player->isOnGround() ? "true" : "false") << endl;
        cout << "goingBack:" << goingBack << endl;
=======
    scene->advance();
    centerOn(player);
    gravity();

    // debug purpose, remove later:
    cout << "" << player->shape().boundingRect().left() + 1 << endl;
    if(player->getKeyMap().value(Qt::Key_Space)){
        scene->removeItem(dog);
        delete dog;
        dog = new Dog();
        dog->setPos(scene->width()/2-102*3, scene->height()-64-60*3);
        scene->addItem(dog);

        scene->removeItem(raptor);
        delete raptor;
        raptor = new Raptor(LEFT);
        raptor->setPos(scene->width() - raptor->getWidth(), scene->height()-64- raptor->getHeight());
        scene->addItem(raptor);
>>>>>>> monster
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
