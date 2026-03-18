#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "GameResultTask.h"
#include "Field.h"

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

extern Field* g_field;

#define CHIP_SIZE 384	// 1コマのサイズ
#define CENTER_POS CVector2D(192.0f, 320.0f)	// 中心座標
#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 10.0f	// 奥方向の移動速度
#define JUMP_SPEED 17.4f	// ジャンプ速度
#define GRAVITY -0.85f		// 重力
#define ATTACK_INDEX 2		// 攻撃が発生するアニメーションの番号
#define ATTACK_RANGE CVector3D(100.0f, 10.0f, 25.0f)	// 攻撃範囲
float  COOL_TIME = 0.0f;  //攻撃クールタイム 

#define SPAWN_RANGE_MIN_Z -80	// Z軸のプレイヤーの最小値
#define SPAWN_RANGE_MAX_Z 160	// Z軸のプレイヤーの最大値

bool g_isGameResult = false;

// プレイヤーのアニメーションデータの前宣言
TexAnimData Player::ANIM_DATA[(int)EAnimType::Num] =
{
	// 待機アニメーション
	{
		new TexAnim[4]
		{
			{6, 10}, {7, 10}, {8, 10},
			{9, 10},
		},
		4
	},
	// 移動アニメーション
	{
		new TexAnim[6]
		{
			{0, 6}, {1, 6}, {2, 6},
			{5, 6}, {4, 6}, {5, 6}
		},
		6
	},
	// 死亡アニメーション
	{
		new TexAnim[3]
		{
			{12, 12},
			{13, 12},
			{14, 12},
		},
		3
	},
	// 攻撃アニメーション
	{
		new TexAnim[4]
		{
			{12, 6},
			{13, 6},
			{14, 6},
			{15, 6},
		},
		3
	},
};


// コンストラクタ
Player::Player(const CVector3D& pos)
	: CharaBase(pos)
	, m_state(EState::Idle)
	, m_stateStep(0)
	, mp_image(nullptr)
{
	m_hp = 100;

	// プレイヤーの画像を読み込み
	mp_image = CImage::CreateImage
	(
		"player3.png",	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(CENTER_POS);
	mp_heart = CImage::CreateImage("heart.png");
}

// デストラクタ
Player::~Player()
{
	// 画像データを削除
	delete mp_image;
}

// 現在の状態を切り替え
void Player::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 移動処理の更新
bool Player::UpdateMove()
{
	//常時走りアニメーション
	bool isMove = true;
	

		// 左キーを押している間
		/*if (HOLD(CInput::eLeft))
		{
			// 左方向へ移動
			m_pos.x -= MOVE_SPEED_X;
			mp_image->SetFlipH(true);
			isMove = true;
		}
		// 右キーを押している間
		else if (HOLD(CInput::eRight))
		{
			// 右方向へ移動
			m_pos.x += MOVE_SPEED_X;
			mp_image->SetFlipH(false);
			isMove = true;
		}
		*/
		// [W]キーを押している間
		if (HOLD(CInput::eButton14))
		{
			// 奥方向へ移動
			m_pos.z -= MOVE_SPEED_Z;
			isMove = true;
		}
		// [A]キーを押している間
		else if (HOLD(CInput::eButton16))
		{
			// 手前方向へ移動
			m_pos.z += MOVE_SPEED_Z;
			isMove = true;
		}

		//プレイヤーの移動範囲
		if (m_pos.z < SPAWN_RANGE_MIN_Z)m_pos.z = SPAWN_RANGE_MIN_Z;
		if (m_pos.z > SPAWN_RANGE_MAX_Z)m_pos.z = SPAWN_RANGE_MAX_Z;

		return isMove;
}
// 待機時の更新処理
void Player::StateIdle()
{
	// 移動処理
	bool isMove = UpdateMove();
	// 移動状態に合わせて、アニメーションを切り替え
	EAnimType anim = isMove ? EAnimType::Move : EAnimType::Idle;
	mp_image->ChangeAnimation((int)anim);
	// [スペース]キーでジャンプ状態へ移行
	if (PUSH(CInput::eButton5))
	{
		ChangeState(EState::Jump);
	}
	// クールタイムが0以下かつ[左クリック]キーで攻撃状態へ移行
	else if (COOL_TIME <= 0 && PUSH(CInput::eMouseL))
	{
		ChangeState(EState::Attack);

		//クールタイムの設定
		COOL_TIME = 60.0f;

		//デバック用クールタイム0
		// //COOL_TIME = 0.0f;

	}
}

// ジャンプ中の更新処理
void Player::StateJump()
{
	// ステップごとに処理を切り替え
	switch(m_stateStep)
	{
		// ステップ0：ジャンプ開始
		case 0:

			// ★ジャンプSE再生
			mciSendString("close jump", NULL, 0, NULL);
			mciSendString("open \"aau.mp3\" type mpegvideo alias jump", NULL, 0, NULL);
			mciSendString("play jump", NULL, 0, NULL);

			// Y軸（高さ）の移動速度にジャンプを速度を設定し、
			// 接地状態を解除する
			m_moveSpeedY = JUMP_SPEED;
			m_isGrounded = false;
			m_stateStep++;

			break;
		// ステップ1：ジャンプ終了
		case 1:
			// 接地したら、待機状態へ移行
			if (m_isGrounded)
			{
				ChangeState(EState::Idle);
			}
			break;
	}

	// 移動処理
	bool isMove = UpdateMove();
	mp_image->ChangeAnimation((int)EAnimType::Idle);
}

// 攻撃中の更新処理
void Player::StateAttack()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：攻撃アニメーションに切り替え
		case 0:
			mp_image->ChangeAnimation((int)EAnimType::Attack, false);
			m_stateStep++;
			break;
			// ステップ1：攻撃判定
		case 1:
			// 攻撃アニメーションが攻撃タイミングまで進めば
			if (mp_image->GetIndex() >= ATTACK_INDEX)
			{
				// ★攻撃SE再生
				mciSendString("close attack", NULL, 0, NULL);
				mciSendString("open \"a.mp3\" type mpegvideo alias attack", NULL, 0, NULL);
				mciSendString("play attack", NULL, 0, NULL);


				// 一番近い敵にダメージを与える
				EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(m_pos, ATTACK_RANGE);
				if (enemy != nullptr)
				{
					enemy->TakeDamage(100);
				}
				m_stateStep++;
			}
			break;
			// ステップ2：アニメーション終了待ち
		case 2:
			// 攻撃アニメーションが終了したら、待機状態へ移行
			if (mp_image->CheckAnimationEnd())
			{
				ChangeState(EState::Idle);
			}
			break;
	}
}

