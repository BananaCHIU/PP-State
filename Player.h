#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <QGraphicsPixmapItem>

class Player : public Character{
public:
    Player(QPixmap image,int width,int height);
    void move(enum direction dir);
    void jump();
    void advance(int step) override;
private:
    const double jumpVelocity{-550.0/120};
};

#endif // PLAYER_H
