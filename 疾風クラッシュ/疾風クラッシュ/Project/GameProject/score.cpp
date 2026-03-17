#include "score.h"

int Score::m_totalScore = 0;
int Score::m_timeScore = 0;
int Score::m_enemyScore = 0;

int Score::m_timeLimit = 30;
int Score::m_frame = 0;

void Score::Init()
{
    m_totalScore = 0;
    m_timeScore = 0;
    m_enemyScore = 0;

    m_timeLimit = 30;
    m_frame = 0;
}

void Score::Update()
{
    m_frame++;

    if (m_frame >= 60)
    {
        m_frame = 0;

        if (m_timeLimit > 0)
        {
            m_timeLimit--;
            m_timeScore += 100;
            m_totalScore += 100;
        }
    }
}

void Score::EnemyDown()
{
    m_enemyScore += 10;
    m_totalScore += 10;
}

int Score::GetScore()
{
    return m_totalScore;
}

int Score::GetTime()
{
    return m_timeLimit;
}

bool Score::IsTimeUp()
{
    return (m_timeLimit <= 0);
}