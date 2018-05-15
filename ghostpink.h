#ifndef GHOSTPINK_H
#define GHOSTPINK_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "ghost.h"
#include "game.h"

class GhostPink : public Ghost
{
    using Ghost::Ghost;
public slots:
    void move();
private:
    int dir = 0;
};

#endif // GHOSTPINK_H
