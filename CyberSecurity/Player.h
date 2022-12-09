#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	// �萔��`

	// �v���C���[�O���t�B�b�N������
	static constexpr int kPlayerGraphicDivX = 3;
	static constexpr int kPlayerGraphicDivY = 5;
	static constexpr int kPlayerGraphicDivNum = kPlayerGraphicDivX * kPlayerGraphicDivY;

	// �G���W���O���t�B�b�N������
	static constexpr int kPlayerEffectDivX = 4;
	static constexpr int kPlayerEffectDivY = 4;
	static constexpr int kPlayerEffectDivNum = kPlayerEffectDivX * kPlayerEffectDivY;

	// �ő吔
	static constexpr int kObjectMax = 128;

public:
	Player();
	virtual ~Player();

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
	// �v���C���[�̃O���t�B�b�N
	int m_handle[kPlayerGraphicDivNum] ;
	int m_effect[kPlayerEffectDivNum] ;

	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �L�����N�^�[�̃A�j���[�V����
	int m_charAnimeNo;	// �\������ԍ�

	// �G�t�F�N�g�̃A�j���[�V����
	int m_effectAnimeNo;	// �\������ԍ�
	int m_effectAnimeFrame;
	int m_effectDirNo;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
};