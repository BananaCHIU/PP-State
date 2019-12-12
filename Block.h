#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Block : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    Block(int x, int y);
    Block(QPixmap image);
    // Block(QPixmap, double, int x, int y);
    Block(QPixmap image, int x, int y);

    enum type{Type = UserType + 1 };

    int getWidth();
    int getHeight();
    virtual int type() const;
protected:
    // width and height of a block
    const int WIDTH = 64;
    const int HEIGHT = 64;
private:
    int coor_x = -1, coor_y = -1;
};

#endif // BLOCK_H
