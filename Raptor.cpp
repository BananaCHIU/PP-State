#include "Block.h"
#include "Raptor.h"
#include "Game.h"
#include <QGraphicsScene>
#include <math.h>
#include <iostream>
using namespace std;
Raptor::Raptor() : Character(QPixmap(":/images/res/green_raptor_0.png"), 154, 92)
{
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/green_raptor_" + to_string(i)+ ".png"));
    }
    this->setSpeed(1.5);
}

Raptor::Raptor(direction movingDirection) : Character(QPixmap(":/images/res/green_raptor_0.png"), 154, 92)
{
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/green_raptor_" + to_string(i)+ ".png"));
    }
    this->movingDirection = movingDirection;
    this->setSpeed(1.5);
}

void Raptor::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT ? RIGHT : LEFT;
}

void Raptor::jump()
{
    // add velocity to the raptor
    if (isOnGround()){
        setVerticalVelocity(jumpVelocity);
        // makes further checking of isOnGround() to false in the same tick
        setPos(x(), y()-1);this->setSpeed(1.0);
    }
}
// handles raptor's moving behaviors
void Raptor::move(direction dir)
{
    // a raptor accelerates until it's horizontal speed reaches the MAX_SPEED
    // a raptor will jump onto a block which is 1 level higher than where it's standing
    // a raptor will jump from a distanced range and land on the block
    // a raptor will not change its direction

    // calculate the tick it requires to reach the highest distance from ground
    // use the calculated tick and it's acceleration to calculate the checking distance
    double acceleration = static_cast<Game*>(scene()->views().first())->getVerticalAcceleration();
    int time =  static_cast<int>(ceil((0.0 - jumpVelocity) / acceleration));
    double destination = getSpeed() * time + 1 / 2.0 * acceleration * pow(time, 2);

    // flip facing and the pixmap if the facing and moving direction are not the same
    if(getFacing()!= getMovingDirection()) flipFacing();

    // in case the character is moving leftward:
    if(dir == LEFT){
        // jumping mechanism of the raptor
        if (isOnGround()){
            // check if there is a block in the destination, perform a "perfect" jumping if there is one
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() + shape().boundingRect().left() - destination, pos().y() + getHeight() - 64 + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() + shape().boundingRect().left() - destination, pos().y() + getHeight() - 1, QTransform()));
            // jump if there is any block in the checking points
            if (objectA != nullptr && objectA->type() == Block::Type){
                jump();
            }

            if (objectB != nullptr && objectB->type() == Block::Type){
                jump();
            }
        }
        if (collide(LEFT)) {
            flipMovingDirection();
            //jump();

            return;
        }
        // out of scene prevention, remove later
        if (x() - getSpeed() < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());

        // in case moving rightward:
    } else {
        // flip facing and the pixmap if the facing and moving direction are not the same
        if(getFacing()!= getMovingDirection()) flipFacing();
        // jump if there is any block in the checking points
        if (isOnGround()){
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
            flipMovingDirection();
            //jump();
            return;
        }
        // out of scene prevention, remove later
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
    }
}

// called by scene->advance, update everything about the raptor
void Raptor::advance(int step)
{
    if (step == 0) return;
    // let the raptor move
    move(movingDirection);

    // handles the animation of raptor
    if (movingDirection == LEFT){
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    } else if (movingDirection == RIGHT) {
        if (anim_count % (ANIM_RATIO * 4) == 0) {
             setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }

    // accelerates until reaching the max speed
    if (getSpeed() < MAX_SPEED) setSpeed(getSpeed() + horizontalAcceleration);

}

// returns the direction that the raptor is moving towards
enum direction Raptor::getMovingDirection()
{
 return movingDirection;
}

// override the shape of the character for better hitbox detection
/*QPainterPath Raptor::shape() const
{
    QPainterPath path;
    path.addRect(56, 0, 133-56, getHeight());
    return path;
}*/

int Raptor::type() const{
    return Type;
}
