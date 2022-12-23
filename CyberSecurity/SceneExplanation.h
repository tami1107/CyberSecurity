#pragma once
#include "SceneBase.h"

class SceneExplanation : public SceneBase
{
public:
	SceneExplanation();

	virtual ~SceneExplanation() {}


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	int m_selectNum;

	int m_Interval;

	int m_BackGround[4];


	int m_fadeCount;

	int m_angle;

	int m_count;

	// �T�E���h
	int m_decisionSound;

	int m_cursorSound;

	int m_bgm1;


	// �t�F�[�h�C���t���O
	bool m_fadeInFlag;

	// �t�F�[�h�A�E�g�t���O
	bool m_fadeOutFlag;

	bool m_isEnd;
};
