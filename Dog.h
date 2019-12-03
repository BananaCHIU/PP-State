#ifndef DOG_H
#define DOG_H

#include "Character.h"


class Dog : public Character{
public:
    Dog(QPixmap image, int w, int h);

    enum direction getMovingDirection();
    void flipMovingDirection();
    void move(enum direction dir) override;
    bool collide(enum direction dir);
    virtual void advance(int step) override;
private:
    enum direction movingDirection{RIGHT};
};

#endif // DOG_H