// 死亡時の更新処理
void Player::StateDeath()
{
}

// 更新処理
void Player::Update()
{
	COOL_TIME--;

	// ① 無敵時間減少
	if (m_invincible > 0)
	{
		m_invincible -= CFPS::GetDeltaTime();
		blinkTimer++;
		if (blinkTimer % 5 == 0)
		{
			blink = !blink; // 点滅切り替え
		}
	}
	else
	{
		blink = true;
	}

	// ② 敵との当たり判定
	EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(m_pos, CVector3D(50, 50, 50));

	//敵と当たった時にジャンプをしているならダメージは受けない　デバック用自爆ボタン[Q]
	if (enemy != nullptr && m_invincible <= 0 && m_state != EState::Jump || HOLD(CInput::eButton17))
	{
		// ★ダメージSE
		mciSendString("close damage", NULL, 0, NULL);
		mciSendString("open \"uaa.mp3\" type mpegvideo alias damage", NULL, 0, NULL);
		mciSendString("play damage", NULL, 0, NULL);

		m_life--;          // ライフ減
		m_invincible = 2.0f; // 無敵時間2秒
		blinkTimer = 0;       // 点滅リセット

		if (m_life <= 0)
		{
			// ★死亡SE再生
			mciSendString("close death", NULL, 0, NULL);
			mciSendString("open \"sibou.mp3\" type mpegvideo alias death", NULL, 0, NULL);
			mciSendString("play death", NULL, 0, NULL);

			ChangeState(EState::Death); // ライフ0で死亡
			
			g_isGameResult = true;

			EnemyManager::Instance()->KillAllEnemies();
			EnemyManager::Destroy();

			delete g_field;
			g_field = nullptr;

			new GameResultTask();  // ← リザルト画面生成
			Kill();                // ← プレイヤー削除
			return;
		}
	}


	// 現在の状態に合わせて、処理を切り替える
	switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Jump:		StateJump();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Death:		StateDeath();	break;
	}

	// Y軸（高さ）の移動を座標に反映
	m_pos.y += m_moveSpeedY;
	m_moveSpeedY += GRAVITY;	// Y軸の移動速度に重力を加算
	// 地面より下にいくと
	if (m_pos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		m_pos.y = 0.0f;
		m_moveSpeedY = 0.0f;
		m_isGrounded = true;
	}

	// イメージに座標を設定して、アニメーションを更新
	mp_image->SetPos(CalcScreenPos());
	mp_image->UpdateAnimation();

	DebugPrint::Print("プレイヤー位置：%.2f, %.2f, %.2f", m_pos.x, m_pos.y, m_pos.z);
}

// 描画処理
void Player::Render()
{
	// 点滅表示
	if (blink)
	{
		mp_image->Draw();
	}

	// ハート描画（1枚を3回）
	for (int i = 0; i < m_life; i++)
	{
		mp_heart->SetPos(CVector2D(30 + i * 60, 80));
		mp_heart->Draw();
	}
}
