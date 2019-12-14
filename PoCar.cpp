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

PoCar::~PoCar(){

}

void PoCar::deleteBullet(){
    scene()->removeItem(bullet);
    delete bullet;
    bullet = nullptr;
}

void PoCar::shoot(){

    bullet = new Bullet();
    bullet->setTransformOriginPoint(bullet->getWidth()/2, bullet->getHeight()/2);
            bullet->setRotation(-90);
    bullet->setPos(this->x() - bullet->getWidth()/2, this->y());
    connect(bullet, SIGNAL(hitBlock()), this, SLOT(deleteBullet()));
    static_cast<Game>(scene()->views().first()).getCharQueue()->enqueue(bullet);
    scene()->addItem(bullet);

}

void PoCar::move(enum direction dir){

}

void PoCar::advance(int step)
{
    if (step == 0) return;

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
