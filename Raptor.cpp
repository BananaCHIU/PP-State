#include "Block.h"
#include "Raptor.h"
#include <QGraphicsScene>
#include <math.h>
Raptor::Raptor(QPixmap image) : Character(image, 154, 92)
{

}

Raptor::Raptor(QPixmap image, int width, int height): Character(image, width, height)
{

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

void Raptor::move(direction dir)
{
    if(dir == LEFT){
        if(getFacing()!= getMovingDirection()) flipFacing();// flip facing and the pixmap
        if (isOnGround()){
            double acceleration = static_cast<Game*>(scene()->views().first())->getVerticalAcceleration();
            int time =  static_cast<int>(ceil((0.0 - jumpVelocity) / acceleration));
            double destination = getSpeed() * time + 1 / 2.0 * acceleration * pow(time, 2);
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() - destination + 64, pos().y() + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() - destination + 64, pos().y() + getHeight() - 1, QTransform()));
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
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() + destination + getWidth(), pos().y() + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() + destination + getWidth(), pos().y() + getHeight() - 1, QTransform()));
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
    setSpeed(getSpeed() + horizontalAcceleration);
}

enum direction Raptor::getMovingDirection()
{
    return movingDirection;
}
