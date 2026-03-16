#include "TitleTask.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"


extern Field* g_field;
extern Player* g_player;

TitleTask::TitleTask()
    :Task(0)
{
    mp_title = CImage::CreateImage("smp1_title.png");
    mp_start = CImage::CreateImage("haikei.png");
    //mp_explain = CImage::CreateImage("field.png");

    mp_start->SetPos(600, 400);
    //mp_explain->SetPos(600, 500);
}

TitleTask::~TitleTask()
{
    delete mp_title;
    delete mp_start;
    //delete mp_explain;
}

void TitleTask::Update()
{
    if (PUSH(CInput::eMouseL))
    {
        // Game Start
        g_field = new Field();

        g_player = new Player(
            CVector3D(SCREEN_WIDTH * 0.15f, 0.0f, 0.0f));

        EnemyManager::Instance();

        //タイマー作動
        Timer::Start();

        Kill();

        /*
        // Explainクリック
        if (IsExplainButton())
        {
            DebugPrint::Print("Game Explain");
        }*/
    }
}

void TitleTask::Render()
{
    mp_title->SetPos(0, 0);
    mp_title->Draw();

    mp_start->Draw();
    //mp_explain->Draw();
}
