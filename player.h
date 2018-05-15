#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SIZE 26
#define PLAYER_SPEED 4
#define EAT_TIME 10000

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <typeinfo>
#include "collectibleitem.h"
#include "point.h"
#include "powerup.h"

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QGraphicsItem *parent = 0);
    void keyPressEvent(QKeyEvent * event);
    QTimer *timer;
    QTimer *repeatKeyPressTimer;
    QTimer *eatTimer;

public slots:
    void move();
    void endEatTime();
    void lastKeyPressEvent();

private:
    void uploadUpImg();
    void uploadDownImg();
    void uploadRightImg();
    void uploadLeftImg();
    void checkCollisons();
    void setVelocityIfPossible(int xVel, int yVel, void (Player::*imgDir)());

    int xVelocity;
    int yVelocity;
    int lastKeyPress = 1; // 0 = L; 1 = R; 2 = U; 3 = D
    QPixmap openMouthImg;
    QPixmap closeMouthImg;
    bool isMouthOpen;
};

#endif // PLAYER_H
