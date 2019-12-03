#include <QPushButton>
#include <QPixmap>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "menu.h"
#include "Game.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    //Background Image
    QPixmap bkgnd(":images/res/bg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //BGM
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/res/bgm_menu.mp3"));
    music->play();

    //Title
    QPixmap pm(":images/res/title.png"); // <- path to image file
    ui->label->setGeometry(450,200,500,70);
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);

    // Create the button, make "this" the parent
    m_button = new QPushButton("Play", this);
    // set size and location of the button
    m_button->setGeometry(650, 600, 100, 100);

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

}

Menu::~Menu()
{
    music->stop();
    delete ui;
}

void Menu::handleButton()
{
    close();
    music->stop();
    Game * game = new Game();
    game->show();
}
