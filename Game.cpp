#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "float.h"
#include "Linkedlist.h"
#include "Trigger.h"
#include "Character.h"
#include "menu.h"
#include "House.h"
#include "PoCar.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QGLFormat>
#include <QObject>

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
    this->setAttribute(Qt::WA_DeleteOnClose);

    q_block = new Linkedlist<Block>();
    q_baseBrick = new Linkedlist<Block>();
    q_char = new Linkedlist<Character>();
    list_bullet = new QList<Bullet*>();

    gameSoundInit();

    //Game ground
    for (int i = 0; (i <= GAME_WIDTH/64); ++i){
        if(((i>=14) && (i<=16)) || ((i>=27) && (i<=30)) || ((i>=42) && (i<=44)) ||
                ((i>=58) && (i<=68)) || ((i>=88) && (i<=91))) continue;
        Block* brick = new Block(img_brick, i, 1);
        q_baseBrick->append(brick);
    }

    loadBrick();
    placeAllBlock();

    loadTrigger();
    //temp
    house = new House(121, 2);
    scene->addItem(house);

    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(200, scene->height() / 2);
    q_char->append(player);

    connect(player, SIGNAL(playerIsDead()), this, SLOT(gameOver()));

    connect(player, SIGNAL(backedHome()), this, SLOT(gameWin()));

    gameMusic->play();
}

Game::~Game(){
    delete scene;
    //lists
    delete q_block;
    delete q_baseBrick;
    delete q_char;
    delete list_bullet;
    delete player;
    //music
    delete gwMusic;
    delete goMusic;
    delete gameMusic;
    //game item

    delete timer;
}

void Game::startTimer(){
    scene->addItem(player);
    timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(10);
    timer->start();
    centerOn(player);
}

void Game::checkForDelete()
{
    foreach (QGraphicsItem *item, scene->items())
    {
        // should split the if statement **nullptr
        if (item == nullptr) continue;
        if (item->type() != Block::Type
            && item->type() != Bullet::Type
            && item->type() != Dog::Type
            && item->type() != Raptor::Type
            && item->type() != PoCar::Type)
            continue;

        //Condition 1: Character fell out of the scene
        //Condition 2: Character flew out of the scene
        //Condition 3: The view has passed for a certain distance
        if (item->pos().y() > scene->height()
            || item->pos().y() + item->boundingRect().height() <= 0
            || item->pos().x() <= (scene->views().first()->horizontalScrollBar()->value()) - 64 * 3) //current distance: 0 block
        {
            scene->removeItem(item);
            switch (item->type())
            {
                case Block::Type:
                    if(q_block->deleteNode(static_cast<Block*>(item)))
                    {

                    }
                    if(q_baseBrick->deleteNode(static_cast<Block*>(item)))
                    {

                    }
                    break;
                case Bullet::Type:
                    if(list_bullet->removeOne(static_cast<Bullet*>(item)))
                    {

                    }
                    break;
                case Dog::Type:
                case Raptor::Type:
                case PoCar::Type:
                    if(q_char->deleteNode(static_cast<Character*>(item)))
                    {

                    }
                    break;
            }
        }
    }
}

void Game::gravity()
{
    // change player to the list/data structure that holds all the characters
    for (Node<Character>* p = q_char->getHead(); p != nullptr; p = p->next){
        if (!p->data->isOnGround()){
            // in air:
            if(p->data->getVerticalVelocity() < 0){
                //upward
                if (p->data->collide(UPWARD)) {

                } else {
                    p->data->setPos(p->data->x(),p->data->y() + p->data->getVerticalVelocity());
                    p->data->setVerticalVelocity(p->data->getVerticalVelocity() + verticalAcceleration);

                }
            } else if (p->data->getVerticalVelocity() >= 0){
                if (p->data->collide(DOWNWARD)){

                } else {
                    p->data->setPos(p->data->x(),p->data->y() + p->data->getVerticalVelocity());
                    p->data->setVerticalVelocity(p->data->getVerticalVelocity() + verticalAcceleration);
                }

            }
        }
    }
}

