#ifndef TRIGGER_H
#define TRIGGER_H

#include "Block.h"
#include "Character.h"
#include "Queue.h"

class Trigger : public Block{
    Q_OBJECT
public:
    Trigger(int size, int x, int y);
    ~Trigger() override;

    enum type{Type = UserType + 5};
    struct characterData{
        int x;
        int y;
        QString type;
        direction dir = RIGHT;
    };

    void setDataAt(int index, characterData data);

public slots:
    void triggered();
private:
    int dataSize;
    struct characterData* data;

    QRectF boundingRect() const override;
    int type() const override;

};

#endif // TRIGGER_H
