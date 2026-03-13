#include "Field.h"

const int FIELD_WIDTH = 1280;//イメージ横幅

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::Field)
	, mp_fieldImg(nullptr)

	,m_scrollx(0.0f)
	,m_scrollspeed(3.0f)

{
	// フィールド画像を読み込み
	mp_fieldImg = CImage::CreateImage("haikei.png");
}

// デストラクタ
Field::~Field()
{
	// フィールドの画像を削除
	if (mp_fieldImg != nullptr)
	{
		delete mp_fieldImg;
		mp_fieldImg = nullptr;
	}
}

// 更新
void Field::Update()
{
	m_scrollx += m_scrollspeed;

    //画像が1枚分進んだら最初に戻す
	if (m_scrollx >= FIELD_WIDTH)
	{
		m_scrollx = 0;
	}
}

// 描画
void Field::PreRender()
{
	// フィールドを描画、移動
	mp_fieldImg->SetPos( -(int)m_scrollx, 0);
	mp_fieldImg->Draw();

	mp_fieldImg->SetPos(FIELD_WIDTH-(int)m_scrollx, 0);
	mp_fieldImg->Draw();
}
