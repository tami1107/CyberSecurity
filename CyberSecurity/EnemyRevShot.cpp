#include "DxLib.h"
#include "EnemyRevShot.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// �V���b�g�X�s�[�h
	constexpr float kShotSpeed = 5.0f;
	// �����蔻��
	static constexpr float kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (�G�l�~�[�V���b�g�̉~�`�̓����蔻��̑傫��)

}

EnemyRevShot::EnemyRevShot() :
	m_handle(-1),// �V���b�g�̃O���t�B�b�N�n���h��
	m_rad(),// ���W�A��
	m_isExist(false),
	m_pos(),
	m_vec()
{
}

EnemyRevShot::~EnemyRevShot()
{
}

void EnemyRevShot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	// �e��������֔�΂�
	m_vec.y = kShotSpeed;
}

void EnemyRevShot::update()
{
	m_vec.x += cosf(m_rad) * kShotSpeed;
	m_pos.y += sinf(m_rad) * kShotSpeed;
	//m_vec *= kShotSpeed;

	// �e�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;

	//m_pos += m_vec;

	// �e����ʊO�ɏo���Ƃ����݂�����
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
	// �V���b�g���h�q���C���ɓ��������Ƃ��A���݂�����
	if (m_pos.y >= DefenseLineEffect::kDefenseLinePosY)
	{
		m_isExist = false;
	}
}
// �\��
void EnemyRevShot::draw()
{
	// �e�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist)return;

	DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.5, m_rad, m_handle, true);
	// �f�o�b�O
#if true
	// �V���b�g�̓����蔻��
	DrawCircle((float)m_pos.x, (float)m_pos.y, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}

void EnemyRevShot::setDir(float m_angle)
{
	m_rad = m_angle * DX_PI_F / 180.0f;
}
