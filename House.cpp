#include "House.h"

House::House(int coorx, int coory):Block(QPixmap(":/images/res/house.png"), coorx ,coory){
    // adjust the image to correct position
    setPos(x(), y()-(363-64));
}

int House::type() const
{
    return Type;
}
