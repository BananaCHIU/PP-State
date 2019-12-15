#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

/*
 * A Player object is a character controlled by the player.
 * It can move horizontally and jump.
 * It can activate triggers to spawn characters.
 * It can jump.
 * It cannot kill other characters.
 * If it dies, the game loses.
 * If it collides with House object, the game wins
 */

class Player : public Character{
    Q_OBJECT
public:
    // used to distinguish custom pixmap items
    enum type{Type = UserType + 2};
    // constructor
    Player();
    // accessors
    QMap <int, bool> getKeyMap();
    int type()const override;
    // mutator
    void setKeyValue(int key, bool value);
    // other method
    void advance(int step) override; // update player every game tick
    void jump();
    void move(enum direction dir) override; // handle player movement

signals:
    void playerIsDead();    // emitted = game over
    void backedHome();      // emitted = game win

private:
    int width;
    int height;
    direction direction;
    const double SPEED{2.5};   // horitzontal speed;

    QMediaPlayer sound_jump;    // jump sound effect
    QPixmap sprites[4];         // animation sprites
    const double jumpVelocity{-700/120.0};  // setting jump force
    const int ANIM_RATIO{2};    // animation variables
    int anim_count{0};          // animation variables
    QMap <int, bool> keys;      // pressed keys have a true value
};

#endif // PLAYER_H
