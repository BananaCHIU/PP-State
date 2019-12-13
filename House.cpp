#include "House.h"

House::House():Block(QPixmap(":/images/res/house.png"), 80 ,2){

}
int House::type() const
{
    return Type;
}
