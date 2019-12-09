#ifndef BLOCK_H
#define BLOCK_H
#include <Game.h>
#include <QGraphicsPixmapItem>
#include <QObject>

class Block : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
<<<<<<< HEAD
    Block(QPixmap, double, int, int);
=======
    enum type{Type = UserType + 1 };
    Block(QPixmap image, int width, int height);
>>>>>>> monster
    int getWidth();
    int getHeight();
    int type() const;
private:
    const int WIDTH = 64;
    const int HEIGHT = 64;
    int coor_x = -1, coor_y = -1;
};

#endif // BLOCK_H
