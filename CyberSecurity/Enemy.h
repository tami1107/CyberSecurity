#pragma once

#include "Vec2.h"
#include "EnemyRevShot.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// SceneMain��ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	// �G�l�~�[�̏�����
	void init();

	// ����
	void update();
	// �`��
	void draw();

	

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	SceneMain* m_pMain;


	int m_handle;
	// �V���b�g�̔����Ԋu
	int m_shotInterval;


	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	EnemyRevShot m_EnemyRevShot;
};