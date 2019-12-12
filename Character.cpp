#include "Block.h"
#include "Character.h"

#include <QGraphicsScene>
#include <QPixmapCache>
Character::Character(QPixmap image,int width, int height) :
    width(width),
    height(height)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    QPixmapCache::setCacheLimit(102400);
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

enum direction Character::getFacing() const
{
    return facing;
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

void Character::setSpeed(double speed)
{
    this->speed = speed;
}

void Character::setVerticalVelocity(double velocity)
{
    this->verticalVelocity = velocity;
}

bool Character::isOnGround()
{
    //QGraphicsItem *objectA = scene()->itemAt(pos().x() + shape().boundingRect().left() + 1, pos().y() + shape().boundingRect().bottom(), QTransform());
    //QGraphicsItem *objectB = scene()->itemAt(pos().x() + shape().boundingRect().right() - 1, pos().y() + shape().boundingRect().bottom(), QTransform());
    QGraphicsItem *objectA = scene()->itemAt(pos().x() + 1, pos().y() + height, QTransform());
    QGraphicsItem *objectB = scene()->itemAt(pos().x() + width - 1, pos().y() + height, QTransform());
    if ((objectA != nullptr && objectA->type() == Block::Type)
        || (objectB != nullptr && objectB->type() == Block::Type)) {
        setVerticalVelocity(0.0);
        return true;
    } else return false;
}

void Character::flipFacing()
{
    facing = facing == LEFT ? RIGHT : LEFT;
    setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

bool Character::collide(enum direction dir){
    //QList<QGraphicsItem*> objects = collidingItems(Qt::IntersectsItemBoundingRect);
    switch(dir){
    case LEFT:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().top() + 1, QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().bottom() - 1, QTransform()));
        QGraphicsItem *objectC = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().center().y(), QTransform()));
        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(objectA->pos().x() - boundingRect().left() + static_cast<Block*>(objectA)->getWidth(), y());
            return true;
        }
        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(objectB->pos().x() - boundingRect().left() + static_cast<Block*>(objectB)->getWidth(), y());
            return true;
        }
        if (objectC != nullptr && objectC->type()==Block::Type){
            setPos(objectC->pos().x() - boundingRect().left() + static_cast<Block*>(objectC)->getWidth(), y());
            return true;
        }
       break;
    }

    case RIGHT:
    {
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() + getSpeed() + boundingRect().right(), pos().y() + shape().boundingRect().top() + 1, QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() + getSpeed() + boundingRect().right(), pos().y() + shape().boundingRect().bottom() - 1, QTransform()));
        QGraphicsItem *objectC = (scene()->itemAt(pos().x() + getSpeed() + boundingRect().right(), pos().y() + shape().boundingRect().center().y(), QTransform()));

        if (objectA != nullptr && objectA->type()==Block::Type){
            setPos(objectA->pos().x() - getWidth(), y());
            return true;
        }

        if (objectB != nullptr && objectB->type()==Block::Type){
            setPos(objectB->pos().x() - getWidth(), y());
            return true;
        }

        if (objectC != nullptr && objectC->type()==Block::Type){
            setPos(objectC->pos().x() - getWidth(), y());
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
        QGraphicsItem *objectA = (scene()->itemAt(pos().x() + shape().boundingRect().left() + 1, pos().y() + getHeight() + getVerticalVelocity(), QTransform()));
        QGraphicsItem *objectB = (scene()->itemAt(pos().x() + + shape().boundingRect().right() - 1, pos().y() + getHeight() + getVerticalVelocity(), QTransform()));

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
