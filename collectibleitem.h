#ifndef COLLECTIBLEITEM_H
#define COLLECTIBLEITEM_H

#define POINT_SCORE 10
#define POWERUP_SCORE 50

#include <QGraphicsPixmapItem>
#include <QString>
#include "playerstats.h"

class CollectibleItem : public QGraphicsPixmapItem
{
public:
    CollectibleItem(QGraphicsItem *parent = 0);
    ~CollectibleItem();
    QString typeOfObj = "";
};

#endif // COLLECTIBLEITEM_H
