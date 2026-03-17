#pragma once
#ifndef SCORE_H
#define SCORE_H

class Score
{
public:

    static void Init();

    static void Update();      // –ˆƒtƒŒ[ƒ€
    static void EnemyDown();   // “GŒ‚”j

    static int GetScore();
    static int GetTime();
    static bool IsTimeUp();

private:

    static int m_totalScore;
    static int m_timeScore;
    static int m_enemyScore;

    static int m_timeLimit;
    static int m_frame;
};

#endif