
#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include <QScrollBar>
#include <QTimer>
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
    if (step == 0) return;
        if(getKeyMap().value(Qt::Key_W)) {
            jump();
        }
        if(getKeyMap().value(Qt::Key_A)) {

            //Cant go back if the player touches the leftmost part of the screen
            if (x() >= scene()->views().first()->horizontalScrollBar()->value()) move(LEFT);

            if (anim_count % (ANIM_RATIO * 4) == 0) {
                setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
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

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(0, 5, getWidth(), getHeight() - 5);
    return path;

}
