#include <Dog.h>
#include <Character.h>
#include <QGraphicsScene>
#include <iostream>
using namespace std;

Dog::Dog(): Character(QPixmap(":/images/res/dog_0.png"), 100, 59)
{
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/dog_" + to_string(i)+ ".png"));
    }
    // initialize vertical velocity
    setVerticalVelocity(0.0);
}

Dog::Dog(direction movingDirection): Character( QPixmap(":/images/res/dog_0.png"), 100, 59)
{
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/dog_" + to_string(i)+ ".png"));
    }
    // initialize vertical velocity
    setVerticalVelocity(0.0);
    this->movingDirection = movingDirection;
}

enum direction Dog::getMovingDirection()
{
    return movingDirection;
}

void Dog::flipMovingDirection()
{
    // change the moving direction of the dog
    movingDirection = movingDirection == LEFT? RIGHT : LEFT;
}

void Dog::move(enum direction dir)
{
    // behaviour: move horizontally, change moving direction when colliding with blocks

    // flip facing and the pixmap if the facing and moving direction are not the same
    if(getFacing()!= getMovingDirection()) flipFacing();

    // moving leftward:
    if(dir == LEFT){
        if (collide(LEFT)) {
            // change the moving direction if collides with block
            flipMovingDirection();
            return;
        }
        // flip direction when colliding with scene boundary
        if (x() - getSpeed() < 0)  {
            setPos(0, y());
            flipMovingDirection();
        }
        else setPos(x()- getSpeed(), y()); // normal case, just move

    // moving rightward:
    } else {
        if (collide(RIGHT)) {
            // change the moving direction if collides with block
            flipMovingDirection();
            return;
        }
        // flip direction when colliding with scene boundary
        if (x() + getWidth() + getSpeed() > scene()->width()) {
            setPos(scene()->width() - getWidth(), y());
            flipMovingDirection();
        }
        else setPos(x()+ getSpeed(), y());  // normal case, just move
    }
}

void Dog::advance(int step)
{
    if (step==0) return;    // ignore indication step
    // move character
    move(movingDirection);

    // handle animation
    if (movingDirection == LEFT){
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    } else if (movingDirection == RIGHT) {
        if (anim_count % (ANIM_RATIO * 4) == 0) {
             setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }

}

int Dog::type() const
{
    return Type;
}
