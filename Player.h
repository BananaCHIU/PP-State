#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

#include <QTimer>
class Player : public Character{
    Q_OBJECT
public:
    Player(QPixmap image,int width,int height);
    QTimer* getTimer(int type);

public slots:
    void movePlayer(int movement);
    void repeatMove_Left();
    void repeatMove_Right();
    void repeatMove_Jump();
    void stopMovement(int movement);
private:
    QTimer* lTimer;
    QTimer* rTimer;
    QTimer* uTimer;
};

#endif // PLAYER_H
