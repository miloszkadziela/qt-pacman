#include "ghostcyan.h"

void GhostCyan::move()
{
    if (timeAfterLastTurn >= 5)
    {
         idleWalk();
    }
    drawIfEadible();
    moveIfPossible();
    timeAfterLastTurn++;
    warp();
    checkCollisonsWithPlayer();
}
