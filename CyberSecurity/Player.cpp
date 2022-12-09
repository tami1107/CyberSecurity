#include <DxLib.h>
#include "game.h"
#include "Player.h"
#include "SceneMain.h"


namespace 
{
	// プレイヤーの低速化
	constexpr float  kSlowSpeed = 2.0f;
	// X方向、Y方向の最大速度
	constexpr float kSpeed = 5.0f;
	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 8;
	// エフェクトアニメーションの速度
	constexpr int kEffectAnimeChangeFrame = 8;
	// プレイヤーの円形の当たり判定の大きさ
	static constexpr float kHitCircleSize = SceneMain::kPlayerHitCircleSize;	
}

Player::Player() :
	m_pMain(nullptr),
	m_shotInterval(0),
	m_pos(),
	m_vec(),
	m_charAnimeNo(),
	m_effectAnimeNo(),
	m_effectAnimeFrame(),
	m_effectDirNo()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	for (auto& handle : m_effect)
	{
		handle = -1;
	}
}

Player::~Player()
{
}

void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_charAnimeNo = 1;
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_shotInterval = kShotInterval;
}

void Player::update()
{
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_charAnimeNo = 1;
	m_effectDirNo = 8;

	
	if (padState & PAD_INPUT_UP)
	{
		m_effectDirNo = 11;
		// 3ボタンを押していたら速度を下げる
		if (padState & PAD_INPUT_3)m_pos.y -= (kSpeed - kSlowSpeed);
		else m_pos.y -= kSpeed;
		
	}
	if (padState & PAD_INPUT_DOWN)
	{
		m_effectDirNo = 4;
		// 3ボタンを押していたら速度を下げる
		if (padState & PAD_INPUT_3)m_pos.y += (kSpeed - kSlowSpeed);
		else m_pos.y += kSpeed;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		// 3ボタンを押していたら速度を下げる
		if (padState & PAD_INPUT_3)m_pos.x -= (kSpeed - kSlowSpeed);
		else m_pos.x -= kSpeed;
		// 0番の画像を表示する
		m_charAnimeNo = 0;
	}
	if (padState & PAD_INPUT_RIGHT)
	{	// 3ボタンを押していたら速度を下げる
		if (padState & PAD_INPUT_3)m_pos.x += (kSpeed - kSlowSpeed);
		else m_pos.x += kSpeed;
		// 2番の画像を表示する
		m_charAnimeNo = 2;
	}
	if ((padState & PAD_INPUT_LEFT)&&(padState & PAD_INPUT_RIGHT)) m_charAnimeNo = 1;// 1番の画像を表示する
	if (padState & PAD_INPUT_3)m_effectDirNo = 0;

	// ショット
	if (padState & PAD_INPUT_1)
	{
		if ((m_pMain) && (m_shotInterval <= 0))
		{
			m_pMain->createShot(m_pos);
			m_shotInterval = kShotInterval;
		}
	}

	m_effectAnimeFrame++;
	if (m_effectAnimeFrame >= kPlayerEffectDivX * kEffectAnimeChangeFrame)
	{
		m_effectAnimeFrame = 0;
	}



	int tempAnimeNo = m_effectAnimeFrame / kEffectAnimeChangeFrame;
	m_effectAnimeNo = m_effectDirNo + tempAnimeNo;

	m_effectDirNo = 0;


	m_pos += m_vec;
}

void Player::draw()
{
	// プレイヤーエフェクトの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y+18),
		1.0, 0.0, m_effect[m_effectAnimeNo], true);
	// プレイヤーの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		0.7, 0.0, m_handle[m_charAnimeNo], true);
#if true
	// プレイヤーの当たり判定の大きさ
	DrawCircle((int)m_pos.x, (int)m_pos.y, kHitCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}


