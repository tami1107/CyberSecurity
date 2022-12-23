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
	constexpr int kEffectAnimeChangeFrame = 1;

	// 停止位置
	constexpr float kStopPosition = 150.0f;

	// 停止時間
	constexpr int kStopTime = 60;

	// プレイヤーの円形の当たり判定の大きさ
	static constexpr float kPlayerHitCircleSize = SceneMain::kPlayerHitCircleSize;	

	// モブエネミーの円形の当たり判定の大きさ
	static constexpr float kMobEnemyHitCircleSize = SceneMain::kMobEnemiesHitCircleSize;

	const char* const kShotSound = "bgm/モブエネミーショット音.mp3";
	const char* const kBombSound = "bgm/モブエネミー爆発音.mp3";
}

MobEnemies::MobEnemies() :
	m_pMain(nullptr),
	m_isExist(),
	
	m_pos(),
	m_vec(),
	m_frameCount(),
	m_shotFlag(),
	m_charAnimeNo(),
	m_charAnimeFrame(),
	m_charDirNo(),
	m_effectAnimeNo(),
	m_effectAnimeFrame(),
	m_effectDirNo(),
	m_shotSound(),
	m_bombSound(),
	m_count()
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
	m_pos.x = GetRand((float)Game::kScreenWidth);
	m_pos.y = {};
	m_vec.x = {};
	m_vec.y = kSpeed;

	m_frameCount = 0;
	m_shotFlag = true;
	m_charAnimeNo = {};
	m_charAnimeFrame = {};
	m_charDirNo = {};
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_shotSound = LoadSoundMem(kShotSound);
	m_bombSound = LoadSoundMem(kBombSound);

	m_count = 0;

	m_isExist = true;

	
}

void MobEnemies::update()
{
	// 敵が存在しなかった場合、ここで処理を終了する
	if (!m_isExist)return;
	
	m_charDirNo = 0;

	// モブエネミーの動きを止める
	if (m_pos.y >= kStopPosition)
	{
		// ショットフラグがtrueの場合、一回だけショットを発射する
		if (m_shotFlag == true)
		{
			PlaySoundMem(m_shotSound, DX_PLAYTYPE_BACK);
			m_pMain->createEnemyShot(m_pos);
			m_shotFlag = false;
		}
		
		m_vec.y = 0;

		// kStopTime/60秒後、再びモブエネミーを動かす
		if (m_vec.y == 0)m_frameCount++;
		if (m_frameCount >= kStopTime)
		{
			m_frameCount = kStopTime;
			m_vec.y = kSpeed;
		}
	}

	m_charAnimeFrame++;
	if (m_charAnimeFrame >= kMobEnemiesGraphicDivX * kCharAnimeChangeFrame)
	{
		m_charAnimeFrame = 0;
	}

	int tempCharAnimeNo = m_charAnimeFrame / kCharAnimeChangeFrame;
	m_charAnimeNo = m_charDirNo + tempCharAnimeNo;

	m_charDirNo = 0;

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
	if (!m_isExist)
	{

		return;
	}

	// モブエネミーの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.5, 0.0, m_handle[m_charAnimeNo], true);

	assert(m_charAnimeNo <= 12);
	assert(m_charAnimeNo >= 0);

	// デバッグ
#if false
	// モブエネミーの当たり判定の大きさ
	DrawCircle((int)m_pos.x, (int)m_pos.y, kMobEnemyHitCircleSize, GetColor(0, 255, 255), FALSE);
#endif
}

void MobEnemies::effect()
{
	if (m_count == 0)
	{
		PlaySoundMem(m_bombSound, DX_PLAYTYPE_BACK);
		m_count = 1;
	}
	// エフェクトの表示が終わったらここで処理を終了する
	if (m_effectAnimeNo >= 49)return;

	m_effectAnimeFrame++;
	if (m_effectAnimeFrame >= kMobEnemiesEffectDivX * kEffectAnimeChangeFrame)
	{
		m_effectAnimeFrame = 0;
	}

	int tempEffectAnimeNo = m_effectAnimeFrame / kEffectAnimeChangeFrame;
	m_effectAnimeNo = m_effectDirNo + tempEffectAnimeNo;

	m_effectDirNo = 0;

	// エフェクトの表示(座標の中心に画像を表示する)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		2.0, 0.0, m_effect[m_effectAnimeNo], true);

}





