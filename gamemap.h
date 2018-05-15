#ifndef GAMEMAP_H
#define GAMEMAP_H

// Number of columns & rows in the game maps
#define UNIVERSAL_BOARD_SIZE 16

// Maximum amount of entities in the game map
#define MAX_AMOUNT_OF_PLAYERS 1
#define MAX_AMOUNT_OF_GHOSTS 4
#define MAX_AMOUNT_OF_ENTITIES (MAX_AMOUNT_OF_PLAYERS + MAX_AMOUNT_OF_GHOSTS)

#include <QChar>
#include <QString>
#include <QVector>
#include <QDebug>

using namespace std;

// Amount of objects in the game map
struct ObjectsCount
{
    unsigned int numberOfPoints;
    unsigned int numberOfPowerUps;
    unsigned int numberOfGhosts;
    unsigned int numberOfWalls;
};

class GameMap
{
public:
    GameMap(QStringList map, ObjectsCount objects);
    void printMap();
    QStringList game_map;
    ObjectsCount objectsCount;
};

#endif // GAMEMAP_H
