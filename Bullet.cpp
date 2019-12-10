#include  "Bullet.h"


Bullet::Bullet() : Character(QPixmap(":/images/res/bullet.png"), 18, 38)
{
    setSpeed(8);
}

void Bullet::move(direction dir)
{
    if (dir == UPWARD){
        setPos(x(), y() - getSpeed());
    }
}

void Bullet::advance(int step)
{
    if (step == 0) return;
    move(UPWARD);
}

int Bullet::type() const
{
    return Type;
}
