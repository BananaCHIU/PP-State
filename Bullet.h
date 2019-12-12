#ifndef BULLET_H
#define BULLET_H
#include "Character.h"


class Bullet : public Character{
public:
    enum type{Type = UserType + 4 };
    Bullet();
    void move(enum direction dir) override;
    virtual void advance(int step) override;
    int type() const;
private:
    enum direction movingDirection{RIGHT};
};
#endif // BULLET_H