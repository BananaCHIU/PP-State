#include "Raptor.h"

Raptor::Raptor(QPixmap image, int width, int height): Character(image, width, height)
{
    // random x & y
    // get Player pos
    // calculate the angle
    // rotate raptor
    // set the vertical and horizontal speed
}

enum direction Raptor::getMovingDirection()
{
    return movingDirection;
}

void Raptor::flipMovingDirection()
{
    movingDirection = movingDirection == LEFT? RIGHT : LEFT;
}

void Raptor::move(direction dir)
{

}

void Raptor::advance(int step)
{
    if (step == 0) return;
}
