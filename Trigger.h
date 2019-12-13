#ifndef TRIGGER_H
#define TRIGGER_H

#include "Block.h"
#include "Character.h"

class Trigger : public Block{
    Q_OBJECT
public:
    enum type{Type = UserType + 6};
    struct characterData{
        int x;
        int y;
        QString type;
        direction dir = RIGHT;
    };

    Trigger(int size, int x, int y);
    ~Trigger() override;
    void setDataAt(int index, characterData data);
        int type() const override;
public slots:
    void triggered();
private:
    int dataSize;
    struct characterData* data;
    QRectF boundingRect() const override;
};

#endif // TRIGGER_H
