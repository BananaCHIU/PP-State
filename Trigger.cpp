#include "Trigger.h"
#include "QGraphicsScene"
#include "Dog.h"
#include "Raptor.h"
#include "Bullet.h"
#include <iostream>
using namespace std;

Trigger::Trigger(int size, int x, int y): Block(QPixmap(":/images/res/trigger.png"),x, y)
{
    // comment the setOpacity(0.0) line or change to
    // setOpacity(1.0) to view trigger image
    // for debug purpose :P
    setOpacity(0.0);
    data = new struct spawnee[size];
    dataSize = size;
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
    cout << "triggered!!!" << endl;
    cout << dataSize << endl;
    for (int i = 0; i < dataSize; ++i){
        // debug
        cout << data[i].x << endl;
        cout << data[i].y << endl;
        cout << data[i].type.toStdString() << endl;
        cout << !data[i].type.compare("DOG") << endl;
        //

        if (!data[i].type.compare("DOG")){
            Dog *dog = new Dog(data[i].dir);
            // change the hard coded 64 to block width & height
            // change the hard coded 800 to win height
            dog->setPos(data[i].x * 64, 800 - data[i].y * 64);
            scene()->addItem(dog);
        } else if (!data[i].type.compare("RAPTOR")){
            Raptor *raptor = new Raptor(data[i].dir);
            raptor->setPos(data[i].x * 64, 800 - data[i].y * 64);
            scene()->addItem(raptor);
        } else if (!data[i].type.compare("BULLET")){
            Bullet *bullet = new Bullet();
            bullet->setPos(data[i].x * 64, 800 - data[i].y * 64);
            scene()->addItem(bullet);
        }
    }
    delete this;
}

QRectF Trigger::boundingRect() const{
    QRectF rect = QRect(0, 0, 64, 64);
    return rect;
}

int Trigger::type() const
{
    return Type;
}
