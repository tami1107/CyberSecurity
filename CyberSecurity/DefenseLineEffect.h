#pragma once

#include "Vec2.h"

class SceneMain;

class DefenseLineEffect
{
public:
	// �h�q���C���̃G�t�F�N�g�O���t�B�b�N
	static constexpr int kDefenseLineEffectDivX = 4;
	static constexpr int kDefenseLineEffectDivY = 1;
	static constexpr int kDefenseLineEffectDivNum = kDefenseLineEffectDivX * kDefenseLineEffectDivY;

public:
	DefenseLineEffect();
	virtual ~DefenseLineEffect();

	void setEffect(int index, int handle) { m_effect[index] = handle; }

	void setSizeX(int size) { m_sizeX = size; }

	// SceneMain��ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }


	// ������
	void init();

	// ����
	void update();

	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }
private:
	SceneMain* m_pMain;

	int m_effect[kDefenseLineEffectDivNum];

	int m_sizeX;

	// �h�q���C���̐�
	int m_number;

	// �h�q���C���̃G�t�F�N�g�̃A�j���[�V����
	int m_animeNo;	// �\������ԍ�
	int m_animeFrame;
	int m_dirNo;


	// �\���ʒu
	Vec2 m_pos;
};

