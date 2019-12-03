#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"


class Raptor: public Character{
public:
    Raptor(QPixmap image, int width, int height);

    enum direction getMovingDirection();
    void flipMovingDirection();
    void move(enum direction dir) override;
    void advance(int step) override;
private:
    enum direction movingDirection{RIGHT};
};

#endif // RAPTOR_H
