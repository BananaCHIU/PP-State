#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>

class Player : public Character{
    Q_OBJECT
public:
    enum type{Type = UserType + 2};
    Player();
    void move(enum direction dir) override;
    void jump();
    void advance(int step) override;
    QMap <int, bool> getKeyMap();
    void setKeyValue(int key, bool value);
    //QPainterPath shape() const override;
private:

    int width;
    int height;
    direction direction;
    double verticalVelocity = 0;
    const double SPEED = 2.5;

    QMediaPlayer sound_jump;
    QPixmap sprites[4];
    const double jumpVelocity{-700/120.0};
    const int ANIM_RATIO = 2;
    int anim_count = 0;
    QMap <int, bool> keys;
    int type()const override;
signals:
    void playerIsDead();
    void backedHome();
};

#endif // PLAYER_H
