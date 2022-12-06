#include "DxLib.h"
#include "EnemyRevShot.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// �V���b�g�X�s�[�h
	constexpr float kShotSpeed = 5.0f;
	// �����蔻��
	static constexpr int  kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (�G�l�~�[�V���b�g�̉~�`�̓����蔻��̑傫��)

}

EnemyRevShot::EnemyRevShot() :
	m_handle(-1),// �V���b�g�̃O���t�B�b�N�n���h��
	m_GraphicSizeX(),// �V���b�g�̃O���t�B�b�N�T�C�YX
	m_GraphicSizeY(),// �V���b�g�̃O���t�B�b�N�T�C�YY
	m_CenterPosX(),// �V���b�g�̒��S�ʒu�Ƃ�
	m_CenterPosY(),
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
	
	// �V���b�g�̃O���t�B�b�N�T�C�Y�����߂�
	GetGraphSize(m_handle, &m_GraphicSizeX, &m_GraphicSizeY);

	// �V���b�g�̒��S�ʒu
	m_CenterPosX = m_pos.x + (m_GraphicSizeX / 2);
	m_CenterPosY = m_pos.y + (m_GraphicSizeY / 2);



	m_pos.x += cosf(m_rad) * kShotSpeed;
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
}
// �\��
void EnemyRevShot::draw()
{
	// �e�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist)return;

	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);

	DrawRotaGraph(m_CenterPosX, m_CenterPosY, 1.0, m_rad, m_handle, true);
	// �f�o�b�O
#if true

	// �V���b�g�̓����蔻��
	DrawCircle((int)m_CenterPosX, (int)m_CenterPosY, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}

void EnemyRevShot::setDir(float m_angle)
{
	m_rad = m_angle * DX_PI_F / 180.0f;

	

}
