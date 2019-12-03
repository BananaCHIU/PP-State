#include <Dog.h>
#include <Character.h>

#include <QGraphicsScene>

Dog::Dog(QPixmap image, int width, int height): Character(image, width, height){
    setVerticalVelocity(0.0);

}

enum direction Dog::getMovingDirection()
{
    return movingDirection;
}

void Dog::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT? RIGHT : LEFT;
    //if (movingDirection == LEFT) setPos(x() - 1, y());
    //else setPos(x() + 1, y());
}

void Dog::move(enum direction dir)
{
    if(dir == LEFT){
        if(getFacing()!= getMovingDirection()) flipFacing();// flip facing and the pixmap
        if (collide(LEFT)) {
            flipMovingDirection(); // change the moving direction
            return;
        }
        if (x() - getSpeed() < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
    } else {
        if(getFacing()!= getMovingDirection()) flipFacing();// flip facing and the pixmap
        if (collide(RIGHT)) {
            flipMovingDirection(); // change the moving direction
            return;
        }
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
    }
    // to be implemented
    // move horizontally, change moving direction when hitting blocks

}

bool Dog::collide(enum direction dir){
    // to be implemented
    return Character::collide(dir);
}

void Dog::advance(int step)
{
    if (step==0) return;
    move(getMovingDirection());
}
