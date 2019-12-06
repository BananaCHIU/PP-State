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
    Menu* menu = new Menu();
    menu->show();

    return a.exec();
}
