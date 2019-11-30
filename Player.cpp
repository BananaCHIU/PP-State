
#include <Game.h>
#include <QObject>
#include <Player.h>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;

Player::Player(QPixmap image,int width,int height) {
    setPixmap(image);
    this->width = width;
    this->height = height;
    this->verticalSpeed = 0.0;
    this->direction = LEFT;
}



void Player::gravity()
{
    Game * game = static_cast<Game*>(scene()->views().first());
    if(inAir){
        if (y() + verticalSpeed + height >= game->getWinHeight()){
            setPos(x(), game->getWinHeight()-height);
            setVerticalSpeed(0.0);
            setVerticalVelocity(0.0);
            inAir = false;
        } else {
            setPos(x(), y()+verticalSpeed);
            setVerticalSpeed(verticalSpeed + verticalVelocity);
            setVerticalVelocity(verticalVelocity + verticalAcceleration);
            //cout << "verticalSpeed: " << verticalSpeed << endl;
        }
    }
}

void Player::focusOutEvent(QFocusEvent *event){
    setFocus();
}

bool Player::isOnGround()
{
    // not final implementation, just testing.
    Game * game = static_cast<Game*>(scene()->views().first());
    if(y() + height == static_cast<double>(game->getWinWidth())){
        inAir = false;
        return true;
    } else {
        setVerticalSpeed(0.0);
        return false;
    }
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

bool Player::getInAir(){
    return this->inAir;
}

double Player::getVerticalAceleration()
{
    return verticalAcceleration;
}

double Player::getVerticalVelocity()
{
    return verticalVelocity;
}

double Player::getVerticalSpeed()
{
    return verticalSpeed;
}

void Player::setInAir(){
    this->inAir = true;
}

void Player::setNotInAir(){
    this->inAir = false;
}

void Player::setVerticalSpeed(double speed){
    this->verticalSpeed = speed;
}

void Player::setVerticalVelocity(double velocity){
    this->verticalVelocity = velocity;
}

int Player::getWidth(){
    return width;
}
