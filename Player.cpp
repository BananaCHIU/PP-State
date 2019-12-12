
#include <Game.h>
#include "Block.h"
#include "Player.h"
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player() : Character(QPixmap(":/images/res/sprite_0.png"), 65, 68){
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/sprite_" + to_string(i)+ ".png"));
    }
}

void Player::move(enum direction dir)
{
    // left
    if (dir == LEFT) {
        if (collide(LEFT)) return;
        if ((x() - getSpeed()) < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
    }

    //right
    if (dir == RIGHT) {
        if (collide(RIGHT)) return;
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
    }

}

void Player::jump()
{
    if (isOnGround()){
        setVerticalVelocity(jumpVelocity);
        setPos(x(), y()-1);
    }
}

void Player::advance(int step)
{
    if (y() > scene()->height()) emit playerIsDead();

    // player die checking && interaction with trigger
    QList<QGraphicsItem*> collidingitems = collidingItems(Qt::IntersectsItemBoundingRect);
    for (int i = 0; i < collidingitems.size(); ++i){
        if (collidingitems[i]->type() != Block::Type
            && collidingitems[i]->type() != Trigger::Type
                ){
            emit playerIsDead();
            break;
        } else if (collidingitems[i]->type() == Trigger::Type){
            static_cast<Trigger*>(collidingitems[i])->triggered();
        }
    }

    if (step == 0) return;

    // if "W" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_W)) {
        // perform jumping
        jump();
    }

    // if "A" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_A)) {
        // out of view prevention + move to leftwards
        // Cant go back if the player touches the leftmost part of the screen
        if (x() >= scene()->views().first()->horizontalScrollBar()->value()) move(LEFT);

        // animation handler
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }

    // if "D" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_D)) {
        // move to leftwards
        move(RIGHT);

        // animation handler
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
}

// return the QMap record that stores which key(s) is/are currently pressed down
QMap<int, bool> Player::getKeyMap(){
    return keys;
}

// records which key(s) is/are currently pressed down
void Player::setKeyValue(int key, bool value)
{
    keys[key] = value;
}

// override shape() for better hitbox detection
QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(0, 5, getWidth(), getHeight() - 5);
    return path;

}
