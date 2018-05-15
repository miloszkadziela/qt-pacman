#include "ghostred.h"

extern Game *game;

void GhostRed::move()
{
    if (!PlayerStats::Instance()->getPowerUpMode())
    {
        if (timeForMove < 400)
        {
                if(game->player->y() < this->y())
                {
                   setVelocityIfPossible(0 , GHOST_SPEED);
                }
                if(game->player->y() > this->y())
                {
                   setVelocityIfPossible(0 , -GHOST_SPEED);
                }
        }
        else if (timeForMove >= 800)
        {
            if(timeAfterLastTurn >= 5)
            {
                idleWalk();
            }
        }
        else if (timeForMove >= 1000)
        {
            timeForMove = 0;
        }
    }
    if (PlayerStats::Instance()->getPowerUpMode())
    {
        if(timeAfterLastTurn >= 5)
        {
            idleWalk();
        }
    }
    moveIfPossible();
    drawIfEadible();
    timeForMove++;
    timeAfterLastTurn++;
    warp();
    checkCollisonsWithPlayer();
}
