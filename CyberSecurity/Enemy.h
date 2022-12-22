#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:

	// �G�l�~�[�O���t�B�b�N������
	static constexpr int kEnemyGraphicDivX = 3;
	static constexpr int kEnemyGraphicDivY = 4;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;

	// �G�t�F�N�g�O���t�B�b�N
	static constexpr int kEnemyEffectDivX = 50;
	static constexpr int kEnemyEffectDivY = 1;
	static constexpr int kEnemyEffectDivNum = kEnemyEffectDivX * kEnemyEffectDivY;

	Enemy();
	virtual ~Enemy();

	// SceneMain��ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEffect(int index, int handle) { m_effect[index] = handle; }

	// �G�l�~�[�̏�����
	void init();

	// ����
	void update();
	// �`��
	void draw();

	// �G�t�F�N�g����
	void effect();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	SceneMain* m_pMain;

	// ���u�G�l�~�[�̃O���t�B�b�N
	int m_handle[kEnemyGraphicDivNum];
	int m_effect[kEnemyEffectDivNum];

	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �L�����N�^�[�̃A�j���[�V����
	int m_charAnimeNo;	// �\������ԍ�
	int m_charAnimeFrame;
	int m_charDirNo;

	// �G�t�F�N�g�̃A�j���[�V����
	int m_effectAnimeNo;	// �\������ԍ�
	int m_effectAnimeFrame;
	int m_effectDirNo;

	int m_shotSound;

	int m_bombSound;

	int m_count;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	
};