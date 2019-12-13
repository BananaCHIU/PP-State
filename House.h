#ifndef HOUSE_H
#define HOUSE_H

#include "Block.h"
#include <QPixmap>

class House : public Block{
public:
    House();
    enum type{Type = UserType + 7 };
    int type() const override;
};
#endif // HOUSE_H
