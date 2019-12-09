#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"


class Raptor: public Character{
public:
    enum type{Type = UserType + 4 };
    Raptor(QPixmap image);
    Raptor(QPixmap image, direction facing);
    void flipMovingDirection();
    void jump();
    void move(enum direction dir) override;
    void advance(int step) override;
    enum direction getMovingDirection();
    double getHorizontalAcceleration() const;
    QPainterPath shape() const override;
private:
    const int anim_ratio = 2;
    int anim_count = 0;
    const double horizontalAcceleration = 0.7/120.0;
    const double jumpVelocity{-375.0/120};
    enum direction movingDirection{RIGHT};
    const double MAX_SPEED{5.0};
};
#endif // RAPTOR_H
