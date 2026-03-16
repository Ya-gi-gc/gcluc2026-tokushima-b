#pragma once
#include "Task.h"

class TitleTask : public Task
{
private:

    CImage* mp_title;
    CImage* mp_start;
    CImage* mp_explain;

public:

    TitleTask();
    ~TitleTask();

    void Update() override;
    void Render() override;
};
