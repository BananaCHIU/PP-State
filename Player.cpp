
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
    if (verticalVelocity < 0) return false;
    Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 1, pos().y() + height, QTransform()));
    Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + width - 1, pos().y() + height, QTransform()));
    if (blockA == nullptr && blockB == nullptr) return false;
    return true;
}

void Player::flipDirection()
{
     direction = direction == LEFT ? RIGHT : LEFT;
     setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

int Player::getDirection(){
    if (direction == LEFT) return 0;
    else return 1;
}

double Player::getVerticalAcceleration()
{
    return verticalAcceleration;
}

double Player::getVerticalVelocity()
{
    return verticalVelocity;
}

void Player::move(double dx)
{
    // left
    if (dx < 0) {
        if (getDirection() != LEFT) flipDirection();
        if (collide(LEFT)) return;
        if (x() - 4 < 0)  setPos(0, y());
        else setPos(x()-4, y());
    }

    //right
    if (dx > 0) {
        if (getDirection() != RIGHT) flipDirection();
        if (collide(RIGHT)) return;
        if (x() + getWidth() + 4 > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+4, y());
    }

}

void Player::jump()
{
    if (isOnGround()){
        setVerticalVelocity(-400/120);
        setPos(x(), y()-1);
    }
}

bool Player::collide(enum direction direction)
{
    switch(direction){
    case LEFT:
    {

        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() - 4, pos().y() - 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() - 4, pos().y() + height - 1, QTransform()));
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
        Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 4 + width, pos().y() - 1, QTransform()));
        Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + 4 + width, pos().y() + height - 1, QTransform()));
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
            //setPos(pos().x(), blockA->y() + blockA->getHeight());
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
        }

        if (blockB != nullptr){
            //setPos(pos().x(), blockB->y() + blockB->getHeight());
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
        }
        break;
    }

    case DOWNWARD:
    {
        Block *block = static_cast<Block*>(scene()->itemAt(pos().x(), pos().y() + height + verticalVelocity, QTransform()));
        if (block != nullptr){
            setPos(pos().x(), block->y() - height);
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

int Player::getWidth(){
    return width;
}

int Player::getHeight(){
    return height;
}
