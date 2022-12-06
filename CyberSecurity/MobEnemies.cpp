#include <DxLib.h>
#include "MobEnemies.h"
#include "game.h"
#include "SceneMain.h"
#include <cassert>



namespace
{
	// X方向、Y方向の移動速度
	constexpr float kSpeed = 2.0f;
	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 8;
	// キャラクターアニメーションの速度
	constexpr int kCharAnimeChangeFrame = 8;

	// エフェクトアニメーションの速度
	constexpr int kEffectAnimeChangeFrame = 8;
	// モブエネミーの円形の当たり判定の大きさ
	static constexpr int kHitCircleSize = SceneMain::kMobEnemiesHitCircleSize;
}

MobEnemies::MobEnemies() :
	m_pMain(nullptr),
	m_shotInterval(0),
	m_pos(),
	m_vec(),
	m_count(),
	m_charAnimeNo(),
	m_charAnimeFrame(),
	m_charDirNo(),
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

MobEnemies::~MobEnemies()
{

}

void MobEnemies::init()
{
	m_pos.x = GetRand(Game::kScreenWidth);
	m_pos.y = 0;
	m_vec.x = 0.0f;
	m_vec.y = kSpeed;

	m_count = 0;
	m_charAnimeNo = {};
	m_charAnimeFrame = {};
	m_charDirNo = {};
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_shotInterval = kShotInterval;
}

void MobEnemies::update()
{
	//m_shotInterval--;
	m_charDirNo = 0;

	if (m_shotInterval < 0) m_shotInterval = 0;

	// モブエネミーの動きを止める
	if (m_pos.y >= 200)
	{
		m_vec.y = 0;
		if (m_vec.y == 0)m_count++;
		if (m_count >= 60)
		{
			m_count = 60;
			m_vec.y = kSpeed;
		}
	}




	m_charAnimeFrame++;
	if (m_charAnimeFrame >= kMobEnemiesGraphicDivX * kEffectAnimeChangeFrame)
	{
		m_charAnimeFrame = 0;
	}

	/*m_effectAnimeFrame++;
	if (m_effectAnimeFrame >= kMobEnemiesEffectDivX * kEffectAnimeChangeFrame)
	{
		m_effectAnimeFrame = 0;
	}*/



	int tempCharAnimeNo = m_charAnimeFrame / kCharAnimeChangeFrame;
	m_charAnimeNo = m_charDirNo + tempCharAnimeNo;

	m_charDirNo = 0;

	/*int tempEffectAnimeNo = m_effectAnimeFrame / kEffectAnimeChangeFrame;
	m_effectAnimeNo = m_effectDirNo + tempEffectAnimeNo;

	m_effectDirNo = 0;*/

	m_pos += m_vec;
	
}

void MobEnemies::draw()
{
	// モブエネミーの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0, m_handle[m_charAnimeNo], true);
	// エフェクトの表示(座標の中心に画像を表示する)
	/*DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.7, 0.0, m_effect[m_effectAnimeNo], true);*/

	assert(m_charAnimeNo <= 12);
	assert(m_charAnimeNo >= 0);

	// デバッグ
#if true
	// モブエネミーの当たり判定の大きさ
	DrawCircle((int)m_pos.x, (int)m_pos.y, kHitCircleSize, GetColor(0, 255, 255), FALSE);
#endif
}
