#include "Block.h"
#include "Raptor.h"
#include <QGraphicsScene>
#include <math.h>
#include <iostream>
using namespace std;
Raptor::Raptor(QPixmap image) : Character(image, 154, 92)
{

}

Raptor::Raptor(QPixmap image, direction movingDirection) : Character(image, 154, 92)
{
    this->movingDirection = movingDirection;
}

void Raptor::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT ? RIGHT : LEFT;
}

void Raptor::jump()
{
    if (isOnGround()){
        setVerticalVelocity(jumpVelocity);
        setPos(x(), y()-1);
    }
}
// handles raptor's moving behaviors
void Raptor::move(direction dir)
{
    // a raptor accelerates until it's horizontal speed reaches the MAX_SPEED
    // a raptor will jump onto a block which is 1 level higher than where it's standing
    // a raptor will jump from a distanced range and land on the block
    // a raptor will not change its direction
    if(dir == LEFT){
        if(getFacing()!= getMovingDirection()) flipFacing();// flip facing and the pixmap
        if (isOnGround()){

            // calculate the tick it requires to reach the highest distance from ground
            // use the calculated tick and it's acceleration to calculate the checking distance
            double acceleration = static_cast<Game*>(scene()->views().first())->getVerticalAcceleration();    
            int time =  static_cast<int>(ceil((0.0 - jumpVelocity) / acceleration));
            double destination = getSpeed() * time + 1 / 2.0 * acceleration * pow(time, 2);
            // check if there is a block in the destination, perform a "perfect" jumping if there is one
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() + shape().boundingRect().left() - destination, pos().y() + getHeight() - 64 + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() + shape().boundingRect().left() - destination, pos().y() + getHeight() - 1, QTransform()));
            if (objectA != nullptr && objectA->type() == Block::Type){
                jump();
            }

            if (objectB != nullptr && objectB->type() == Block::Type){
                jump();
            }
        }
        if (collide(LEFT)) {
            jump();
            return;
        }
        if (x() - getSpeed() < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
    } else {
        if(getFacing()!= getMovingDirection()) flipFacing();// flip facing and the pixmap
        if (isOnGround()){
            double acceleration = static_cast<Game*>(scene()->views().first())->getVerticalAcceleration();
            int time =  static_cast<int>(floor((0.0 - jumpVelocity) / acceleration));
            double destination = getSpeed() * time + 1 / 2.0 * acceleration * pow(time, 2);
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() + destination + shape().boundingRect().right(), pos().y() + getHeight() - 64 + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() + destination + shape().boundingRect().right(), pos().y() + getHeight() - 1, QTransform()));
            if (objectA != nullptr && objectA->type() == Block::Type){
                jump();
            }
            if (objectB != nullptr && objectB->type() == Block::Type){
                jump();
            }
        }
        if (collide(RIGHT)) {
            jump();
            return;
        }
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
    }
}

void Raptor::advance(int step)
{
    if (step == 0) return;
    move(movingDirection);

    if (movingDirection == LEFT){
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/green_raptor_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
            setPixmap(QPixmap(QString::fromStdString(s)).transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    } else if (movingDirection == RIGHT) {
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/green_raptor_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
                        setPixmap(QPixmap(QString::fromStdString(s)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
    // accelerates until reaching the max speed
    if (getSpeed() < MAX_SPEED) setSpeed(getSpeed() + horizontalAcceleration);

}

enum direction Raptor::getMovingDirection()
{
    return movingDirection;
}

QPainterPath Raptor::shape() const
{
    QPainterPath path;
    path.addRect(56, 0, 133-56, getHeight());
    return path;
}
