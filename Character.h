#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
enum direction{LEFT, RIGHT, UPWARD, DOWNWARD};
class Character : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Character(QPixmap image,int width, int height);
    //accessor
    int getWidth() const;
    int getHeight() const;
    int getDirection() const;
    double getVerticalVelocity() const;
    double getSpeed() const;
    //mutator
    void setWidth(int width);
    void setHeight(int height);
    void setVerticalVelocity(double velocity);
    //other
    virtual void move(direction dir) =0;
    bool collide(enum direction dir);
    bool isOnGround();
    void flipDirection();

private:
    int width;
    int height;
    direction direction;
    double verticalVelocity = 0;
    double speed = 2.5;
};

#endif // CHARACTER_H
