#include "PoCar.h"
#include "Bullet.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QMediaPlayer>

PoCar::PoCar(): Character(QPixmap(":/images/res/car_0.png"), 217, 110)
{
    sprites[0] = QPixmap(QString::fromStdString(":/images/res/car_0.png"));
    sprites[1] = QPixmap(QString::fromStdString(":/images/res/car_1.png"));

    setVerticalVelocity(0.0);
    setSpeed(0.0);
}

PoCar::PoCar(direction facing): Character(QPixmap(":/images/res/car_0.png"), 217, 110)
{
    sprites[0] = QPixmap(QString::fromStdString(":/images/res/car_0.png"));
    sprites[1] = QPixmap(QString::fromStdString(":/images/res/car_1.png"));

    sound.setMedia(QUrl("qrc:/music/res/shooting.wav"));
    sound.setVolume(2);

    setVerticalVelocity(0.0);
    setSpeed(0.0);
    this->facingDirection = facing;
    shootTimer = new QTimer();
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    shootTimer->setInterval(1500);
    shootTimer->start();
}

PoCar::~PoCar(){
    disconnect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    shootTimer->stop();
    delete shootTimer;
}

void PoCar::shoot(){
    // shoot a bullet
    Bullet* bullet = new Bullet(facingDirection);
    if (sound.state() == QMediaPlayer::PlayingState) sound.setPosition(0);
    else if(sound.state() == QMediaPlayer::StoppedState) sound.play();
    if (facingDirection == LEFT){
        bullet->setTransformOriginPoint(bullet->getWidth()/2, bullet->getHeight()/2);
                bullet->setRotation(-90);
        bullet->setPos(this->x() - bullet->getWidth() / 2, this->y() + this->getHeight()/6);
    }else if(facingDirection == RIGHT){
        bullet->setTransformOriginPoint(bullet->getWidth()/2, bullet->getHeight()/2);
                bullet->setRotation(90);
        bullet->setPos(this->x() + this->getWidth() + bullet->getWidth()/2, this->y() + this->getHeight()/6);
    }
    // signal and slot connection
    connect(bullet, SIGNAL(hitBlock()), static_cast<Game*>(scene()->views().first()), SLOT(deleteBullet()));
    // add the bullet to the data structure for updates and management
    static_cast<Game*>(scene()->views().first())->getBulletList()->append(bullet);
    // add the bullet to scene
    scene()->addItem(bullet);
}

void PoCar::move(enum direction dir){

}

void PoCar::advance(int step)
{
    if (step == 0) return;
    // handles the animation
    if (facingDirection == LEFT){
        if (anim_count % (ANIM_RATIO * 2) == 0) {
             setPixmap(sprites[anim_count / (ANIM_RATIO * 2)].transformed(QTransform().scale(-1,1)));
        }
            if (anim_count == (ANIM_RATIO * 2 * 2) - 1){
                anim_count = 0;
            }
        else ++anim_count;
    } else if (facingDirection == RIGHT){
        if (anim_count % (ANIM_RATIO * 2) == 0) {
             setPixmap(sprites[anim_count / (ANIM_RATIO * 2)]);
            if (anim_count == (ANIM_RATIO * 2 * 2) - 1){
                anim_count = 0;
            }
        else ++anim_count;
        }
    }
}

int PoCar::type() const
{
    return Type;
}
