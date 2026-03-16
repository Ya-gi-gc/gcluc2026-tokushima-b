#pragma once
#include "Task.h"

class CImage;

class GameResultTask : public Task
{
private:

    int m_clearTime;
    int m_select;

    CImage* mp_result;
    CImage* mp_playAgain;
    CImage* mp_titleBtn;

public:

    GameResultTask();
    ~GameResultTask();

    void Update() override;
    void Render() override;
};