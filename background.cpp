#include "background.h"

Background::Background(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/assets/board.png"));
}
