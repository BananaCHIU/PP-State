#include "Bullet.h"
#include "Dog.h"
#include "Game.h"
#include "PoCar.h"
#include "Queue.h"
#include "Raptor.h"
#include "Trigger.h"

#include "QGraphicsScene"
#include <iostream>
using namespace std;

Trigger::Trigger(int size, int x, int y): Block(QPixmap(":/images/res/trigger.png"),x, y)
{
    // comment the setOpacity(0.0) line or change to setOpacity(1.0)
    // to view trigger image for debug purpose :P
    setOpacity(0.0);
    data = new struct characterData[size];
    dataSize = size;
}

Trigger::~Trigger(){
    delete [] data;
}

void Trigger::setDataAt(int index, characterData data)
{
    // shallow copying, since there isn't any pointer
    // in the struct characterData,
    this->data[index] = data;
}

void Trigger::triggered()
{
    int winHeight = static_cast<Game*>(scene()->views().first())->getWinHeight();
    Queue<Character>* temp = static_cast<Game*>(scene()->views().first())->getCharQueue();
    // add character to the scene according
    for (int i = 0; i < dataSize; ++i){
        // confirm character type
        Character *character = nullptr;
        if (!data[i].type.compare("DOG")){
            character = new Dog(data[i].dir);
            // change the hard coded 64 to block width & height
            // change the hard coded 800 to win height
            character->setPos(data[i].x * WIDTH, winHeight - data[i].y * HEIGHT);
        } else if (!data[i].type.compare("RAPTOR")){
            character = new Raptor(data[i].dir);
            character->setPos(data[i].x * WIDTH, winHeight - data[i].y * HEIGHT);
        } else if (!data[i].type.compare("BULLET")){
            character = new Bullet();
            character->setPos(data[i].x * WIDTH, winHeight - data[i].y * HEIGHT);
        } else if (!data[i].type.compare("POCAR")){
            character = new PoCar();
            character->setPos(data[i].x * WIDTH, winHeight - data[i].y * HEIGHT - character->getHeight()/2);
        }

        if (character != nullptr){
            temp->enqueue(character);
            scene()->addItem(character);
        }
    }
    scene()->removeItem(this);
}

int Trigger::type() const
{
    return Type;
}
