#include "gamemap.h"

GameMap::GameMap(QStringList map, ObjectsCount objects)
    : game_map(map), objectsCount(objects)
{
}

void GameMap::printMap()
{
    for (int row = 0; row < UNIVERSAL_BOARD_SIZE; row++)
    {
        qDebug() << game_map[row];
    }
    qDebug() << "\nNumber of points:" << objectsCount.numberOfPoints
             << "\nNumber of powerUps:" << objectsCount.numberOfPowerUps
             << "\nNumber of ghosts:" << objectsCount.numberOfGhosts
             << "\nNumber of walls:" << objectsCount.numberOfWalls;
}