void Game::update(){

    checkForDelete();

    // advance all the characters only, since other
    // items(block,trigger,etc.) do not need to be advanced

    // scene.advance() calls all items QGraphics::advance(step)
    // twice:
    // step==0 to indicate items they are about to advance;
    // step==1 advance the items
    // checked qt source code and some other examples
    // have no idea why and what will happen in advance(0);
    // but we better keep it

    for (Node<Character>* current = q_char->getHead(); current!=nullptr; current = current->next){
        current->data->advance(0);
    }

    for (Node<Character>* current = q_char->getHead(); current!=nullptr; current = current->next){
        current->data->advance(1);
        // stops the method when gameover,
        // prevent nullptr accessing
        if (player == nullptr) return;
    }

    for (int i = 0; i < list_bullet->size(); ++i) list_bullet->value(i)->advance(1);


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
        // temp

        }
}

void Game::gameSoundInit(){
    //bgm
    gameMusic = new QMediaPlayer();
    gameMusic->setMedia(QUrl("qrc:/music/res/bgm_game.mp3"));
    gameMusic->setVolume(40);

    //Game Over
    goMusic = new QMediaPlayer();
    goMusic->setMedia(QUrl("qrc:/music/res/go.wav"));
    goMusic->setVolume(40);

    //Game Win
    gwMusic = new QMediaPlayer();
    gwMusic->setMedia(QUrl("qrc:/music/res/gw.wav"));
    gwMusic->setVolume(20);
}

void Game::loadBrick(){
    //Open file
    QFile f(":/coordinates/coordinates/coorBrick.txt");
    f.open(QIODevice::ReadOnly);
    //Read Coordinates
    foreach (QString i,QString(f.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        Block* brick = new Block(img_brick, i.section(" ",0,0).toInt() , i.section(" ",1,1).toInt());
        q_block->append(brick);
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
    triggerFile.close();
}

void Game::loadTrigChar(QString trigData)
{

    QFile trigCharFile(":/coordinates/coordinates/coorTrigChar.txt");
    trigCharFile.open(QIODevice::ReadOnly);
    // count data with matching index
    int size = 0;
    foreach (QString characterData,QString(trigCharFile.readAll()).split(QRegExp("[\r\n]"),QString::SkipEmptyParts)){
        if (trigData.section(" ",2,2).toInt() == characterData.section(" ",0,0).toInt()) ++size;
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

void Game::deleteBullet(){
    scene->removeItem(qobject_cast<Bullet*>(sender()));
    list_bullet->removeAll(qobject_cast<Bullet*>(sender()));
    delete qobject_cast<Bullet*>(sender());
}

void Game::gameOver(){
    disconnect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->stop();
    goMusic->play();
    gameMusic->stop();
    centerOn(0,0);
    result = LOSE;

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    while(!q_block->isEmpty()){
        temp = q_block->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    while(!q_char->isEmpty()){
        temp = q_char->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    for (int i = 0; i < list_bullet->size(); ++i) {
        delete list_bullet->value(i);
    }
    list_bullet->clear();

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
    gwMusic->play();
    centerOn(0,0);
    gameMusic->stop();
    //If lose before, the game is lose forever
    if (result != LOSE) result = WIN;

    QGraphicsItem* temp;
    while(!q_baseBrick->isEmpty()){
        temp = q_baseBrick->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    while(!q_block->isEmpty()){
        temp = q_block->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    while(!q_char->isEmpty()){
        temp = q_char->removehead();
        scene->removeItem(temp);
        delete temp;
    }

    for (int i = 0; i < list_bullet->size(); ++i) {
        delete list_bullet->value(i);
    }
    list_bullet->clear();

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

Linkedlist<Character>* Game::getCharLinkedlist()
{
    return q_char;
}

QList<Bullet*> *Game::getBulletList()
{
    return list_bullet;
}

int Game::getWinHeight(){
    return WIN_HEIGHT;
}

int Game::getWinWidth(){
    return WIN_WIDTH;
}

double Game::getVerticalAcceleration()
{
    return verticalAcceleration;
}
