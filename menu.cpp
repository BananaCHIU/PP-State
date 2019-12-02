#include <QPushButton>
#include <QPixmap>
#include "menu.h"
#include "Game.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QPixmap pm(":images/res/title.png"); // <- path to image file
    ui->label->setGeometry(450,200,500,70);
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);
    // Create the button, make "this" the parent
    QPushButton* m_button = new QPushButton("Play", this);
    // set size and location of the button
    m_button->setGeometry(650, 600, 100, 100);

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

}

Menu::~Menu()
{
    delete ui;
}

void Menu::handleButton()
{
    close();
    Game * game = new Game();
    game->show();
}
