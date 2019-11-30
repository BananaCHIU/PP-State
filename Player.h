#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
class Player : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QPixmap image,int width,int height);

    void gravity();
    void focusOutEvent(QFocusEvent * event) ;

    int getWidth();
    int getHeight();
    int getDirection();
    bool getInAir();
    double getVerticalAceleration();
    double getVerticalVelocity();
    double getVerticalSpeed();

    void setWidth(int width);
    void setHeight(int height);
    void setInAir();
    void setNotInAir();
    void setVerticalVelocity(double velocity);
    void setVerticalSpeed(double speed);

    bool isOnGround();
    void flipDirection();

public slots:
private:
    enum direction{LEFT = -1, RIGHT = 1};
    int width;
    int height;
    direction direction;
    const double verticalAcceleration = 0.4/120.0;
    double verticalVelocity = 0;
    double verticalSpeed = 0;

    bool inAir = true;

};

#endif // PLAYER_H
