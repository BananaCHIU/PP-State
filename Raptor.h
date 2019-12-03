#ifndef RAPTOR_H
#define RAPTOR_H

#include "Character.h"


class Raptor: public Character{
public:
    Raptor(QPixmap image, int width, int height);

    void move(enum direction dir) override;
    void advance(int step) override;
private:
};

#endif // RAPTOR_H
