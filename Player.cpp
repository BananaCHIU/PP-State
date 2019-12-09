
#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player(QPixmap image) : Character(image, 65, 68){
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
    if (step == 0) return;
    if(getKeyMap().value(Qt::Key_W)) {
        jump();
    }
    if(getKeyMap().value(Qt::Key_A)) {
        move(LEFT);
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/sprite_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
            setPixmap(QPixmap(QString::fromStdString(s)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    if(getKeyMap().value(Qt::Key_D)) {
        move(RIGHT);
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/sprite_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
            setPixmap(QPixmap(QString::fromStdString(s)).transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
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

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(0, 5, getWidth(), getHeight() - 5);
    return path;
}
