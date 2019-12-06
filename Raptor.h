#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"


class Raptor: public Character{
public:
    Raptor(QPixmap image);
    Raptor(QPixmap image, int width, int height);
    void flipMovingDirection();
    void jump();
    void move(enum direction dir) override;
    void advance(int step) override;
    enum direction getMovingDirection();
    double getHorizontalAcceleration() const;
private:
    const double horizontalAcceleration = 1/120.0;
    const double jumpVelocity{-375.0/120};
    enum direction movingDirection{RIGHT};
};
#endif // RAPTOR_H
