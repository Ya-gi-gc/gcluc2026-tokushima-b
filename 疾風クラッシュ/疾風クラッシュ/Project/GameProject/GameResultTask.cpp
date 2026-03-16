#include "GameResultTask.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "TitleTask.h"

extern Field* g_field;
extern Player* g_player;

GameResultTask::GameResultTask()
    : Task(0)
{
    mp_result = CImage::CreateImage("Clear.png");
    mp_playAgain = CImage::CreateImage("Over.png");
    mp_titleBtn = CImage::CreateImage("title.png");

    mp_playAgain->SetPos(600, 400);
    mp_titleBtn->SetPos(600, 500);

    //int elapsed = Timer::GetElapsed();
    //m_clearTime = 60 - elapsed;

    if (m_clearTime < 0)
        m_clearTime = 0;
}

GameResultTask::~GameResultTask()
{
    delete mp_result;
    delete mp_playAgain;
    delete mp_titleBtn;
}

void GameResultTask::Update()
{
    if (PUSH(CInput::eMouseL))
    {
        // もう一度プレイ
        if (m_select == 0)
        {
            g_field = new Field();

            g_player = new Player(
                CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));

            EnemyManager::Instance();

            Timer::Start();

            Kill();
        }

        // タイトルへ
        if (m_select == 1)
        {
            new TitleTask();

            Kill();
        }
    }
}

void GameResultTask::Render()
{
    mp_result->SetPos(0, 0);
    mp_result->Draw();

    mp_playAgain->Draw();
    mp_titleBtn->Draw();

    int min = m_clearTime / 60;
    int sec = m_clearTime % 60;

    DebugPrint::Print("Clear Time %d:%02d", min, sec);
}