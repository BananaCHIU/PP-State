#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "float.h"
#include "Queue.h"
#include "Dog.h"
<<<<<<< HEAD
#include "menu.h"
=======
#include "Bullet.h"
#include "Trigger.h"
>>>>>>> origin/data_structure

#include <math.h>
#include <iostream>
#include <fstream>
#include <String>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QTAlgorithms>
#include <QSound>

using namespace std;

Game::Game(QWidget *parent) : QGraphicsView(){
    this->setWindowTitle("Save this city!");
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GAME_WIDTH ,WIN_HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    q_block = new Queue<Block>();
    q_baseBrick = new Queue<Block>();

    //Game ground
    for (int i = 0; (i <= GAME_WIDTH/64); ++i){
        if(((i>=14) && (i<=16)) || ((i>=22) && (i<=25)) || ((i>=33) && (i<=35)) || ((i>=33) && (i<=35)) ||
                ((i>=43) && (i<=45)) || ((i>=54) && (i<=57)) || ((i>=59) && (i<=60)) || ((i>=62) && (i<=63))
                || ((i>=65) && (i<=66))) continue;
<<<<<<< HEAD
        Block* brick = new Block(img_brick, getWinHeight() , i, 1);
        q_baseBrick->enqueue(brick);
=======
        Block* brick = new Block(img_brick, i, 1);
        q_block->enqueue(brick);
>>>>>>> origin/data_structure
    }

    loadBrick();
    placeAllBlock();

    loadTrigger();

    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(200, scene->height()/2);
    scene->addItem(player);

    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/120);

    connect(player, SIGNAL(playerIsDead()), this, SLOT(gameOver()));

    centerOn(player);
}

Game::~Game(){
    delete q_block;
    delete q_baseBrick;
    delete player;
    delete gwMusic;
}

