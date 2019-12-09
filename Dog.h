#ifndef DOG_H
#define DOG_H

#include "Character.h"


class Dog : public Character{
public:
    enum type{Type = UserType + 3 };
    Dog(QPixmap image);
    Dog(QPixmap image, direction movingDirection);
    enum direction getMovingDirection();
    void flipMovingDirection();
    void move(enum direction dir) override;
    virtual void advance(int step) override;
private:
    enum direction movingDirection{RIGHT};
};

#endif // DOG_H
