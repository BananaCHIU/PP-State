#include "Block.h"

Block::Block(QPixmap image, double winHeight, int x, int y): coor_x(x), coor_y(y)
{
    setPixmap(image);
    setPos(coor_x * WIDTH, winHeight - HEIGHT * coor_y);
}

int Block::getWidth()
{
    return WIDTH;
}

int Block::getHeight()
{
    return HEIGHT;
}

int Block::type() const
{
    return Type;
}

