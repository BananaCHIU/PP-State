#ifndef POCAR_H
#define POCAR_H

#include "Character.h"
#include "Bullet.h"
#include <QObject>

class PoCar : public Character{
    Q_OBJECT
public:
    enum type{Type = UserType + 8};
    PoCar();
    PoCar(direction facingDirection);

    enum direction getFacingDirection();
    int type() const override;

public slots:
    void deleteBullet();
private:
    QPixmap sprites[2];
    const int ANIM_RATIO = 3;
    int anim_count = 0;
    Bullet *bullet = nullptr;
    enum direction facingDirection{RIGHT};

    void shoot();
    void advance(int step) override;
    void move(enum direction dir) override;
};

#endif // POCAR_H
