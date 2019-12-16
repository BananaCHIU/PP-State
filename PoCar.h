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
    // destructor
    ~PoCar() override;
    // accessors
    int type() const override;
public slots:
    void shoot();   // shoots a Bullet object
private:
    void advance(int step) override;    // updates character every game tick
    void move(enum direction dir) override; // empty function, just to get rid of abstract class
    // data members
    QPixmap sprites[2];         // animation sprites
    const int ANIM_RATIO = 3;   // for animation
    int anim_count = 0;         // for animation
    enum direction facingDirection{RIGHT};
    QTimer * shootTimer;
};

#endif // POCAR_H
