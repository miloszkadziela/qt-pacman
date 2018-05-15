#include "collectibleitem.h"

CollectibleItem::CollectibleItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
}

CollectibleItem::~CollectibleItem()
{
    if (typeOfObj == "point")
    {
        PlayerStats::Instance()->increaseItemsCollected();
        PlayerStats::Instance()->increaseScore(POINT_SCORE);
    }
    if (typeOfObj == "powerUp")
    {
        PlayerStats::Instance()->setPowerUpMode(true);
        PlayerStats::Instance()->increaseItemsCollected();
        PlayerStats::Instance()->increaseScore(POWERUP_SCORE);
    }
}
