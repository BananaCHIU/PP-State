#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"
/*
 * A Raptor is a character will slow initial horizontal speed.
 * It speeds up as it moves.
 * When there is a block in front of it, it will try to jump on it.
 * Its not strong enough to jump on blocks, so it changes its direction.
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
    enum direction getMovingDirection();
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
    const double horizontalAcceleration = 0.7/120.0;
    const double jumpVelocity{-375/120.0};
    enum direction movingDirection{RIGHT};
    const double MAX_SPEED{4.0};
};
#endif // RAPTOR_H
