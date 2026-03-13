#pragma once
#include "EnemyBase.h"

class Log : public EnemyBase
{
private:
	CImage* mp_image;

public:
	Log(const CVector3D& pos);
	~Log();

	void Update();
	void Render();
};