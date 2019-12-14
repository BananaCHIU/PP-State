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
    setVerticalVelocity(0.0);
    setSpeed(3.0);
}

Dog::Dog(direction movingDirection): Character( QPixmap(":/images/res/dog_0.png"), 100, 59)
{
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/dog_" + to_string(i)+ ".png"));
    }
    setVerticalVelocity(0.0);
    setSpeed(3.0);
    this->movingDirection = movingDirection;
}

enum direction Dog::getMovingDirection()
{
    return movingDirection;
}

// change the moving direction of the dog
void Dog::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT? RIGHT : LEFT;
}

// handles dog movement and behaviors
void Dog::move(enum direction dir)
{
    // move horizontally, change moving direction while hitting blocks

    // flip facing and the pixmap if the facing and moving direction are not the same
    if(getFacing()!= getMovingDirection()) flipFacing();

    // in case moving leftward:
    if(dir == LEFT){
        if (collide(LEFT)) {
            // change the moving direction if collides with block
            flipMovingDirection();
            return;
        }
        // out of scene prevention, remove later
        if (x() - getSpeed() < 0)  {
            setPos(0, y());
            flipMovingDirection();
        }
        else setPos(x()- getSpeed(), y());

    // in case moving rightward:
    } else {
        if (collide(RIGHT)) {
            // change the moving direction if collides with block
            flipMovingDirection();
            return;
        }
        // out of scene prevention, remove later
        if (x() + getWidth() + getSpeed() > scene()->width()) {
            setPos(scene()->width() - getWidth(), y());
            flipMovingDirection();
        }
        else setPos(x()+ getSpeed(), y());
    }
}

// called by scene->advance(), handles dog movement and animation
void Dog::advance(int step)
{
    if (step==0) return;
    // let the dog move
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
