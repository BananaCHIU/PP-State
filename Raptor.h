#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"
/*
 * A Raptor is a character will slow initial horizontal speed.
 * It accelerates until it jumps or reaches its max speed.
 * When there is a block in front of it, it will try to jump on it.
 * Its not strong enough to jump on blocks, so it changes its direction afterwards.
 * It slows down after jumping.
 * It kills player when they collide.
 */

class Raptor: public Character{
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 4};
    // constructors
    Raptor();
    Raptor(direction facing);
    // accessors
    double getHorizontalAcceleration() const;
    int type() const override;

private:
    // other methods
    void advance(int step) override;    // updates character every game tick
    void flipMovingDirection();
    void jump();
    void move(enum direction dir) override;

    QPixmap sprites[4];     // animation sprites
    const int ANIM_RATIO = 2;   // for animtaion
    int anim_count = 0;     // for animation
    const double horizontalAcceleration = 0.75/120.0;
    const double jumpVelocity{-375/120.0};
    const double MAX_SPEED{4};
};
#endif // RAPTOR_H
