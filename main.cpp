
#include "menu.h"
#include "Game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/res/icon.png"));
    Menu* menu = new Menu();
    menu->show();
    return a.exec();
}
