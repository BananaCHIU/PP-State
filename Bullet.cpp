#include  "Bullet.h"
#include <QGraphicsScene>

Bullet::Bullet(direction movingDirection): Character(QPixmap(":/images/res/bullet.png"), 18, 38)
{
    // modify horizontal movement speed
    setSpeed(4);
    // set the moving direction
    this->movingDirection = movingDirection;
}

enum direction Bullet::getMovingDirection()
{
    return movingDirection;
}

int Bullet::type() const
{
    return Type;
}

void Bullet::move(direction dir)
{
    // move upward
    if (dir == UPWARD){
        setPos(x(), y() - getSpeed());
    }else if(dir == LEFT){ // move leftward
        if (collide(LEFT) || collide(RIGHT)|| collide(UPWARD) || collide(DOWNWARD)) {
            // emit signal asking for deletion upon collision
            emit hitBlock();
            return;
        }
        // out of scene case
        if (x() - getSpeed() < 0)  {
            // emit signal for deletion upon collision
            emit hitBlock();
            return;
        }
        else setPos(x() - getSpeed(), y()); // normal case, just move to left
    } else if(dir == RIGHT){ // move rightward
        if (collide(LEFT) || collide(RIGHT)|| collide(UPWARD) || collide(DOWNWARD)) {
            // emit signal asking for deletion upon collision
            emit hitBlock();
            return;
        }
        // out of scene case
        if (x() + getSpeed() < 0)  {
            emit hitBlock();
            return;
        }
        else setPos(x() + getSpeed(), y()); // normal case, just move to right
    }
}

void Bullet::advance(int step)
{
    if (step == 0) return; // ignore indication step
    move(getMovingDirection()); // update position
}


