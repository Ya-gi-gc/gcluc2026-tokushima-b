#include "Log.h"

#define CHIP_SIZE 600
#define CENTER_POS CVector2D(150.0f,128.0f)
#define ENEMY_SPEED 5.0 //“G‚Ì‘¬“x


Log::Log(const CVector3D& pos)
    : EnemyBase(pos)
    , mp_image(nullptr)
{
    // HP‚ð”ñí‚É‘å‚«‚­‚µ‚ÄŽ€‚È‚È‚¢‚æ‚¤‚É‚·‚é
    m_hp = 9999;

    mp_image = CImage::CreateImage("log.png");
    mp_image -> SetCenter(CENTER_POS);
}

Log::~Log()
{
    delete mp_image;
}

void Log::Update()
{
    mp_image->SetPos(CalcScreenPos());
    m_pos.x -= ENEMY_SPEED; //“G‚ÌˆÚ“®

}

void Log::Render()
{
    mp_image->Draw();
}