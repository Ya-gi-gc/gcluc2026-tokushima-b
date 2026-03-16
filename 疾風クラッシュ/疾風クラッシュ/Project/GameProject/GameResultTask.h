#pragma once
#include "Task.h"

class GameResultTask : public Task
{
private:

    int m_select;

    CImage* mp_result; // ‰æ‘œ
    CImage* mp_restart;
    CImage* mp_titleBtn;
    CImage* mp_exit;
    CImage* mp_marker;


public:
    GameResultTask();
    ~GameResultTask();

    void Update() override;
    void Render() override;
};