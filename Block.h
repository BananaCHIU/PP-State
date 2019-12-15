#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>

/*
 * A Block is a static game object.
 * It will not move.
 * It acts as a platform for characters to stand and walk on.
 * It collides with characters and stop their movement.
 */

class Block :  public QGraphicsPixmapItem, public QObject{
public :
    // userType for distinguishing custom pixmap items
    enum type{Type = UserType + 1 };

    // constructors
    Block(QPixmap image, int x, int y);

    // accessors
    int getWidth();
    int getHeight();
    int type() const override;

private:
    // constant width and height of a block
    // should be static?
    const int WIDTH = 64;
    const int HEIGHT = 64;
};

#endif // BLOCK_H
