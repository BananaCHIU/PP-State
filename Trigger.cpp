#include "Trigger.h"
#include "QGraphicsScene"

Trigger::Trigger(int size, int x, int y): Block(x, y)
{
    data = new struct spawnee[size];
}

Trigger::~Trigger(){
    delete [] data;
}

void Trigger::setDataAt(int index, spawnee data)
{
    // shallow copying, since there isn't any pointer
    // in the struct spawnee,
    this->data[index] = data;
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

QRectF Trigger::boundingRect() const{
    QRectF rect = QRect(0, 0, 64, 64);
    return rect;
}
