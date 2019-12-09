#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <QGraphicsPixmapItem>

class Player : public Character{
public:
    enum type{Type = UserType + 2 };
    Player(QPixmap image);
    void move(enum direction dir) override;
    void jump();
    void advance(int step) override;
    QMap <int, bool> getKeyMap();
    void setKeyValue(int key, bool value);
    QPainterPath shape() const override;
private:
    const double jumpVelocity{-550.0/120};
    const int anim_ratio = 2;
    int anim_count = 0;
    QMap <int, bool> keys;
};

#endif // PLAYER_H
