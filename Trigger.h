#ifndef TRIGGER_H
#define TRIGGER_H

#include "Block.h"
#include "Character.h"

class Trigger : public Block{
    Q_OBJECT
public:
    enum type{Type = UserType + 5};
    Trigger(int size);
    ~Trigger();
public slots:
    void triggered();
private:
    int dataSize;
    struct spawnee{
        int x;
        int y;
        int typeIndex;
        direction dir = RIGHT;
    };
    struct spawnee* data;
};

#endif // TRIGGER_H
