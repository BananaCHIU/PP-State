
#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player() : Character(QPixmap(":/images/res/sprite_0.png"), 65, 68){
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/sprite_" + to_string(i)+ ".png"));
    }
<<<<<<< HEAD
}

void Player::flipDirection()
{
     direction = direction == LEFT ? RIGHT : LEFT;
     setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

int Player::getDirection() const{
    if (direction == LEFT) return 0;
    else return 1;
}

double Player::getVerticalAcceleration() const
{
    return VERTICALACCELERATION;
}

double Player::getVerticalVelocity() const
{
    return verticalVelocity;
=======
    setVerticalVelocity(0.0);
>>>>>>> monster
}

void Player::move(enum direction dir)
{
    // left
    if (dir == LEFT) {
<<<<<<< HEAD
        //if (getDirection() != LEFT) flipDirection();
        if (collide(LEFT)) return;
        if (x() - SPEED < 0)  setPos(0, y());
        else setPos(x()- SPEED, y());
=======
        if (getFacing() != LEFT) flipFacing();
        if (collide(LEFT)) return;
        if (x() - getSpeed() < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
>>>>>>> monster
    }

    //right
    if (dir == RIGHT) {
<<<<<<< HEAD
        //if (getDirection() != RIGHT) flipDirection();
        if (collide(RIGHT)) return;
        if (x() + getWidth() + SPEED > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ SPEED, y());
=======
        if (getFacing() != RIGHT) flipFacing();
        if (collide(RIGHT)) return;
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
>>>>>>> monster
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
<<<<<<< HEAD
    switch(direction){
    case LEFT:
    {

        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() - SPEED, pos().y() + 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() - SPEED, pos().y() + height - 1, QTransform()));
        if (blockA != nullptr){
            setPos(blockA->pos().x() + blockA->getWidth(), y());
            return true;
        }

        if (blockB != nullptr){
            setPos(blockB->pos().x() + blockB->getWidth(), y());
            return true;
        }

        break;
    }

    case RIGHT:
    {
        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + SPEED + width, pos().y() + 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + SPEED + width, pos().y() + height - 1, QTransform()));
        if (blockA != nullptr){
            setPos(blockA->pos().x() - width, y());
            return true;
        }

        if (blockB != nullptr){
            setPos(blockB->pos().x() - width, y());
            return true;
        }
       break;
     }
    case UPWARD:
    {
        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 1, pos().y() + verticalVelocity, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + width - 1, pos().y() + verticalVelocity, QTransform()));
        if (blockA != nullptr){
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
        }

        if (blockB != nullptr){
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
=======
    if (step == 0) return;
    if(getKeyMap().value(Qt::Key_W)) {
        jump();
    }
    if(getKeyMap().value(Qt::Key_A)) {
        move(LEFT);
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
>>>>>>> monster
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    if(getKeyMap().value(Qt::Key_D)) {
        move(RIGHT);
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
}

QMap<int, bool> Player::getKeyMap(){
    return keys;
}

void Player::setKeyValue(int key, bool value)
{
    keys[key] = value;
}

<<<<<<< HEAD
double Player::getSpeed() const{
    return SPEED;
=======
QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(0, 5, getWidth(), getHeight() - 5);
    return path;
>>>>>>> monster
}
