#ifndef TRIGGER_H
#define TRIGGER_H

#include "Block.h"
#include "Character.h"

class Trigger : public Block{
    Q_OBJECT
public:
    struct spawnee{
        int x;
        int y;
        int typeIndex;
        direction dir = RIGHT;
    };
    enum type{Type = UserType + 5};
    Trigger(int size, int x, int y);
    ~Trigger() override;
    void setDataAt(int index, spawnee data);
    QRectF boundingRect() const override;
public slots:
    void triggered();
private:
    int dataSize;
    struct spawnee* data;
};

#endif // TRIGGER_H
