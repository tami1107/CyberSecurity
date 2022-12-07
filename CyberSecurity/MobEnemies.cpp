#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "MobEnemies.h"
#include "game.h"


namespace
{
	// X方向、Y方向の移動速度
	constexpr float kSpeed = 2.0f;
	
	// キャラクターアニメーションの速度
	constexpr int kCharAnimeChangeFrame = 8;

	// エフェクトアニメーションの速度
	constexpr int kEffectAnimeChangeFrame = 8;

	// プレイヤーの円形の当たり判定の大きさ
	static constexpr int kPlayerHitCircleSize = SceneMain::kPlayerHitCircleSize;	

	// モブエネミーの円形の当たり判定の大きさ
	static constexpr int kMobEnemyHitCircleSize = SceneMain::kMobEnemiesHitCircleSize;
}

MobEnemies::MobEnemies() :
	m_pMain(nullptr),
	m_isExist(),
	
	m_pos(),
	m_vec(),
	m_frameCount(),
	m_memberCount(),
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

	m_frameCount = 0;
	m_memberCount = 0;
	m_charAnimeNo = {};
	m_charAnimeFrame = {};
	m_charDirNo = {};
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_isExist = true;

	
}

void MobEnemies::update()
{



	// 敵が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;



	m_charDirNo = 0;

	

	// モブエネミーの動きを止める
	if (m_pos.y >= 150)
	{
		if (m_memberCount == 0)
		{
			m_pMain->createEnemyShot(m_pos);
			m_memberCount = 1;
		}
		

		m_vec.y = 0;
		if (m_vec.y == 0)m_frameCount++;
		if (m_frameCount >= 60)
		{
			m_frameCount = 60;
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

	// モブエネミーが画面外に出た場合、存在を消す
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}
	


void MobEnemies::draw()
{
	// 敵が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;



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
	DrawCircle((int)m_pos.x, (int)m_pos.y, kMobEnemyHitCircleSize, GetColor(0, 255, 255), FALSE);
#endif
}


