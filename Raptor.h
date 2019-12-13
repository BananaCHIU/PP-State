#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"


class Raptor: public Character{
public:
    enum type{Type = UserType + 4 };
    Raptor();
    Raptor(direction facing);
    void flipMovingDirection();
    void jump();
    void move(enum direction dir) override;
    void advance(int step) override;
    enum direction getMovingDirection();
    double getHorizontalAcceleration() const;
    //QPainterPath shape() const override;
private:
    // maybe change to static later
    QPixmap sprites[4];

    const int ANIM_RATIO = 2;
    int anim_count = 0;
    const double horizontalAcceleration = 0.7/120.0;
    const double jumpVelocity{-375/120.0};
    enum direction movingDirection{RIGHT};
    const double MAX_SPEED{4.0};
};
#endif // RAPTOR_H
