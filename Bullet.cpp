#include  "Bullet.h"
#include <QGraphicsScene>


Bullet::Bullet() : Character(QPixmap(":/images/res/bullet.png"), 18, 38)
{
    setSpeed(1);
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
            scene()->removeItem(this);

        }
        else setPos(x()- getSpeed(), y());
    }
}

void Bullet::advance(int step)
{
    if (step == 0) return;
    move(LEFT);
}

int Bullet::type() const
{
    return Type;
}
