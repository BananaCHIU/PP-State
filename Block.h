#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Block : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    Block(QPixmap image, int width, int height);
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
};

#endif // BLOCK_H
