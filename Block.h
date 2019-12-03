#ifndef BLOCK_H
#define BLOCK_H
#include <Game.h>
#include <QGraphicsPixmapItem>
#include <QObject>

class Block : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    enum type{Type = UserType + 1 };
    Block(QPixmap image, int width, int height);
    int getWidth();
    int getHeight();
    int type() const;
private:
    int width;
    int height;
};

#endif // BLOCK_H
