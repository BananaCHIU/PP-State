#include "PoCar.h"
#include "Bullet.h"
#include "Game.h"
#include <QGraphicsScene>

PoCar::PoCar(): Character(QPixmap(":/images/res/car_0.png"), 217, 110)
{
    sprites[0] = QPixmap(QString::fromStdString(":/images/res/car_0.png"));
    sprites[1] = QPixmap(QString::fromStdString(":/images/res/car_1.png"));

    setVerticalVelocity(0.0);
    setSpeed(0.0);
}

PoCar::PoCar(direction facingDirection): Character(QPixmap(":/images/res/car_0.png"), 217, 110)
{
    setVerticalVelocity(0.0);
    setSpeed(0.0);
    this->facingDirection = facingDirection;
}

enum direction PoCar::getFacingDirection()
{
    return facingDirection;
}

void PoCar::deleteBullet(){
    scene()->removeItem(bullet);
    static_cast<Game*>(scene()->views().first())->getBulletList()->removeAll(bullet);
    delete bullet;
    bullet = nullptr;
}

void PoCar::shoot(){

    bullet = new Bullet(facingDirection);
    if (facingDirection == LEFT){
        bullet->setTransformOriginPoint(bullet->getWidth()/2, bullet->getHeight()/2);
                bullet->setRotation(-90);
        bullet->setPos(this->x() - bullet->getWidth()/2, this->y() + this->getHeight()/6);
    }else if(facingDirection == RIGHT){
        bullet->setTransformOriginPoint(bullet->getWidth()/2, bullet->getHeight()/2);
                bullet->setRotation(90);
        bullet->setPos(this->x() + this->getWidth() + bullet->getWidth()/2, this->y() + this->getHeight()/6);
    }

    connect(bullet, SIGNAL(hitBlock()), this, SLOT(deleteBullet()));
    static_cast<Game*>(scene()->views().first())->getBulletList()->append(bullet);
    scene()->addItem(bullet);

}

void PoCar::move(enum direction dir){

}

void PoCar::advance(int step)
{
    if (step == 0) return;
    if(getFacing()!= getFacingDirection()) flipFacing();
    // handles the animation
        if (anim_count % (ANIM_RATIO * 2) == 0) {
             setPixmap(sprites[anim_count / (ANIM_RATIO * 2)]);
        }
        if (anim_count == (ANIM_RATIO * 2 * 2) - 1){
            anim_count = 0;
        }
        else ++anim_count;
        if (bullet == nullptr) shoot();
}

int PoCar::type() const
{
    return Type;
}
