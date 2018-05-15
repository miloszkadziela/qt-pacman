#include "powerup.h"

PowerUp::PowerUp(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/assets/power-up.png"));
}
