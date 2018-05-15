#include "ghost.h"
#include "game.h"

extern Game *game;

Ghost::Ghost(QPixmap image) : ghostImage(image)
{
    srand(time(NULL));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    xVelocity = 0;
    yVelocity = -4;
    timeAfterLastTurn = 0;
}

bool Ghost::setVelocityIfPossible(int xVel, int yVel)
{
    setPos(x() + xVel, y() + yVel);
    if (!collidesWithItem(game->background, Qt::IntersectsItemBoundingRect))
    {
        xVelocity = xVel;
        yVelocity = yVel;
        setPos(x() - xVel, y() - yVel);
        return true;
    }
    setPos(x() - xVel, y() - yVel);
    return false;
}

void Ghost::moveIfPossible()
{
    setPos(x() + xVelocity, y() + yVelocity);
    if (collidesWithItem(game->background, Qt::IntersectsItemBoundingRect))
    {
        setPos(x() - xVelocity, y() - yVelocity);
        if (!setVelocityIfPossible(yVelocity, xVelocity))
        {
            if (!setVelocityIfPossible(-yVelocity, -xVelocity))
            {
                setVelocityIfPossible(-xVelocity, -yVelocity);
            }
        }
        timeAfterLastTurn = 0;
    }
}

void Ghost::checkCollisonsWithPlayer()
{
    if (collidesWithItem(game->player, Qt::IntersectsItemBoundingRect))
    {
        if(PlayerStats::Instance()->getPowerUpMode())
        {
            for (int k = 0; k < UNIVERSAL_BOARD_SIZE; k ++)
            {
                for (int j = 0; j < UNIVERSAL_BOARD_SIZE; j ++)
                {
                    if (game->currentMap->game_map[j][k] == 'G')
                    {
                        setPos(BLOCK_SIZE*k + GHOST_POSITION_OFFSET, BLOCK_SIZE*j + GHOST_POSITION_OFFSET);
                    }
                }
            }
            PlayerStats::Instance()->increaseScore(KILL_SCORE);
        }
        else if(!PlayerStats::Instance()->getPowerUpMode())
        {
            PlayerStats::Instance()->decreaseLives();
            for (int i = 0; i < UNIVERSAL_BOARD_SIZE; i ++)
            {
                for (int j = 0; j < UNIVERSAL_BOARD_SIZE; j ++)
                {
                    if (game->currentMap->game_map[j][i] == 'P')
                    {
                        game->player->setPos(BLOCK_SIZE*i+PLAYER_X_OFFSET, BLOCK_SIZE*j+PLAYER_Y_OFFSET);
                    }
                }
            }
            int add = 0;
            for (unsigned int i = 0; i < game->currentMap->objectsCount.numberOfGhosts; i++, add++)
            {
                for (int k = 0; k < UNIVERSAL_BOARD_SIZE; k ++)
                {
                    for (int j = 0; j < UNIVERSAL_BOARD_SIZE; j ++)
                    {
                        if (game->currentMap->game_map[j][k] == 'G')
                        {
                            game->ghost[i]->setPos(BLOCK_SIZE*(k-3+add) + GHOST_POSITION_OFFSET, BLOCK_SIZE*j + GHOST_POSITION_OFFSET);
                        }
                    }
                }
            }
            xVelocity = -GHOST_SPEED;
            //yVelocity = -GHOST_SPEED;
        }
    }
}

void Ghost::drawIfEadible()
{
    if (PlayerStats::Instance()->getPowerUpMode())
    {
        setPixmap(QPixmap(":/images/assets/eatable_ghost.png").scaled(GHOST_SIZE, GHOST_SIZE));
    }
    else
    {
        setPixmap(ghostImage.scaled(GHOST_SIZE, GHOST_SIZE));
    }
}

void Ghost::warp()
{
    if (x() < -GHOST_SIZE + 12)
    {
        setPos(WIDTH - 12, y());
    }
    else if (x() > WIDTH - 12)
    {
        setPos(-GHOST_SIZE + 12, y());
    }
    if (y() < -GHOST_SIZE + 12)
    {
        setPos(x(), HEIGHT - 12);
    }
    else if (y() > HEIGHT - 12)
    {
        setPos(x(), -GHOST_SIZE + 12);
    }
}

void Ghost::idleWalk()
{
    int randomNumber = rand() % 3;
    if (randomNumber == 0)
    {
        setVelocityIfPossible(yVelocity, xVelocity);
    }
    else if (randomNumber == 1)
    {
        setVelocityIfPossible(-yVelocity, -xVelocity);
    }
    timeAfterLastTurn = 0;
}
