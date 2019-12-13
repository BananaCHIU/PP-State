#include <Dog.h>
#include <Character.h>
#include <QGraphicsScene>
#include <iostream>
using namespace std;

Dog::Dog(): Character(QPixmap(":/images/res/dog.png"), 102, 60)
{
    setVerticalVelocity(0.0);
    setSpeed(3.0);
}

Dog::Dog(direction movingDirection): Character( QPixmap(":/images/res/dog.png"), 102, 60)
{
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
    move(getMovingDirection());

    // handle animation
    /*if (movingDirection == LEFT){
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/green_raptor_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
            setPixmap(QPixmap(QString::fromStdString(s)).transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    } else if (movingDirection == RIGHT) {
        if (anim_count % (anim_ratio * 4) == 0) {
            string s = ":/images/res/green_raptor_" + to_string(anim_count / (anim_ratio * 4)) + ".png";
                        setPixmap(QPixmap(QString::fromStdString(s)));
        }
        if (anim_count == (anim_ratio * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }*/
}

int Dog::type() const
{
    return Type;
}
