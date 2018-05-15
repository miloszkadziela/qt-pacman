#ifndef GHOSTORANGE_H
#define GHOSTORANGE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "ghost.h"
#include "game.h"

class GhostOrange : public Ghost
{
    using Ghost::Ghost;
public slots:
    void move();
private:
    bool followPlayer();
};

#endif // GHOSTORANGE_H
