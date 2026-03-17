#include "Log.h"

//出現位置
#define CENTER_POS CVector2D(150.0f,128.0f)
//丸太の速度
#define ENEMY_SPEED 5.0f

// アニメーションデータ（3コマ）
static TexAnim logAnim[] =
{
    {0, 6},
    {1, 6},
    {2, 6}
};

static TexAnimData logAnimData[] =
{
    ANIMDATA(logAnim)
};

Log::Log(const CVector3D& pos)
    : EnemyBase(pos)
    , mp_image(nullptr)
{
    m_hp = 9999;

    mp_image = CImage::CreateImage("log.png");

    mp_image->SetCenter(CENTER_POS);

    mp_image->SetSize(235, 500);

    // ★ アニメーション登録
    mp_image->AttachAnimationData(logAnimData, 455, 768);
   
    // ★ 再生開始
    mp_image->ChangeAnimation(0, true);

    m_hitRange = CVector3D(25, 0, 800000);
}

Log::~Log()
{
    delete mp_image;
}

void Log::Update()
{
    mp_image->SetPos(CalcScreenPos());

    m_pos.x -= ENEMY_SPEED;

    //mp_image->SetAng(0.0f);

    mp_image->UpdateAnimation();
}

void Log::Render()
{
    mp_image->Draw();
}