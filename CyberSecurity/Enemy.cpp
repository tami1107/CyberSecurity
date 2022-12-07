#include <DxLib.h>
#include "SceneMain.h"
#include "game.h"


namespace 
{
	// X�����AY�����̍ő呬�x
	constexpr float kSpeedMax = 5.0f;
	constexpr float kAcc = 0.4f;
	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 4;
	// �G�l�~�[�V���b�g�̉~�`�̓����蔻��̑傫��
	static constexpr int kShotCircleSize = SceneMain::kEnemyHitCircleSize;
}


Enemy::Enemy():
	m_pMain(nullptr),
	m_handle(-1),
	m_shotInterval(0),
	m_pos(),
	m_vec()
{
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
	
	m_shotInterval = kShotInterval;
}

void Enemy::update()
{
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	//if ((m_pMain) && (m_shotInterval <= 0))
	//{
	//	
	//	m_pMain->createEnemyShot(m_pos);
	//	
	//
	//	m_shotInterval = kShotInterval;
	//}

	if ((m_pMain) && (m_shotInterval <= 0))
	{

		m_pMain->createEnemyShot(m_pos);
		
		m_shotInterval = kShotInterval;
	}

	// enemy���E��ʒ[�ɍs���Ƃ����ɐi�܂���
	if (m_pos.x >= Game::kScreenWidth - kShotCircleSize)
	{
		m_vec.x -= kAcc;
		if (m_vec.x < -kSpeedMax)	m_vec.x = -kSpeedMax;
	}
	// enemy������ʒ[�ɍs���Ƃ��E�ɐi�܂���
	if (m_pos.x <= 0)
	{
		m_vec.x += kAcc;
		if (m_vec.x < -kSpeedMax)	m_vec.x = -kSpeedMax;
	}

	

	m_pos += m_vec;
}

void Enemy::draw()
{
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawTurnGraphF(m_pos.x, m_pos.y, m_handle, true);
#if true
	// �G�l�~�[�̓����蔻��̑傫��
	DrawCircle((int)m_pos.x,(int)m_pos.y, kShotCircleSize, GetColor(255, 255, 255), FALSE);
#endif
}


