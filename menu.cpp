#include <QPushButton>
#include <QPixmap>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "menu.h"
#include "Game.h"
#include "instruction.h"
#include "ui_menu.h"

Menu::Menu(bool state, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    //Title
    ui->setupUi(this);
    if (state){
        this->setWindowTitle("PP State");
        QPixmap pm(":images/res/title_pp.png"); // <- path to image file
        ui->label->setGeometry(this->size().width() / 2 - pm.width() / 2, 100,pm.width(), pm.height());
        ui->label->setPixmap(pm);
        ui->label->setScaledContents(true);
    }else {
        this->setWindowTitle("HK");
        QPixmap pm(":images/res/title_hk.png"); // <- path to image file
        ui->label->setGeometry(this->size().width() / 2 - pm.width() / 2, 100,pm.width(), pm.height());
        ui->label->setPixmap(pm);
        ui->label->setScaledContents(true);
    }
    createMenu();
}

Menu::~Menu()
{
    music->stop();
    delete music;
    delete btn_quit;
    delete btn_play;
    delete btn_ins;
    delete ui;
}

void Menu::createMenu()
{
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

    // Create the playbutton, make "this" the parent
    btn_play = new QPushButton(this);
    //Set image
    QPixmap img_play(":images/res/btn_play.png");
    img_play = img_play.scaled(200, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QIcon PlayIcon(img_play);
    btn_play->setIcon(PlayIcon);
    btn_play->setIconSize(img_play.rect().size());
    // set size and location of the button
    btn_play->setGeometry(this->size().width()/2 - img_play.rect().size().width()/2, this->size().height() - 400, img_play.rect().size().width(), img_play.rect().size().height());
    // Connect button signal to appropriate slot
    connect(btn_play, SIGNAL (released()), this, SLOT (handlePlayButton()));

    // Create the instruction button, make "this" the parent
    btn_ins = new QPushButton(this);
    //Set image
    QPixmap img_ins(":images/res/btn_ins.png");
    img_ins = img_ins.scaled(200, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QIcon InsIcon(img_ins);
    btn_ins->setIcon(InsIcon);
    btn_ins->setIconSize(img_ins.rect().size());
    // set size and location of the button
    btn_ins->setGeometry(this->size().width()/2 - img_ins.rect().size().width()/2, this->size().height() - 300, img_ins.rect().size().width(), img_ins.rect().size().height());
    // Connect button signal to appropriate slot
    connect(btn_ins, SIGNAL (released()), this, SLOT (handleInsButton()));

    // Create the quit button, make "this" the parent
    btn_quit = new QPushButton(this);
    //Set image
    QPixmap img_quit(":images/res/btn_quit.png");
    img_quit = img_quit.scaled(200, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QIcon QuitIcon(img_quit);
    btn_quit->setIcon(QuitIcon);
    btn_quit->setIconSize(img_quit.rect().size());
    // set size and location of the button
    btn_quit->setGeometry(this->size().width()/2 - img_quit.rect().size().width()/2, this->size().height() - 200, img_quit.rect().size().width(), img_quit.rect().size().height());
    // Connect button signal to appropriate slot
    connect(btn_quit, SIGNAL (released()), this, SLOT (handleQuitButton()));
}

void Menu::handlePlayButton()
{
    close();
    music->stop();
    Game * game = new Game();
    game->show();
}

void Menu::handleInsButton()
{
    Instruction * ins = new Instruction();
    ins->show();
}

void Menu::handleQuitButton()
{
    music->stop();
    close();
    exit(0);
}
