#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>

/*
 * Character class is an abstract class.
 * All characters in the game inherits this class.
 * This class provides methods that:
 * - check character-block collision
 * - check whether character is standing on a block
 * - basic accessors and mutators
 *
 * The class has two abstract methods:
 * - advance() called by Game in every game tick
 * - move() handles character movement/behaviour
 *
 * Implemented inherited classes are:
 * Player, Dog, Raptor, Bullet, PoCar
 */

enum direction{LEFT, RIGHT, UPWARD, DOWNWARD};

class Character : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // constructor
    Character(QPixmap image,int width, int height);
    // accessors
    enum direction getFacing() const;
    int getHeight() const;
    double getSpeed() const;
    double getVerticalVelocity() const;
    int getWidth() const;
    int type() const override;
    // mutators
    void setHeight(int height);
    void setSpeed(double speed);
    void setVerticalVelocity(double velocity);
    void setWidth(int width);
    //other methods
    virtual void advance(int step) override =0; // virtual method called by game to update character
    bool collide(enum direction dir); // return whether the character collides with blocks
    void flipFacing(); // flip character facing(variable and image)
    bool isOnGround(); // return whether the character is on ground(not floating/falling)
    virtual void move(enum direction dir) =0; // virtual method to handle character movement

private:
    int width;
    int height;
    enum direction facing{RIGHT};
    double verticalVelocity{0}; // vertical velocity for falling/jumping
    double speed{3};    // default horizontal speed
};

#endif // CHARACTER_H
