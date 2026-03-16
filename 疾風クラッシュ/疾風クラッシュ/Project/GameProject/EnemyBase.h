#pragma once
#include "CharaBase.h"

// 敵のベースクラス
class EnemyBase : public CharaBase
{
public:
	// コンストラクタ
	EnemyBase();
	EnemyBase(const CVector3D& pos);
	// デストラクタ
	virtual ~EnemyBase();

	//当たり判定サイズ
	const CVector3D& GetHitRange() const { return m_hitRange; }
protected:

	CVector3D m_hitRange;

};
