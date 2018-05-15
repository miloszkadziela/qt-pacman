#include "ghostorange.h"

extern Game *game;

void GhostOrange::move()
{
    if (!followPlayer())
    {
       if (timeAfterLastTurn >= 5)
       {
            idleWalk();
       }
    }
    drawIfEadible();
    moveIfPossible();
    timeAfterLastTurn++;
    warp();
    checkCollisonsWithPlayer();
}

bool GhostOrange::followPlayer()
{
    if (!PlayerStats::Instance()->getPowerUpMode())
    {
        if (this->x() == game->player->x())
        {
            if (this->y() > game->player->y())
            {
                setVelocityIfPossible(0, -GHOST_SPEED);
                return true;
            }
            else
            {
                setVelocityIfPossible(0, GHOST_SPEED);
                return true;
            }
        }
        else if (this->y() == game->player->y())
        {
            if (this->x() > game->player->x())
            {
                setVelocityIfPossible(-GHOST_SPEED, 0);
                return true;
            }
            else
            {
                setVelocityIfPossible(GHOST_SPEED, 0);
                return true;
            }
        }
    }
    else
    {
        if (this->x() == game->player->x())
        {
            if (this->y() > game->player->y())
            {
                setVelocityIfPossible(0, GHOST_SPEED);
                return true;
            }
            else
            {
                setVelocityIfPossible(0, -GHOST_SPEED);
                return true;
            }
        }
        else if (this->y() == game->player->y())
        {
            if (this->x() > game->player->x())
            {
                setVelocityIfPossible(GHOST_SPEED, 0);
                return true;
            }
            else
            {
                setVelocityIfPossible(-GHOST_SPEED, 0);
                return true;
            }
        }
    }
    return false;
}
