#include "Block.h"
#include "Game.h"

#include <QPixmapCache>

Block::Block(int x, int y)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    QPixmapCache::setCacheLimit(102400);
    setPos(x * WIDTH, Game::getWinHeight() - HEIGHT * y);
}

Block::Block(QPixmap image)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    QPixmapCache::setCacheLimit(102400);
    setPixmap(image);
}

Block::Block(QPixmap image, int x, int y)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    QPixmapCache::setCacheLimit(102400);
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

