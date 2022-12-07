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
	void setExist (bool isExist) { m_isExist = isExist; }


	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;

	// ���݃t���O
	bool m_isExist;

	// �v���C���[
	Player m_player;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
};