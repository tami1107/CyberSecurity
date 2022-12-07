#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "DefenseLineEffect.h"
#include "game.h"


namespace
{
	// エフェクトアニメーションの速度
	constexpr int kEffectAnimeChangeFrame = 8;
	// 防衛ラインの座標
	constexpr int kDefenseLinePosY = 500;
	
}

DefenseLineEffect::DefenseLineEffect() :
	m_pMain(nullptr),
	m_pos(),

	m_number(),
	m_animeNo(),
	m_animeFrame(),
	m_dirNo()
{
	for (auto& handle : m_effect)
	{
		handle = -1;
	}
}

DefenseLineEffect::~DefenseLineEffect()
{
}

void DefenseLineEffect::init()
{
	m_pos.x = 0;
	m_pos.y = 0;

	m_number = (Game::kScreenWidth / m_sizeX) + 1;

	m_animeNo = {};
	m_animeFrame = {};
	m_dirNo = {};
}

void DefenseLineEffect::update()
{
	m_animeFrame++;
	if (m_animeFrame >= kDefenseLineEffectDivX * kEffectAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kEffectAnimeChangeFrame;
	m_animeNo = m_dirNo + tempAnimeNo;

	m_dirNo = 0;
}



void DefenseLineEffect::draw()
{
	int num = 0;
	// 防衛ラインの表示(座標の中心に画像を表示する)
	for (int i = 0; i < m_number; i++)
	{
		num = m_sizeX * i;
		DrawGraph(0 + num, kDefenseLinePosY, m_effect[m_animeNo], true);
	}

	// デバッグ
#if true
	
#endif
}


