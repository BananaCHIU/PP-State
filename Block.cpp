#include "Block.h"
#include "Game.h"
#include <QGraphicsScene>

#include <iostream>
using namespace std;

Block::Block(int x, int y)
{
    setPos(x * WIDTH, Game::getWinHeight() - HEIGHT * y);
}

Block::Block(QPixmap image)
{
    setPixmap(image);
}

Block::Block(QPixmap image, int x, int y)
{
    setPixmap(image);
    setPos(x * WIDTH, Game::getWinHeight() - HEIGHT * y);
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

