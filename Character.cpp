#include "Block.h"
#include "Character.h"

#include <QGraphicsScene>

Character::Character(QPixmap image,int width, int height) :
    width(width),
    height(height),
    direction(LEFT)
{
    setPixmap(image);
}

int Character::getWidth() const
{
    return width;
}

int Character::getHeight() const
{
    return height;
}

int Character::getDirection() const
{
    return direction;
}

double Character::getVerticalVelocity() const
{
    return verticalVelocity;
}

double Character::getSpeed() const
{
    return speed;
}

void Character::setWidth(int width)
{
    this->width = width;
}

void Character::setHeight(int height)
{
    this->height = height;
}

void Character::setVerticalVelocity(double velocity)
{
    this->verticalVelocity = velocity;
}

bool Character::isOnGround()
{
    Block *blockA = static_cast<Block*>(scene()->itemAt(pos().x() + 1, pos().y() + height, QTransform()));
    Block *blockB = static_cast<Block*>(scene()->itemAt(pos().x() + width - 1, pos().y() + height, QTransform()));
    if (blockA == nullptr && blockB == nullptr) return false;
    else {
        setVerticalVelocity(0.0);
        return true;
    }
}

void Character::flipDirection()
{
    direction = direction == LEFT ? RIGHT : LEFT;
    setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

bool Character::collide(enum direction dir){
    switch(dir){
    case LEFT:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() - getSpeed(), pos().y() + 1, QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() - getSpeed(), pos().y() + getHeight() - 1, QTransform()));

        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(objectA->pos().x() + static_cast<Block*>(objectA)->getWidth(), y());
            return true;
        }
        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(objectB->pos().x() + static_cast<Block*>(objectB)->getWidth(), y());
            return true;
        }
       break;
    }

    case RIGHT:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() + getSpeed() + getWidth(), pos().y() + 1, QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() + getSpeed() + getWidth(), pos().y() + getHeight() - 1, QTransform()));

        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(objectA->pos().x() - getWidth(), y());
            return true;
        }

        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(objectB->pos().x() - getWidth(), y());
            return true;
        }
       break;
     }
    case UPWARD:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() + 1, pos().y() + getVerticalVelocity(), QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() + getWidth() - 1, pos().y() + getVerticalVelocity(), QTransform()));

        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
        }

        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(pos().x(), y());
            setVerticalVelocity(0.0);
            return true;
        }
        break;
    }

    case DOWNWARD:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() + 1, pos().y() + getHeight() + getVerticalVelocity(), QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() + getWidth() - 1, pos().y() + getHeight() + getVerticalVelocity(), QTransform()));

        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(pos().x(), objectA->y() - getHeight());
            return true;
        }

        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(pos().x(), objectB->y() - getHeight());
            return true;
        }

    break;
    }
    }
    return false;
}
