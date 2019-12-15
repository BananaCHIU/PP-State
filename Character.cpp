#include "Block.h"
#include "Character.h"

#include <QGraphicsScene>
#include <QPixmapCache>

// constructor
Character::Character(QPixmap image,int width, int height) :
    width(width),
    height(height)
{
    //setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    //QPixmapCache::setCacheLimit(102400);
    setPixmap(image);   // set character image
    this->setShapeMode(QGraphicsPixmapItem::MaskShape);
    // MaskShape mode allows complex image shape
    // and it ignores transparent parts
    // totaly something we need for our character collision
}

// accessors
enum direction Character::getFacing() const
{
    return facing;
}

int Character::getHeight() const
{
    return height;
}

double Character::getSpeed() const
{
    return speed;
}

double Character::getVerticalVelocity() const
{
    return verticalVelocity;
}

int Character::getWidth() const
{
    return width;
}

int Character::type() const
{
    return Type;
}

// mutator
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

void Character::setWidth(int width)
{
    this->width = width;
}

// other methods
bool Character::collide(enum direction dir){
    // collision checking using pixmapitems' bounding rectangle
    switch(dir){
    case LEFT:
        {
            // check 3 points on the left of the character with top, bottom and centered y-coordinate
            // the methods checks x-coordinate on which the player is going to move to
            // if any of the coordinate hits a block, return true.
            QGraphicsItem *objectA = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().top() + 1, QTransform()));
            QGraphicsItem *objectB = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().bottom() - 1, QTransform()));
            QGraphicsItem *objectC = (scene()->itemAt(pos().x() - getSpeed() + boundingRect().left(), pos().y() + shape().boundingRect().center().y(), QTransform()));

            // if there is a block in any of the point return true;
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

void Character::flipFacing()
{
    // change character facing and flip the image horiztally
    facing = facing == LEFT ? RIGHT : LEFT;
    setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

bool Character::isOnGround()
{
    // check the bottom-left, bottom-mid and bottom-right points of the character
    // if any of the point collides with block, set the vertically velocity zero
    // and return true, meaning the character is now standing on a block
    QGraphicsItem *objectA = scene()->itemAt(pos().x() + 1, pos().y() + height, QTransform());
    QGraphicsItem *objectB = scene()->itemAt(pos().x() + width - 1, pos().y() + height, QTransform());
    QGraphicsItem *objectC = scene()->itemAt(pos().x() + width/2, pos().y() + height, QTransform());
    if ((objectA != nullptr && objectA->type() == Block::Type)
        || (objectB != nullptr && objectB->type() == Block::Type)
        || (objectC != nullptr && objectC->type() == Block::Type)) {
        setVerticalVelocity(0.0);
        return true;
    } else return false;
}
