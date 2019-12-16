#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
#include <QPixmap>

/*
 * A House is a special block representing the goal in the game.
 * Player wins when he/she collides with the house.
 * It does not move.
 */
class House : public Block{
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 7};
    // constructor
    House(int, int);
    // other method
    int type() const override;
};
#endif // HOUSE_H
