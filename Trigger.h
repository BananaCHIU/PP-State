#ifndef TRIGGER_H
#define TRIGGER_H

#include "Block.h"
#include "Character.h"

/*
 * A Trigger is a special kind of block.
 * It will not move.
 * It is transparent.
 * It spawns characters(enemies) when player collides with it.
 * It self destructs after spawning characters.
 * It will not block characters' movement.
 */

class Trigger : public Block{
    Q_OBJECT
public:
    // userType for distinguishing custom pixmap items
    enum type{Type = UserType + 6};

    // holds everything needed to spawn a character
    struct characterData{
        int x;  // x-coor
        int y;  // y-coord
        QString type;   // character type
        direction dir = RIGHT;  // character moving direction
    };
    // constructor
    Trigger(int size, int x, int y);
    // destructor
    ~Trigger() override;
    // accessor
    int type() const override;
    // other methods
    void setDataAt(int index, characterData data);

public slots:
    void triggered(); // spawn enemy when the connected signal is emitted

private:
    int dataSize;
    struct characterData* data;
};

#endif // TRIGGER_H
