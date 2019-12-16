#include <Game.h>
#include <QObject>
#include "Block.h"
#include "Player.h"
#include "House.h"
#include <QScrollBar>
#include <QTimer>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
using namespace std;
Player::Player() : Character(QPixmap(":/images/res/sprite_0.png"), 65, 68){
    for(int i = 0; i < 4; ++i){
        sprites[i] = QPixmap(QString::fromStdString(":/images/res/sprite_" + to_string(i)+ ".png"));
    }
    sound_jump.setMedia(QUrl("qrc:/music/res/jump.mp3"));
    sound_jump.setVolume(5);
}

// accessor
QMap<int, bool> Player::getKeyMap(){
    return keys;
}

int Player::type() const{
    return Type;
}

// mutator
void Player::setKeyValue(int key, bool value)
{
    keys[key] = value;
}

// other methods
void Player::advance(int step)
{
    if (step==0) return;
    if (y() > scene()->height()) {
        emit playerIsDead();
        return;
    }

    // player die checking && interaction with trigger
    QList<QGraphicsItem*> collidingitems = collidingItems(Qt::IntersectsItemShape);
    for (int i = 0; i < collidingitems.size(); ++i){
        if (collidingitems[i]->type() != Block::Type
            && collidingitems[i]->type() != Trigger::Type
            && collidingitems[i]->type() != House::Type){
            emit playerIsDead();
            return;
        } else if (collidingitems[i]->type() == Trigger::Type){
            static_cast<Trigger*>(collidingitems[i])->triggered();
        }else if (collidingitems[i]->type() == House::Type){
            emit backedHome();
            return;
        }
    }

    if (step == 0) return;

    // if "W" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_W)) {
        // perform jumping
        jump();
    }

    // if "A" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_A)) {
        // out of view prevention + move to leftwards
        // Cant go back if the player touches the leftmost part of the screen
        if (x() >= scene()->views().first()->horizontalScrollBar()->value()) move(LEFT);

        // animation handler
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)]);
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }

    // if "D" key was pressed/pressing
    if(getKeyMap().value(Qt::Key_D)) {
        // move to leftwards
        move(RIGHT);

        // animation handler
        if (anim_count % (ANIM_RATIO * 4) == 0) {
            setPixmap(sprites[anim_count / (ANIM_RATIO * 4)].transformed(QTransform().scale(-1,1)));
        }
        if (anim_count == (ANIM_RATIO * 4 * 4) - 1) anim_count = 0;
        else ++anim_count;
    }
}

void Player::jump()
{
    if (isOnGround()){
        if (sound_jump.state() == QMediaPlayer::PlayingState) sound_jump.setPosition(0);
        else if(sound_jump.state() == QMediaPlayer::StoppedState) sound_jump.play();
        setVerticalVelocity(jumpVelocity);
        setPos(x(), y()-1);
    }
}

void Player::move(enum direction dir)
{
    // left
    if (dir == LEFT) {
        if (collide(LEFT)) return;
        if ((x() - getSpeed()) < 0)  setPos(0, y());
        else setPos(x()- getSpeed(), y());
    }

    //right
    if (dir == RIGHT) {
        if (collide(RIGHT)) return;
        if (x() + getWidth() + getSpeed() > scene()->width())  setPos(scene()->width() - getWidth(), y());
        else setPos(x()+ getSpeed(), y());
    }

}
