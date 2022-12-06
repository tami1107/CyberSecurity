#include <DxLib.h>
#include "MobEnemies.h"
#include "game.h"
#include "SceneMain.h"
#include <cassert>



namespace
{
	// X�����AY�����̈ړ����x
	constexpr float kSpeed = 2.0f;
	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 8;
	// �L�����N�^�[�A�j���[�V�����̑��x
	constexpr int kCharAnimeChangeFrame = 8;

	// �G�t�F�N�g�A�j���[�V�����̑��x
	constexpr int kEffectAnimeChangeFrame = 8;
	// ���u�G�l�~�[�̉~�`�̓����蔻��̑傫��
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

	// ���u�G�l�~�[�̓������~�߂�
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
	// ���u�G�l�~�[�̕\��(���W�̒��S�ɉ摜��\������)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0, m_handle[m_charAnimeNo], true);
	// �G�t�F�N�g�̕\��(���W�̒��S�ɉ摜��\������)
	/*DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.7, 0.0, m_effect[m_effectAnimeNo], true);*/

	assert(m_charAnimeNo <= 12);
	assert(m_charAnimeNo >= 0);

	// �f�o�b�O
#if true
	// ���u�G�l�~�[�̓����蔻��̑傫��
	DrawCircle((int)m_pos.x, (int)m_pos.y, kHitCircleSize, GetColor(0, 255, 255), FALSE);
#endif
}
