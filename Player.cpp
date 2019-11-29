
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
}

void Player::keyPressEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
    keys[e->key()] = true; QGraphicsPixmapItem::keyPressEvent(e);
}

void Player::keyReleaseEvent(QKeyEvent *e)
{
    if (e->isAutoRepeat()) return;
   keys[e->key()] = false; QGraphicsPixmapItem::keyReleaseEvent(e);
}

void Player::update()
{
    Game * game = static_cast<Game*>(scene()->views().first());
    if(keys[Qt::Key_A]) setPos(x()-2, y());
    if(keys[Qt::Key_D]) setPos(x()+2, y());
    if(keys[Qt::Key_Space]) {
        if (!inAir){
            setVerticalSpeed(-500.0/120);
            setVerticalVelocity(0.0);
            inAir = true;
        }
    }
    if(keys[Qt::Key_S]) setPos(x(), y()+4);
    if(inAir){
        if (y() + verticalSpeed + height >= game->WIN_HEIGHT){
            setPos(x(), game->WIN_HEIGHT-height);
            setVerticalSpeed(0.0);
            setVerticalVelocity(0.0);
            inAir = false;
        } else {
            setPos(x(), y()+verticalSpeed);
            setVerticalSpeed(verticalSpeed + verticalVelocity);
            setVerticalVelocity(verticalVelocity + verticalAcceleration);
            cout << "verticalSpeed: " << verticalSpeed << endl;
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
    if(y() + height == static_cast<double>(game->WIN_WIDTH)){
        inAir = false;
        return true;
    } else {
        setVerticalSpeed(0.0);
        return false;
    }
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

void Player::setVerticalSpeed(double speed){
    this->verticalSpeed = speed;
}

void Player::setVerticalVelocity(double velocity){
    this->verticalVelocity = velocity;
}
