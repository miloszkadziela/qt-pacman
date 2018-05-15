#ifndef GHOSTCYAN_H
#define GHOSTCYAN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "ghost.h"
#include "game.h"

class GhostCyan : public Ghost
{
    using Ghost::Ghost;
public slots:
    void move();
};

#endif // GHOSTCYAN_H
