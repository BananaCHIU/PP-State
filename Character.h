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
    enum direction getFacing() const;
    double getVerticalVelocity() const;
    double getSpeed() const;
    //mutator
    void setWidth(int width);
    void setHeight(int height);
    void setSpeed(double speed);
    void setVerticalVelocity(double velocity);
    //other
    virtual void move(enum direction dir) =0;
    virtual void advance(int step) =0;
    virtual bool collide(enum direction dir);
    bool isOnGround();
    void flipFacing();
    int type() const;

private:
    int width;
    int height;
    enum direction facing{RIGHT};
    double verticalVelocity{0};
    double speed{2.5};

};

#endif // CHARACTER_H
