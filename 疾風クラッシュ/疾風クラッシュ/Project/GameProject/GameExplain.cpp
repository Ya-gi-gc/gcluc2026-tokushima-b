#include "GameExplain.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "TitleTask.h"

extern Field* g_field;
extern Player* g_player;

GameExplainTask::GameExplainTask()
    : Task(0)
{
    mp_explain = CImage::CreateImage("set.png");
}

GameExplainTask::~GameExplainTask()
{
    delete mp_explain;
}

void GameExplainTask::Update()
{
    // Dキー → ゲームスタート
    if (PUSH(CInput::eButton15))
    {
        g_field = new Field();

        g_player = new Player(
            CVector3D(130.0f, 0.0f, 150.0f));

        g_player->SetField(g_field);

        EnemyManager::Instance();

        Timer::Start();

        Kill();
    }

    // Sキー → タイトル
    if (PUSH(CInput::eButton6))
    {
        new TitleTask();
        Kill();
    }
}

void GameExplainTask::Render()
{
    mp_explain->SetPos(0, 0);
    mp_explain->Draw();
}