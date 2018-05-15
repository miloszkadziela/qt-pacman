#include "playerstats.h"
#include "game.h"

extern Game *game;
PlayerStats* PlayerStats::m_Instance;

PlayerStats::PlayerStats()
{
    emit gameState(MENU);
}

void PlayerStats::increaseItemsCollected()
{
    if (itemsCollected >= (game->currentMap->objectsCount.numberOfPoints + game->currentMap->objectsCount.numberOfPowerUps))
    {
        emit gameState(GAMEOVER);
    }
    else
    {
        itemsCollected++;
    }
}

void PlayerStats::decreaseLives()
{
    if (lives > 1)
    {
        lives--;
        emit updateStats();
    }
    else
    {
        emit gameState(GAMEOVER);
    }
}

int PlayerStats::getLives()
{
    return lives;
}

void PlayerStats::increaseScore(int amount)
{
    score += amount;
    emit updateStats();
}

int PlayerStats::getScore()
{
    return score;
}

void PlayerStats::setPowerUpMode(bool hasPowerUp)
{
    powerUpMode = hasPowerUp;
}

bool PlayerStats::getPowerUpMode()
{
    return powerUpMode;
}

void PlayerStats::setStartingPlayerStats()
{
    lives = STARTING_LIVES;
    score = STARTING_SCORE;
    powerUpMode = STARTING_MODE;
    itemsCollected = 0;
}
