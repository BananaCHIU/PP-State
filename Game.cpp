#include "Game.h"
#include "Player.h"

#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

enum move{LEFT, RIGHT, JUMP};

Game::Game(QWidget *parent) : QGraphicsView(){
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WIN_WIDTH ,WIN_HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);

    player = new Player(QPixmap(":/images/player.png"), 64, 64);
    player->setPos(scene->width()/2, scene->height()/2);
    scene->addItem(player);

    QObject::connect(this, &Game::keyInputReceived, player, &Player::movePlayer);
}

void Game::keyPressEvent(QKeyEvent * event){
    switch (event->key()){
    case Qt::Key_A:{
        player->movePlayer(LEFT);
        qDebug() << "LEFT";
        break;
    }
    case Qt::Key_D:{
        qDebug() << "RIGHT";
        break;
    }
    case Qt::Key_W:{
        qDebug() << "JUMP";
        break;
    }
    default:
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_A:{
            qDebug() << "LEFT released";
            break;
        }
        case Qt::Key_D:{
            qDebug() << "RIGHT released";
            break;
        }
        case Qt::Key_W:{
            qDebug() << "JUMP released";
            break;
        }
        default:
            break;
    }
}

