#ifndef GHOSTRED_H
#define GHOSTRED_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "ghost.h"
#include "game.h"

class GhostRed : public Ghost
{
    using Ghost::Ghost;
public slots:
    void move();
private:
    int timeForMove = 0;
};

#endif // GHOSTRED_H
