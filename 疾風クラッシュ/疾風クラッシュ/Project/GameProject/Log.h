#pragma once
#include "EnemyBase.h"

class Log : public EnemyBase
{
public:
    Log(const CVector3D& pos);
    ~Log();

    void Update();
    void Render();

private:
    CImage* mp_image;
};