#include <Dog.h>
#include <Character.h>

#include <QGraphicsScene>

Dog::Dog(QPixmap image, int width, int height): Character(image, width, height){
    setVerticalVelocity(0.0);
    setSpeed(3.0);
}

enum direction Dog::getMovingDirection()
{
    return movingDirection;
}

void Dog::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT? RIGHT : LEFT;
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

void Dog::advance(int step)
{
    if (step==0) return;
    move(getMovingDirection());
}
