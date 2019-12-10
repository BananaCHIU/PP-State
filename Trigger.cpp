#include "Trigger.h"
#include "QGraphicsScene"

Trigger::Trigger(int size): Block(64, 64)
{
    data = new struct spawnee[size];
}

Trigger::~Trigger(){
   delete [] data;
}

void Trigger::triggered()
{
    for (int i = 0; i < dataSize; ++i){
        /* switch(dataIndex){
         * Dog::Type:
         *      pointer in data structure = new dog(data[i]->dir);
         * break;
         * Raptor::Type:
         *      pointer in data structure = new raptor(data[i]->dir);
         * break;
         * Bullet::Type:
         *      pointer in data structure = new bullet();
         * break;
        }*/
        //
        // setPos(data[i].x, data[i].y);
        // scene()->addItem(pointer in data structure);
    }
    delete this;
}
