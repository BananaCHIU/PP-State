#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <QGraphicsPixmapItem>

class Player : public Character{
    Q_OBJECT
public:
    enum type{Type = UserType + 2 };
    Player();
    void move(enum direction dir) override;
    void jump();
    void advance(int step) override;
    QMap <int, bool> getKeyMap();
    void setKeyValue(int key, bool value);
    QPainterPath shape() const override;
private:

    int width;
    int height;
    direction direction;
    const double VERTICALACCELERATION = 6/120.0;
    double verticalVelocity = 0;
    const double SPEED = 2.5;

    QPixmap sprites[4];
    const double jumpVelocity{-550.0/120};
    const int ANIM_RATIO = 2;
    int anim_count = 0;
    QMap <int, bool> keys;

signals:
    void playerIsDead();
};

#endif // PLAYER_H
