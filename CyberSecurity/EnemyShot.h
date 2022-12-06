#pragma once

#include "Vec2.h"
#include "SceneBase.h"
#include "Player.h"

class EnemyShot
{
public:
	EnemyShot();
	virtual ~EnemyShot();

	// �O���t�B�b�N�𓾂�
	void setHandle(int handle) { m_handle = handle; }

	void setShotPos(Vec2 ShotPos) { m_pos = ShotPos; }

	// ����
	void start(Vec2 pos);

	// �X�V
	void update();
	// �\��
	void draw();

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// �e���v���C���[�ɓ����������ǂ���
	virtual bool CheckHit();

	// �G�l�~�[�̃O���t�B�b�N�T�C�Y
	void setPlayerGraphicX(int PlayerGraphicX) { m_PlayerGraphicX = PlayerGraphicX; }
	void setPlayerGraphicY(int PlayerGraphicY) { m_PlayerGraphicY = PlayerGraphicY; }

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;

	// �V���b�g�̃O���t�B�b�N�T�C�Y
	int m_GraphicSizeX;
	int m_GraphicSizeY;

	// �V���b�g�̒��S���W
	float m_CenterPosX;
	float m_CenterPosY;

	// �G�l�~�[�̃O���t�B�b�N�T�C�Y
	int m_PlayerGraphicX;
	int m_PlayerGraphicY;

	// ���݃t���O
	bool m_isExist;

	// �v���C���[
	Player m_player;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
};