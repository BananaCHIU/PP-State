#ifndef BULLET_H
#define BULLET_H
#include "Character.h"

#include <QObject>

/*
 * A Bullet is a non-player-control character.
 * It moves constantly towards one direction.
 * It kills player when they collides.
 * It will be destroyed when it collides a block.
 * It can be spawned by PoCar(another character).
 */

class Bullet : public Character{
    Q_OBJECT
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 5};
    // constructor
    Bullet(direction movingDirection);
    // accessor
    enum direction getMovingDirection();
    int type() const override;
    // other methods
    void move(enum direction dir) override; // update bullet position
    virtual void advance(int step) override; // called by Game, updates the bullet

private:
    enum direction movingDirection{RIGHT};

signals:
    void hitBlock(); // emits signal asking for deleteion
};
#endif // BULLET_H
