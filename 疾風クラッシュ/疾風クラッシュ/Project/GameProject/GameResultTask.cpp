#include "GameResultTask.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "TitleTask.h"

extern Field* g_field;
extern Player* g_player;

extern bool g_isGameResult;

GameResultTask::GameResultTask()
    : Task(0)
{
    mp_result = CImage::CreateImage("Clear.png");

    // 敵削除
    if (EnemyManager::Instance() != nullptr)
    {
        EnemyManager::Instance()->KillAllEnemies();
        EnemyManager::Destroy();
    }

    mp_restart = CImage::CreateImage("gamestart.png");
    mp_exit = CImage::CreateImage("exitgame.png");

    mp_marker = CImage::CreateImage("テッポウウオ.png");

    m_select = 0;
}

GameResultTask::~GameResultTask()
{
    delete mp_result;
    delete mp_restart;
    delete mp_exit;
    delete mp_marker;
}

void GameResultTask::Update()
{
    // 上
    if (PUSH(CInput::eUp))
    {
        m_select--;

        if (m_select < 0)
            m_select = 1;
    }

    // 下
    if (PUSH(CInput::eDown))
    {
        m_select++;

        if (m_select > 1)
            m_select = 0;
    }

    // 決定
    if (PUSH(CInput::eButton10))
    {
        switch (m_select)
        {
        case 0: // リスタート

            //フラッグリセット
            g_isGameResult = false;

            // フィールド生成
            g_field = new Field();

            // プレイヤー生成
            g_player = new Player(
                CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));

            g_player->SetField(g_field);

            // 敵マネージャー生成
            EnemyManager::Instance();

            // スコアリセット
            // Score::Reset();

            Kill();
            break;

        case 1: // ゲーム終了
            exit(0);
            break;
        }
    }
}

void GameResultTask::Render()
{
    mp_result->SetPos(0, 0);
    mp_result->Draw();

    int x = 700;
    int y = 450;
    int space = 120;

    mp_restart->SetPos(x, y);
    mp_restart->Draw();

    mp_exit->SetPos(x, y + space);
    mp_exit->Draw();

    //マーカー
    int markerX = x - 120;
    int markerY = y + space * m_select;

    mp_marker->SetPos(markerX, markerY);
    mp_marker->Draw();
}