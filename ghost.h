#ifndef GHOST_H
#define GHOST_H

#define GHOST_SPEED 4
#define GHOST_SIZE 26

#define GHOST_POSITION_OFFSET 4
#define PLAYER_X_OFFSET 16
#define PLAYER_Y_OFFSET 4
#define KILL_SCORE 200

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <time.h>

class Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Ghost(QPixmap image);
    QTimer * timer;
public slots:
    virtual void move() = 0;
protected:
    bool setVelocityIfPossible(int xVel, int yVel);
    void moveIfPossible();
    void checkCollisonsWithPlayer();
    void warp();
    int xVelocity = 0;
    int yVelocity = -4;
    unsigned timeAfterLastTurn;
    void drawIfEadible();
    QPixmap ghostImage;
    void idleWalk();
};

#endif // GHOST_H
