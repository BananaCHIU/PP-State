#ifndef BULLET_H
#define BULLET_H
#include "Character.h"
#include <QObject>

class Bullet : public Character{
    Q_OBJECT
public:
    enum type{Type = UserType + 5};
    Bullet();
    void move(enum direction dir) override;
    virtual void advance(int step) override;
    int type() const override;
private:
    enum direction movingDirection{RIGHT};

signals:
    void hitBlock();
};
#endif // BULLET_H
