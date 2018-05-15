#ifndef GAMEAREA_H
#define GAMEAREA_H

// When this constant is declared, debugging is on
#define DEBUG_MODE
#ifdef DEBUG_MODE
#include <QDebug>
#endif

// GraphicsView position
#define GRAPHICS_VIEW_X 44
#define GRAPHICS_VIEW_Y 70

// QGraphicsScene dimensions
#define WIDTH 512
#define HEIGHT 512

// Graphical size of a field in the game_map array
#define BLOCK_SIZE 32

// Map properties
#define NUMBER_OF_MAPS 1
#define MAX_AMOUNT_OF_OBJECTS 256

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "point.h"
#include "powerup.h"
#include "gamemap.h"
#include "background.h"
#include "player.h"
#include "ghost.h"
#include "ghostred.h"
#include "ghostorange.h"
#include "ghostpink.h"
#include "ghostcyan.h"
#include "collectibleitem.h"

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    struct EntityPosition
    {
        int entityX = 0;
        int entityY = 0;
        bool entityExists = false;
    };
public:
    Game(QWidget* parent = 0);
    void createGameMaps();
    void initializeGame();
    void initializeScene();
    void addObjects();
    void addEntities(EntityPosition entitiesPositions[MAX_AMOUNT_OF_ENTITIES]);
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    GameMap *currentMap;
    Player *player;
    Ghost *ghost[MAX_AMOUNT_OF_GHOSTS];
    CollectibleItem **points[MAX_AMOUNT_OF_OBJECTS];
    CollectibleItem **powerUps[MAX_AMOUNT_OF_OBJECTS];
private:
    QStringList maps[NUMBER_OF_MAPS];
    int x = GRAPHICS_VIEW_X;
    int y = GRAPHICS_VIEW_Y;
    void addPlayer(int col, int row);
    void addGhost(int index, int col, int row);
    void loadGhostsImages(EntityPosition entitiesPositions[]);
};

#endif // GAMEAREA_H
