#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "float.h"
#include "Queue.h"
#include "Trigger.h"
#include "Character.h"
#include "menu.h"
#include "House.h"

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
#include <QGLFormat>

using namespace std;

static bool renamedPP = false;

Game::Game(QWidget *parent) : QGraphicsView(){
    QGLFormat fmt;
        fmt.setSampleBuffers(true);
        fmt.setSamples(2);
        setViewport(new QGLWidget(fmt));
        fmt.setDirectRendering(true);


    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //this->setCacheMode(QGraphicsView::CacheBackground);
    setWindowTitle("Quick! Go Back Home!");
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, GAME_WIDTH ,WIN_HEIGHT);
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    scene->setBackgroundBrush(QBrush(QPixmap(":images/res/level1_bg.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    centerOn(0,0);

    q_block = new Queue<Block>();
    q_baseBrick = new Queue<Block>();
    q_char = new Queue<Character>();

    //Game ground
    for (int i = 0; (i <= GAME_WIDTH/64); ++i){
        if(((i>=14) && (i<=16)) || ((i>=27) && (i<=30)) || ((i>=42) && (i<=44)) ||
                ((i>=58) && (i<=68)) )continue;
        Block* brick = new Block(img_brick, i, 1);
        q_baseBrick->enqueue(brick);
    }

    loadBrick();
    placeAllBlock();

    loadTrigger();
    //temp
    house = new House(85, 2);
    scene->addItem(house);

    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(200, scene->height()/2);
    q_char->enqueue(player);
    scene->addItem(player);

    connect(player, SIGNAL(playerIsDead()), this, SLOT(gameOver()));

    connect(player, SIGNAL(backedHome()), this, SLOT(gameWin()));

    gameMusic = new QMediaPlayer();
    gameMusic->setMedia(QUrl("qrc:/music/res/bgm_game.mp3"));
    gameMusic->setVolume(20);
    gameMusic->play();
}

Game::~Game(){
    delete q_block;
    delete q_baseBrick;
    delete player;
    delete gwMusic;
    delete gameMusic;
    delete house;
}

void Game::startTimer(){
    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(10);
    timer->start();
    centerOn(player);
}

void Game::gravity()
{
    // change player to the list/data structure that holds all the characters
    for (Node<Character>* p = q_char->getHead(); p != nullptr; p = p->next){
        if ((p->data)->type() == Bullet::Type) continue;
        if (!p->data->isOnGround()){
            // in air:
            if(p->data->getVerticalVelocity() < 0){
                //upward
                if (p->data->collide(UPWARD)) {

                } else {
                    p->data->setPos(p->data->x(),p->data->y() + p->data->getVerticalVelocity());
                    //cout << player->getVerticalVelocity() << endl;
                }
                p->data->setVerticalVelocity(p->data->getVerticalVelocity() + verticalAcceleration);

            } else if (p->data->getVerticalVelocity() >= 0){
                if (p->data->collide(DOWNWARD)){

                } else {
                    p->data->setPos(p->data->x(),p->data->y() + p->data->getVerticalVelocity());
                }
                p->data->setVerticalVelocity(p->data->getVerticalVelocity() + verticalAcceleration);
            }
        }
    }
}

void Game::update(){

    scene->advance();
    if (player == nullptr) return;
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
        cout << static_cast<int>(player->x() / 64) << "  " << static_cast<int>(-(player->y() - WIN_HEIGHT) / 64 )<< endl;
    }
}

void Game::loadBrick(){
    //Open file
    QFile f(":/coordinates/coordinates/coorBrick.txt");
    f.open(QIODevice::ReadOnly);
    //Read Coordinates
    foreach (QString i,QString(f.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        Block* brick = new Block(img_brick, i.section(" ",0,0).toInt() , i.section(" ",1,1).toInt());
        q_block->enqueue(brick);
    }
    f.close();
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
        ++size;
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

void Game::gameOver(){
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->stop();
    gameMusic->stop();
    centerOn(0,0);
    result = LOSE;
    QSound::play(":/music/res/go.wav");

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->dequeue();
        scene->removeItem(temp);

    }
    while(!q_block->isEmpty()){
        temp = q_block->dequeue();
        scene->removeItem(temp);
    }
    while(!q_char->isEmpty()){
             temp = q_char->dequeue();
             scene->removeItem(temp);
         }

    player = nullptr;

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
    gameMusic->stop();
    //If lose before, the game is lose forever
    if (result != LOSE) result = WIN;

    gwMusic = new QMediaPlayer();
    gwMusic->setMedia(QUrl("qrc:/music/res/gw.wav"));
    gwMusic->play();

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->dequeue();
        scene->removeItem(temp);
    }
    while(!q_block->isEmpty()){
        temp = q_block->dequeue();
        scene->removeItem(temp);
    }
    while(!q_char->isEmpty()){
        temp = q_char->dequeue();
        scene->removeItem(temp);
    }
    player = nullptr;

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
        renamedPP = true;
        Menu* menu = new Menu(true);
        menu->show();
        close();
    }else if (result == WIN){
        if (renamedPP){
            Menu* menu = new Menu(true);
            menu->show();
            close();
        }else{
            Menu* menu = new Menu();
            menu->show();
            close();
        }
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

Queue<Character>* Game::getCharQueue()
{
    return q_char;
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
