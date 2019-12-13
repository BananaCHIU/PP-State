#include "House.h"

House::House():Block(QPixmap(":/images/res/house.png"), 80 ,2){
    setPos(x(), y()-(363-64));
}
int House::type() const
{
    return Type;
}
