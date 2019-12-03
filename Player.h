#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
enum direction{LEFT, RIGHT, UPWARD, DOWNWARD};
class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QPixmap image,int width,int height);

    void focusOutEvent(QFocusEvent * event) ;

    int getWidth() const;
    int getHeight() const;
    int getDirection() const;
    bool getInAir() const;
    double getVerticalAcceleration() const;
    double getVerticalVelocity() const;
    double getSpeed() const;

    void move(direction dir);
    void jump();
    bool collide(direction dir);

    void setWidth(int width);
    void setHeight(int height);
    void setInAir(bool b);
    void setVerticalVelocity(double velocity);

    bool isOnGround();
    void flipDirection();

private:
    int width;
    int height;
    direction direction;
    const double verticalAcceleration = 6/120.0;
    double verticalVelocity = 0;
    const double speed = 2.5;
};

#endif // PLAYER_H
