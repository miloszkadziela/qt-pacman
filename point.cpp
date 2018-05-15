#include "point.h"

Point::Point(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/assets/point.png"));
}
