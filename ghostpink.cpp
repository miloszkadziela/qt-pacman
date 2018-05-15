#include "ghostpink.h"

extern Game *game;

void GhostPink::move()
{
    if (!PlayerStats::Instance()->getPowerUpMode())
    {
        if (timeAfterLastTurn >= 200)
        {
            if(dir == 0)
            {
                setVelocityIfPossible(GHOST_SPEED, 0);
                dir++;
            }
            else if(dir == 1)
            {
                setVelocityIfPossible(0, -GHOST_SPEED);
                dir++;
            }
            else if(dir == 2)
            {
                setVelocityIfPossible(-GHOST_SPEED, 0);
                dir++;
            }
            else if(dir == 3)
            {
                setVelocityIfPossible(0, GHOST_SPEED);
                dir++;
            }
            else if(dir == 4)
            {
                dir = 0;
            }
            else
            {
                dir++;
            }
            timeAfterLastTurn = 0;
        }
   }
   else if (PlayerStats::Instance()->getPowerUpMode())
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