void Game::gravity()
{
    // temp data structure to hold characters:
    QList<Character*> characters = {player};
    // change player to the list/data structure that holds all the characters
    for (int i = 0; i < characters.size(); ++i){
        if ((characters[i])->type() == Bullet::Type) continue;
        if (!characters[i]->isOnGround()){
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

    }else if(player->getKeyMap().value(Qt::Key_D)){

        if (goingBack){
            if (player->x()+ player->getWidth() / 2 >= prev_x){
                centerOn(player);
                goingBack = false;
            }
        }else {
            centerOn(player);
        }
    }else if(player->getKeyMap().value(Qt::Key_Space)){
        gameOver();
    }else if(player->getKeyMap().value(Qt::Key_L)){
        gameWin();
    }
    // testing purpose:
    if(player->getKeyMap().value(Qt::Key_Space)){
        cout << floor(player->x()/64.0) << " " << floor(player->y()/64.0) << endl;
    }

}

void Game::loadBrick(){
    //Open file
    QFile f(":/coordinates/coordinates/coorBrick.txt");
    f.open(QIODevice::ReadOnly);
    //Read Coordinates
    foreach (QString i,QString(f.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        Block* block = new Block(img_brick, i.section(" ",0,0).toInt() , i.section(" ",1,1).toInt());
        q_block->enqueue(block);
    }
    f.close();
}

void Game::loadTrigger(){
    QFile triggerFile(":/coordinates/coordinates/coorTrigger.txt");
    triggerFile.open(QIODevice::ReadOnly);
    foreach (QString trigData,QString(triggerFile.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        loadTrigChar(trigData);
    }
}

void Game::loadTrigChar(QString trigData)
{

    QFile trigCharFile(":/coordinates/coordinates/coorTrigChar.txt");
    trigCharFile.open(QIODevice::ReadOnly);
    // count data with matching index
    int size = 0;
    foreach (QString characterData,QString(trigCharFile.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        size++;
    }
    trigCharFile.close();

    // read and put data into the Trigger block
    int count = 0;
    Trigger *trigger = new Trigger(size, trigData.section(" ",0,0).toInt() , trigData.section(" ",1,1).toInt());
    trigCharFile.open(QIODevice::ReadOnly);
    foreach (QString characterData,QString(trigCharFile.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        if (trigData.section(" ",2,2).toInt() == characterData.section(" ",0,0).toInt()){
            // convert string to enum direction
            direction dir;
            if (!characterData.section(" ",4,4).toUpper().compare("UPWARD")) dir = UPWARD;
            else if (!characterData.section(" ",4,4).toUpper().compare("DOWNWARD")) dir = DOWNWARD;
            else if (!characterData.section(" ",4,4).toUpper().compare("LEFT")) dir = LEFT;
            else dir = RIGHT;

            // store value to a temp spawnee variable
            Trigger::characterData temp;
            temp.x = characterData.section(" ",1,1).toInt();
            temp.y = characterData.section(" ",2,2).toInt();
            temp.type = characterData.section(" ",3,3).toUpper();
            temp.dir = dir;

            // add it to the Trigger block
            trigger->setDataAt(count, temp);

            // increase counter
            count++;
        }
    }
    scene->addItem(trigger);
    trigCharFile.close();
}

void Game::placeAllBlock(){
    //Place all block in game
    for(Node<Block>* p = q_block->getHead(); p != nullptr; p = p->next){
        scene->addItem(p->data);
    }
    for(Node<Block>* p = q_baseBrick->getHead(); p != nullptr; p = p->next){
        scene->addItem(p->data);
    }
}

void Game::gameOver(){
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->stop();
    centerOn(0,0);
    result = LOSE;
    QSound::play(":/music/res/go.wav");

    scene->removeItem(player);
    delete player;
    player = nullptr;

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->dequeue();
        scene->removeItem(temp);
        delete temp;
    }
    while(!q_block->isEmpty()){
        temp = q_block->dequeue();
        scene->removeItem(temp);
        delete temp;
    }

    scene->setBackgroundBrush(QBrush(QColor("#ffffff")));
    QGraphicsPixmapItem* goTitle = new QGraphicsPixmapItem (QPixmap(":/images/res/go.png"));
    goTitle->setPos(700 - goTitle->pixmap().width() /2 , 70);
    scene->addItem(goTitle);
    QGraphicsPixmapItem* go1 = new QGraphicsPixmapItem (QPixmap(":/images/res/go_1.png"));
    go1->setPos(200 , 230);
    scene->addItem(go1);
    QGraphicsPixmapItem* go2 = new QGraphicsPixmapItem (QPixmap(":/images/res/go_2.png"));
    go2->setPos(700 - go2->pixmap().width() /2 , 660);
    scene->addItem(go2);
}

void Game::gameWin(){
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->stop();
    centerOn(0,0);
    result = WIN;
    gwMusic = new QMediaPlayer();
    gwMusic->setMedia(QUrl("qrc:/music/res/gw.wav"));
    gwMusic->play();

    scene->removeItem(player);
    delete player;
    player = nullptr;

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->dequeue();
        scene->removeItem(temp);
        delete temp;
    }
    while(!q_block->isEmpty()){
        temp = q_block->dequeue();
        scene->removeItem(temp);
        delete temp;
    }

    scene->setBackgroundBrush(QBrush(QColor("#ffffff")));
    QGraphicsPixmapItem* gwTitle = new QGraphicsPixmapItem (QPixmap(":/images/res/gw.png"));
    gwTitle->setPos(700 - gwTitle->pixmap().width() /2 , 70);
    scene->addItem(gwTitle);
    QGraphicsPixmapItem* gw1 = new QGraphicsPixmapItem (QPixmap(":/images/res/gw_1.png"));
    gw1->setPos(200 , 230);
    scene->addItem(gw1);
    QGraphicsPixmapItem* gw2 = new QGraphicsPixmapItem (QPixmap(":/images/res/gw_2.png"));
    gw2->setPos(700 - gw2->pixmap().width() /2 , 660);
    scene->addItem(gw2);
}

void Game::keyPressEvent(QKeyEvent *e)
{
    if (result == LOSE){
        Menu* menu = new Menu(true);
        menu->show();
        close();
    }else if (result == WIN){
        Menu* menu = new Menu();
        menu->show();
        close();
    }
    if (player == nullptr) return;
    if (e->isAutoRepeat()) return;
    player->setKeyValue(e->key(), true);
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    if (player == nullptr) return;
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

void Game::gameOver(){
    // to be merged with gameOver() in branche game_over
    // cout << " game over" << endl;
}
