#ifndef DOG_H
#define DOG_H

#include "Character.h"


class Dog : public Character{
public:
    enum type{Type = UserType + 3 };
    Dog();
    Dog(direction movingDirection);
    enum direction getMovingDirection();
    void flipMovingDirection();
    void move(enum direction dir) override;
    virtual void advance(int step) override;
private:
    enum direction movingDirection{RIGHT};
    const int anim_ratio = 2;
    int anim_count = 0;
};

#endif // DOG_H
