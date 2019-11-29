#include <QObject>
#include <Player.h>
#include <QTimer>
enum move{LEFT, RIGHT, JUMP};
Player::Player(QPixmap image,int width,int height) : Character(image, width, height){
    setPixmap(image);
    setWidth(width);
    setHeight(height);

    rTimer = new QTimer();
    lTimer = new QTimer();
    uTimer = new QTimer();
}


QTimer* Player::getTimer(int type)
{
    if (type == LEFT) return lTimer;
    if (type == RIGHT) return rTimer;
    if (type == JUMP) return uTimer;
    return nullptr;
}

void Player::movePlayer(int movement){

    switch(movement){
        case LEFT:
            connect(lTimer, SIGNAL(timeout()), this, SLOT(Player::repeatMove_Left()));
            lTimer->start(1000/60);
            break;
            case RIGHT:
            connect(rTimer, SIGNAL(timeout()), this, SLOT(Player::repeatMove_Right()));
            rTimer->start(1000/60);
            break;
        case JUMP:
            connect(uTimer, SIGNAL(timeout()), this, SLOT(Player::repeatMove_Jump()));
            uTimer->start(1000/60);
            break;
        default:
            break;
    }
}

void Player::repeatMove_Left(){

}

void Player::repeatMove_Right(){

}

void Player::repeatMove_Jump(){

}

void Player::stopMovement(int movement){

}
