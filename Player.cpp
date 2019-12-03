
#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player(QPixmap image,int width,int height) {
    setPixmap(image);
    this->width = width;
    this->height = height;
    this->verticalVelocity = 0.0;
    this->direction = LEFT;
}

void Player::focusOutEvent(QFocusEvent *event){
    setFocus();
}

bool Player::isOnGround()
{
    Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 1, pos().y() + height, QTransform()));
    Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + width - 1, pos().y() + height, QTransform()));
    if (blockA == nullptr && blockB == nullptr) return false;
    else {
        setVerticalVelocity(0.0);
        return true;
    }
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
    return verticalAcceleration;
}

double Player::getVerticalVelocity() const
{
    return verticalVelocity;
}

void Player::move(enum direction dir)
{
    // left
    if (dir == LEFT) {
        if (getDirection() != LEFT) flipDirection();
        if (collide(LEFT)) return;
        if (x() - speed < 0)  setPos(0, y());
        else setPos(x()- speed, y());
    }

    //right
    if (dir == RIGHT) {
        if (getDirection() != RIGHT) flipDirection();
        if (collide(RIGHT)) return;
        if (x() + getWidth() + speed > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ speed, y());
    }

}

void Player::jump()
{
    if (isOnGround()){
        setVerticalVelocity(-550/120);
        setPos(x(), y()-1);
    }
}

bool Player::collide(enum direction direction)
{
    switch(direction){
    case LEFT:
    {

        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() - speed, pos().y() + 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() - speed, pos().y() + height - 1, QTransform()));
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
        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + speed + width, pos().y() + 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + speed + width, pos().y() + height - 1, QTransform()));
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
        }
        break;
    }

    case DOWNWARD:
    {
        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 1, pos().y() + height + verticalVelocity, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + width - 1, pos().y() + height + verticalVelocity, QTransform()));
        if (blockA != nullptr){
            setPos(pos().x(), blockA->y() - height);
            return true;
        }

        if (blockB != nullptr){
            setPos(pos().x(), blockB->y() - height);
            return true;
        }
    break;
    }
    }
    return false;
}

void Player::setVerticalVelocity(double velocity){
    this->verticalVelocity = velocity;
}

int Player::getWidth() const{
    return width;
}

int Player::getHeight() const{
    return height;
}

double Player::getSpeed() const{
    return speed;
}
