//Test
#include "Node.h"
#include "Queue.h"
#include "Block.h"
//Test
#include "menu.h"
#include "Game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon(QIcon("./images/res/icon.png"));
    Menu* menu = new Menu();
    menu->show();
    //Test
    Block* b1 = new Block(QPixmap(":images/res/icon.png"), 100, 100);
    //Node<Block>* n1 = new Node<Block>(*b1);
    Queue<Block>* q = new Queue<Block>(b1);
    q->print();
    //Test
    return a.exec();
}
