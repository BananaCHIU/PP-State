#ifndef POCAR_H
#define POCAR_H

#include "Character.h"
#include "Bullet.h"
#include <QObject>

class PoCar : public Character{
    Q_OBJECT
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 8};
    // constructors
    PoCar();
    PoCar(direction movingDirection);
    // accessors
    int type() const override;
// slots
public slots:
    void deleteBullet();    // deletes the bullet it shooted

private:
    void advance(int step) override;    // updates character every game tick
    void move(enum direction dir) override; // empty function, just to get rid of abstract class
    void shoot();   // shoots a Bullet object

    QPixmap sprites[2];         // animation sprites
    const int ANIM_RATIO = 3;   // for animation
    int anim_count = 0;         // for animation
    Bullet *bullet = nullptr;   // pointer to the bullet it shoots
    enum direction facingDirection{RIGHT};
};

#endif // POCAR_H
