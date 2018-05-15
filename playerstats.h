#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

// Stacked Widget page indexes
#define MENU 0
#define GAME 1
#define GAMEOVER 2

// Player starting stats
#define STARTING_LIVES 3
#define STARTING_SCORE 0
#define STARTING_MODE false

#include <QObject>
#include <assert.h>

class PlayerStats : public QObject
{
    Q_OBJECT
    static PlayerStats *m_Instance;
    int lives;
    int score;
    unsigned int itemsCollected;
    bool powerUpMode;
    PlayerStats();
signals:
    void updateStats();
    void gameState(int state);
public:
    static PlayerStats* Instance()
    {
        if (!m_Instance)
        {
            m_Instance = new PlayerStats;
        }
        assert(m_Instance != NULL);
        return m_Instance;
    }
    void increaseItemsCollected();
    void decreaseLives();
    int getLives();
    void increaseScore(int amount);
    int getScore();
    void setPowerUpMode(bool hasPowerUp);
    bool getPowerUpMode();
    void setStartingPlayerStats();
};

#endif // PLAYERSTATS_H
