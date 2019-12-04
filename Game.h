#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QTimer>
#include <QGraphicsView>

class Game: public QGraphicsView{
    Q_OBJECT

    void gravity();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    QMap <int, bool> getKeyMap();
    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 800;
    int anim_count = 0;
    const int anim_ratio = 2;
    QGraphicsScene *scene;
    Player *player;
    QTimer * timer;
    QMap <int, bool> keys;

    QPixmap img_brick{":/background/res/brick_1.png"};
    QVector<QPixmap> player_array;
public:
    Game(QWidget *parent = nullptr);
    ~Game();
    double getWinHeight();
    double getWinWidth();
public slots:
    void update();
};

#endif // GAME_H
