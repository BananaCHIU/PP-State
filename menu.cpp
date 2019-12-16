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
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Menu::~Menu()
{
    music->stop();
    delete music;
    delete btn_quit;
    delete btn_play;
    delete btn_ins;
    if(movie != nullptr) {delete movie;}
    if(processLabel != nullptr) {delete processLabel;}
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
    music->setVolume(40);
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
    btn_play->setDefault(false); btn_play->setAutoDefault(false);
    // Connect button signal to appropriate slot
    connect(btn_play, SIGNAL (clicked()), this, SLOT (handlePlayButton()));
    btn_play->setFocusPolicy(Qt::ClickFocus);
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
    btn_ins->setDefault(false); btn_ins->setAutoDefault(false);
    // Connect button signal to appropriate slot
    connect(btn_ins, SIGNAL (clicked()), this, SLOT (handleInsButton()));
    btn_ins->setFocusPolicy(Qt::ClickFocus);
    // Create the quit button, make "this" the parent
    btn_quit = new QPushButton(this);
    //Set image
    QPixmap img_quit(":images/res/btn_quit.png");
    img_quit = img_quit.scaled(200, 60, Qt::KeepAspectRatio, Qt::FastTransformation);
    QIcon QuitIcon(img_quit);
    btn_quit->setIcon(QuitIcon);
    btn_quit->setIconSize(img_quit.rect().size());
    // set size and location of the button
    btn_quit->setDefault(false); btn_quit->setAutoDefault(false);
    btn_quit->setGeometry(this->size().width()/2 - img_quit.rect().size().width()/2, this->size().height() - 200, img_quit.rect().size().width(), img_quit.rect().size().height());
    // Connect button signal to appropriate slot
    connect(btn_quit, SIGNAL (clicked()), this, SLOT (handleQuitButton()));
    btn_quit->setFocusPolicy(Qt::ClickFocus);
}

void Menu::handlePlayButton()
{
    music->stop();
    //QSplashScreen *splash = new QSplashScreen;
    //splash->setPixmap(QPixmap(":/images/res/bg_load.png")); // splash picture

    Game* game = new Game();

    //QTimer::singleShot(3000, game, SLOT(show()));

    //close();
    //game->show();
    movie = new QMovie(":/images/res/load.gif");
    processLabel = new QLabel(nullptr);

    processLabel->resize(1400,800);
    processLabel->setMovie(movie);
    processLabel->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    processLabel->setStyleSheet("background-color: rgba(255,255,255,255);");

    processLabel->setAlignment(Qt::AlignCenter);
    processLabel->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,processLabel->size(),qApp->desktop()->availableGeometry())         );


    //testing:
    game->show();
    //splash->show();
    movie->start();
    processLabel->show();

    QTimer::singleShot(1950,processLabel,SLOT(close()));
    QTimer::singleShot(2000,game,SLOT(startTimer()));
    //QTimer::singleShot(1300, splash, SLOT(close())); // Timer

    QTimer::singleShot(1950, this, SLOT(close()));
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
