#include "Block.h"

Block::Block(QPixmap image, int width, int height)
{
    setPixmap(image);
    this->width = width;
    this->height = height;
}

int Block::getWidth()
{
    return width;
}

int Block::getHeight()
{
    return height;
}
