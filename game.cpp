#include "game.h"

Game::Game(QWidget* parent)
    : QGraphicsView(parent)
{
    setGeometry(x, y, WIDTH, HEIGHT);

    createGameMaps();
}

void Game::initializeGame()
{
    PlayerStats::Instance()->setStartingPlayerStats();
    initializeScene();
    show();
}

void Game::initializeScene()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsRectItem* blackBackground = new QGraphicsRectItem(0, 0, WIDTH, HEIGHT);
    blackBackground->setBrush(Qt::black);
    scene->addItem(blackBackground);
    background = new QGraphicsPixmapItem(QPixmap(":/images/assets/board.png"));
    background->setPos(0,0);
    scene->addItem(background);
    addObjects();
}

void Game::addObjects()
{
    EntityPosition entitiesPositions[5];
    int pointIndex = 0;
    int powerUpIndex = 0;
    int ghostIndex = 0;
    CollectibleItem **points = new CollectibleItem*[currentMap->objectsCount.numberOfPoints];
    CollectibleItem **powerUps = new CollectibleItem*[currentMap->objectsCount.numberOfPoints];
    for (int row = 0; row < UNIVERSAL_BOARD_SIZE; row++)
    {
        for (int col = 0; col < UNIVERSAL_BOARD_SIZE; col++)
        {
            QChar object = currentMap->game_map[row][col];
            int object_ascii = object.toLatin1();
            switch (object_ascii)
            {
                case '-':
                    points[pointIndex] = new CollectibleItem();
                    points[pointIndex]->setPixmap(QPixmap(":/images/assets/point.png"));
                    points[pointIndex]->typeOfObj = "point";
                    points[pointIndex]->setPos(BLOCK_SIZE * col, BLOCK_SIZE * row);
                    scene->addItem(points[pointIndex]);
                    pointIndex++;
                break;
                case 'S':
                    powerUps[powerUpIndex] = new CollectibleItem();
                    powerUps[powerUpIndex]->setPixmap(QPixmap(":/images/assets/power-up.png"));
                    powerUps[powerUpIndex]->typeOfObj = "powerUp";
                    powerUps[powerUpIndex]->setPos(BLOCK_SIZE * col, BLOCK_SIZE * row);
                    scene->addItem(powerUps[powerUpIndex]);
                    powerUpIndex++;
                break;
                case 'P':
                    entitiesPositions[0].entityX = col;
                    entitiesPositions[0].entityY = row;
                    entitiesPositions[0].entityExists = true;
                break;
                case 'G':
                    ghostIndex++;
                    entitiesPositions[ghostIndex].entityX = col;
                    entitiesPositions[ghostIndex].entityY = row;
                    entitiesPositions[ghostIndex].entityExists = true;
                break;
            }
        }
    }
    addEntities(entitiesPositions);
}

void Game::addPlayer(int col, int row)
{
    player = new Player();
    player->setPos(BLOCK_SIZE * col + 16, BLOCK_SIZE * row + 4);
    player->setFlag(QGraphicsItem::ItemIsFocusable, true);
    player->setFocus();
    scene->addItem(player);
}

void Game::loadGhostsImages(EntityPosition entitiesPositions[])
{
    if (entitiesPositions[1].entityExists)
    {
        ghost[0] = new GhostRed(QPixmap(":/images/assets/ghost_red.png"));
    }
    if (entitiesPositions[2].entityExists)
    {
        ghost[1] = new GhostOrange(QPixmap(":/images/assets/ghost_orange.png"));
    }
    if (entitiesPositions[3].entityExists)
    {
        ghost[2] = new GhostCyan(QPixmap(":/images/assets/ghost_cyan.png"));
    }
    if (entitiesPositions[4].entityExists)
    {
        ghost[3] = new GhostPink(QPixmap(":/images/assets/ghost_pink.png"));
    }
}

void Game::addGhost(int index, int col, int row)
{
    ghost[index]->setPos(BLOCK_SIZE * col + 4, BLOCK_SIZE * row + 4);
    scene->addItem(ghost[index]);
}

void Game::addEntities(EntityPosition entitiesPositions[])
{
    loadGhostsImages(entitiesPositions);
    for (unsigned int i = 0; i < (MAX_AMOUNT_OF_PLAYERS + currentMap->objectsCount.numberOfGhosts); i++)
    {
        switch (i)
        {
            case 0:
                if (entitiesPositions[i].entityExists)
                {
                    addPlayer(entitiesPositions[i].entityX, entitiesPositions[i].entityY);
                }
            break;
            case 1:
                if (entitiesPositions[i].entityExists)
                {
                    addGhost(i-1, entitiesPositions[i].entityX, entitiesPositions[i].entityY);
                }
            break;
            case 2:
                if (entitiesPositions[i].entityExists)
                {
                    addGhost(i-1, entitiesPositions[i].entityX, entitiesPositions[i].entityY);
                }
            break;
            case 3:
                if (entitiesPositions[i].entityExists)
                {
                    addGhost(i-1, entitiesPositions[i].entityX, entitiesPositions[i].entityY);
                }
            break;
            case 4:
                if (entitiesPositions[i].entityExists)
                {
                    addGhost(i-1, entitiesPositions[i].entityX, entitiesPositions[i].entityY);
                }
            break;
            default:
            break;
        }
    }
}

void Game::createGameMaps()
{
    maps[0] <<
    "WWWWWWWWWWWWWWWW" <<
    "WS-----WW-----SW" <<
    "W-WW-W-WW-W-WW-W" <<
    "W-WW-W-WW-W-WW-W" <<
    "W--------------W" <<
    "W-WW-WWWWWW-WW-W" <<
    "W-WW-WWWWWW-WW-W" <<
    "----------------" <<
    "W-WW-W-WW-W-WW-W" <<
    "W-WW-WGGGGW-WW-W" <<
    "W-WW-WWWWWW-WW-W" <<
    "W------P-------W" <<
    "W-WW-W-WW-W-WW-W" <<
    "W-WW-W-WW-W-WW-W" <<
    "WS-----WW-----SW" <<
    "WWWWWWWWWWWWWWWW";
    ObjectsCount objects =
    {
        108, // Number of points
        4,   // Number of powerUps
        4,   // Number of ghosts
        136  // Number of walls
    };
    currentMap = new GameMap(maps[0], objects);

    #ifdef DEBUG_MODE
    currentMap->printMap();
    #endif
}
