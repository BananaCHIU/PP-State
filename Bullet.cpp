#include  "Bullet.h"
#include <QGraphicsScene>

Bullet::Bullet(direction movingDirection): Character(QPixmap(":/images/res/bullet.png"), 18, 38)
{
    setSpeed(4);
    this->movingDirection = movingDirection;
}

enum direction Bullet::getMovingDirection()
{
    return movingDirection;
}

void Bullet::move(direction dir)
{
    if (dir == UPWARD){
        setPos(x(), y() - getSpeed());
    }else if(dir == LEFT){
        if (collide(LEFT) || collide(RIGHT)|| collide(UPWARD) || collide(DOWNWARD)) {
            // delete itself if collides with block
            emit hitBlock();
            return;
        }
        // out of scene prevention, remove later
        if (x() - getSpeed() < 0)  {
            emit hitBlock();
            return;
        }
        else setPos(x() - getSpeed(), y());
    }else if(dir == RIGHT){
    if (collide(LEFT) || collide(RIGHT)|| collide(UPWARD) || collide(DOWNWARD)) {
        // delete itself if collides with block
        emit hitBlock();
        return;
    }
    // out of scene prevention, remove later
    if (x() + getSpeed() < 0)  {
        emit hitBlock();
        return;
    }
    else setPos(x() + getSpeed(), y());
}
}

void Bullet::advance(int step)
{
    if (step == 0) return;
    move(getMovingDirection());
}

int Bullet::type() const
{
    return Type;
}
