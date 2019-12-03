//Test
#include "Node.h"
#include "Queue.h"
#include "Block.h"
//Test
#include "menu.h"
#include "Game.h"
#include "Queue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon(QIcon("./images/res/icon.png"));
    Menu* menu = new Menu();
    menu->show();

    /* Test
    Block* b1 = new Block(QPixmap(":images/res/icon.png"), 100, 100);
    Block* b2 = new Block(QPixmap(":images/res/icon.png"), 100, 100);
    Block* b3 = new Block(QPixmap(":images/res/icon.png"), 100, 100);
    //Node<Block>* n1 = new Node<Block>();
    Queue<Block>* q = new Queue<Block>(b1);
    q->enqueue(b2);
    q->enqueue(b3);
    q->print();
    delete q;

    //q->dequeue();
    //q->print();
    //q->dequeue();
    //q->print();
    //q->dequeue();
    //q->print();
    */

    return a.exec();
}
