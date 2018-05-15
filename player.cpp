#include "player.h"
#include "mainwindow.h"

extern Game *game;

Player::Player(QGraphicsItem  *parent) : QGraphicsPixmapItem(parent),
    openMouthImg(QPixmap(":/images/assets/player_open.png")),
    closeMouthImg(QPixmap(":/images/assets/player_close.png"))
{
    setPixmap(closeMouthImg.scaled(PLAYER_SIZE, PLAYER_SIZE));
    isMouthOpen = false;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    eatTimer = new QTimer();
    connect(eatTimer, SIGNAL(timeout()), this, SLOT(endEatTime()));

    repeatKeyPressTimer = new QTimer();
    connect(repeatKeyPressTimer, SIGNAL(timeout()), this, SLOT(lastKeyPressEvent()));
    repeatKeyPressTimer->start(50);

    xVelocity = 0;
    yVelocity = 0;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        setVelocityIfPossible(-PLAYER_SPEED, 0, &Player::uploadLeftImg);
        lastKeyPress = 0;
    }
    else if (event->key() == Qt::Key_Right)
    {
        setVelocityIfPossible(PLAYER_SPEED, 0, &Player::uploadRightImg);
        lastKeyPress = 1;
    }
    else if (event->key() == Qt::Key_Up)
    {
        setVelocityIfPossible(0, -PLAYER_SPEED, &Player::uploadUpImg);
        lastKeyPress = 2;
    }
    else if (event->key() == Qt::Key_Down)
    {
        setVelocityIfPossible(0, PLAYER_SPEED, &Player::uploadDownImg);
        lastKeyPress = 3;
    }
}

void Player::lastKeyPressEvent()
{
    if (lastKeyPress == 0)
    {
        setVelocityIfPossible(-PLAYER_SPEED, 0, &Player::uploadLeftImg);
    }
    else if (lastKeyPress == 1)
    {
        setVelocityIfPossible(PLAYER_SPEED, 0, &Player::uploadRightImg);
    }
    else if (lastKeyPress == 2)
    {
        setVelocityIfPossible(0, -PLAYER_SPEED, &Player::uploadUpImg);
    }
    else if (lastKeyPress == 3)
    {
        setVelocityIfPossible(0, PLAYER_SPEED, &Player::uploadDownImg);
    }
    else
    {
        return;
    }
}

void Player::move()
{
    setPos(x() + xVelocity, y() + yVelocity);

    if (isMouthOpen)
    {
        setPixmap(closeMouthImg.scaled(PLAYER_SIZE, PLAYER_SIZE));
        isMouthOpen = false;
    }
    else
    {
        setPixmap(openMouthImg.scaled(PLAYER_SIZE, PLAYER_SIZE));
        isMouthOpen = true;
    }

    if (x() < -PLAYER_SIZE + 12)
    {
        setPos(WIDTH - 12, y());
    }
    else if (x() > WIDTH - 12)
    {
        setPos(-PLAYER_SIZE + 12, y());
    }
    if (y() < -PLAYER_SIZE + 12)
    {
        setPos(x(), HEIGHT - 12);
    }
    else if (y() > HEIGHT-BLOCK_SIZE / 3)
    {
        setPos(x(), -PLAYER_SIZE + 12);
    }
    if (!PlayerStats::Instance()->getPowerUpMode())
    {
         eatTimer->start(EAT_TIME);
    }
    checkCollisons();
}

void Player::endEatTime()
{
    PlayerStats::Instance()->setPowerUpMode(false);
    eatTimer->stop();
}

void Player::uploadUpImg()
{
    closeMouthImg.load(":/images/assets/player_close.png");
    openMouthImg.load(":/images/assets/player_open.png");
    QMatrix rm;
    rm.rotate(-90);
    closeMouthImg = closeMouthImg.transformed(rm);
    openMouthImg = openMouthImg.transformed(rm);
}

void Player::uploadDownImg()
{
    closeMouthImg.load(":/images/assets/player_close.png");
    openMouthImg.load(":/images/assets/player_open.png");
    QMatrix rm;
    rm.rotate(90);
    closeMouthImg = closeMouthImg.transformed(rm);
    openMouthImg = openMouthImg.transformed(rm);
}

void Player::uploadRightImg()
{
    closeMouthImg.load(":/images/assets/player_close.png");
    openMouthImg.load(":/images/assets/player_open.png");
}

void Player::uploadLeftImg()
{
    QImage tempImg1;
    tempImg1.load(":/images/assets/player_close.png");
    QImage tempImg2;
    tempImg2.load(":/images/assets/player_open.png");
    tempImg1 = tempImg1.mirrored(true, false);
    tempImg2 = tempImg2.mirrored(true, false);
    closeMouthImg = QPixmap::fromImage(tempImg1);
    openMouthImg = QPixmap::fromImage(tempImg2);
}

void Player::checkCollisons()
{
    if (collidesWithItem(game->background, Qt::IntersectsItemBoundingRect))
    {
        setPos(x() - xVelocity, y() - yVelocity);
        lastKeyPressEvent();
    }

    QList<QGraphicsItem *> collItems = collidingItems(Qt::IntersectsItemBoundingRect);
    for (int i = 0, n = collItems.size(); i < n; i++)
    {
        if (typeid(*collItems[i]) == typeid(CollectibleItem))
        {
            scene()->removeItem(collItems[i]);
            delete collItems[i];
        }
    }
}

void Player::setVelocityIfPossible(int xVel, int yVel, void (Player::*imgDir)())
{
    setPos(x() + xVel, y() + yVel);
    if (!collidesWithItem(game->background, Qt::IntersectsItemBoundingRect))
    {
        xVelocity = xVel;
        yVelocity = yVel;
        (this->*imgDir)();
        setPos(x() - xVel, y() - yVel);
        return;
    }
    setPos(x() - xVel, y() - yVel);

}
