#pragma once

#include "Vec2.h"

class SceneMain;

class MobEnemies
{
public:
	// �萔��`

	// �v���C���[�O���t�B�b�N������
	static constexpr int kMobEnemiesGraphicDivX = 3;
	static constexpr int kMobEnemiesGraphicDivY = 4;
	static constexpr int kMobEnemiesGraphicDivNum = kMobEnemiesGraphicDivX * kMobEnemiesGraphicDivY;

	// �G�t�F�N�g�O���t�B�b�N
	static constexpr int kMobEnemiesEffectDivX = 4;
	static constexpr int kMobEnemiesEffectDivY = 4;
	static constexpr int kMobEnemiesEffectDivNum = kMobEnemiesEffectDivX * kMobEnemiesEffectDivY;

	MobEnemies();
	virtual ~MobEnemies();

	// SceneMain��ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// �O���t�B�b�N�f�[�^�ݒ�

	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEffect(int index, int handle) { m_effect[index] = handle; }


	// �v���C���[�̏�����
	void init();

	// ����
	void update();

	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:

	SceneMain* m_pMain;
	// ���u�G�l�~�[�̃O���t�B�b�N
	int m_handle[kMobEnemiesGraphicDivNum];
	int m_effect[kMobEnemiesEffectDivNum];

	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �t���[�������J�E���g����
	int m_count;

	// �L�����N�^�[�̃A�j���[�V����
	int m_charAnimeNo;	// �\������ԍ�
	int m_charAnimeFrame;
	int m_charDirNo;

	// �G�t�F�N�g�̃A�j���[�V����
	int m_effectAnimeNo;	// �\������ԍ�
	int m_effectAnimeFrame;
	int m_effectDirNo;
	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
};