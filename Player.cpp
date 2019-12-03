
#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player(QPixmap image,int width,int height) : Character(image, width, height){
    setVerticalVelocity(0.0);
}

void Player::move(enum direction dir)
{
    // left
    if (dir == LEFT) {
        if (getFacing() != LEFT) flipFacing();
        if (collide(LEFT)) return;
        if (x() - getSpeed() < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
    }

    //right
    if (dir == RIGHT) {
        if (getFacing() != RIGHT) flipFacing();
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

}

