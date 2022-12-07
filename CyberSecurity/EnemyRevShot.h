#pragma once

#include "Vec2.h"
#include "SceneBase.h"


class EnemyRevShot
{
public:
	EnemyRevShot();
	virtual ~EnemyRevShot();

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

	// ���ł����������w�肷��(��������0�x�Ƃ��Ď��v���̊p�x���w�肷��)
	void setDir(float angle);

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;

	// ���W�A��
	float m_rad;

	// ���݃t���O
	bool m_isExist;

	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
};
