#include <DxLib.h>
#include "SceneMain.h"
#include "game.h"


namespace 
{
	// X方向、Y方向の最大速度
	constexpr float kSpeedMax = 5.0f;
	constexpr float kAcc = 0.4f;
	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 8;
	// エネミーショットの円形の当たり判定の大きさ
	static constexpr float kShotCircleSize = SceneMain::kEnemyHitCircleSize;
	// キャラクターアニメーションの速度
	constexpr int kCharAnimeChangeFrame = 8;
	// エフェクトアニメーションの速度
	constexpr int kEffectAnimeChangeFrame = 1;

	const char* const kShotSound = "bgm/エネミーショット音.mp3";
	const char* const kBombSound = "bgm/エネミー爆発音.mp3";
	
}


Enemy::Enemy():
	m_pMain(nullptr),
	m_shotInterval(0),
	m_charAnimeNo(),
	m_charAnimeFrame(),
	m_charDirNo(),
	m_effectAnimeNo(),
	m_effectAnimeFrame(),
	m_effectDirNo(),
	m_shotSound(),
	m_bombSound(),
	m_count(),
	m_pos(),
	m_vec()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
	m_pos.x = Game::kScreenWidth / 2;
	m_pos.y = {50};
	m_vec.x = kSpeedMax;
	m_vec.y = {};
	
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_shotSound = LoadSoundMem(kShotSound);
	m_bombSound = LoadSoundMem(kBombSound);

	m_count = 0;

	m_shotInterval = kShotInterval;
}

void Enemy::update()
{
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	m_charDirNo = 0;


	if ((m_pMain) && (m_shotInterval <= 0))
	{
		PlaySoundMem(m_shotSound, DX_PLAYTYPE_BACK);
		//m_pMain->createEnemyShot(m_pos);
		m_pMain->createEnemyRevShot(m_pos);
		
		m_shotInterval = kShotInterval;
	}

	// enemyが右画面端に行くとき左に進ませる
	if (m_pos.x >= Game::kScreenWidth - kShotCircleSize)
	{
		m_vec.x -= kAcc;
		if (m_vec.x < -kSpeedMax)	m_vec.x = -kSpeedMax;
	}
	// enemyが左画面端に行くとき右に進ませる
	if (m_pos.x <= 0)
	{
		m_vec.x += kAcc;
		if (m_vec.x < -kSpeedMax)	m_vec.x = -kSpeedMax;
	}

	m_charAnimeFrame++;
	if (m_charAnimeFrame >= kEnemyGraphicDivX * kCharAnimeChangeFrame)
	{
		m_charAnimeFrame = 0;
	}

	int tempCharAnimeNo = m_charAnimeFrame / kCharAnimeChangeFrame;
	m_charAnimeNo = m_charDirNo + tempCharAnimeNo;

	m_charDirNo = 0;

	m_pos += m_vec;
}

void Enemy::draw()
{
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	// エネミーの表示
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		2.0, 0.0, m_handle[m_charAnimeNo], true);
#if true
	// エネミーの当たり判定の大きさ
	DrawCircle((int)m_pos.x,(int)m_pos.y, kShotCircleSize, GetColor(255, 255, 255), FALSE);
#endif
}


void Enemy::effect()
{
	if (m_count == 0)
	{
		PlaySoundMem(m_bombSound, DX_PLAYTYPE_BACK);
		m_count = 1;
	}
	// エフェクトの表示が終わったらここで処理を終了する
	if (m_effectAnimeNo >= 49)return;

	m_effectAnimeFrame++;
	if (m_effectAnimeFrame >= kEnemyEffectDivX * kEffectAnimeChangeFrame)
	{
		m_effectAnimeFrame = 0;
	}

	int tempEffectAnimeNo = m_effectAnimeFrame / kEffectAnimeChangeFrame;
	m_effectAnimeNo = m_effectDirNo + tempEffectAnimeNo;

	m_effectDirNo = 0;

	// エフェクトの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		3.0, 0.0, m_effect[m_effectAnimeNo], true);

}