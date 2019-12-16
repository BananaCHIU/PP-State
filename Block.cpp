#include "Block.h"
#include "Game.h"

#include <QPixmapCache>

Block::Block(QPixmap image, int x, int y)
{
    //setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    //QPixmapCache::setCacheLimit(102400);
    //seems we are not using cache right?
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

