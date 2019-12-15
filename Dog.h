#ifndef DOG_H
#define DOG_H

#include "Character.h"

/*
 * A Dog is a non-player-control character.
 * It moves towards left or right.
 * It changes direction when it collides with blocks.
 * It kills player when they collide.
 */
class Dog : public Character{
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 3};
    // constructor
    Dog();
    Dog(direction movingDirection);
    // accessors
    enum direction getMovingDirection();
    int type() const override;
    // mutators
    void flipMovingDirection();
    // other methods
    virtual void advance(int step) override;// implement advance to handle animation and movement
    void move(enum direction dir) override; // handles character movement
private:
    QPixmap sprites[4];     // sprites for animation
    enum direction movingDirection{RIGHT};
    const int ANIM_RATIO = 2;   // for animation
    int anim_count = 0;         // for animation
};

#endif // DOG_H
