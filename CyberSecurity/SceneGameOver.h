

#pragma once

#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver()
	{
		m_isEnd = false;
	}
	virtual ~SceneGameOver() {}


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	
	int m_BackGround;

	// フェードインフラグ
	bool m_fadeInFlag;

	// フェードアウトフラグ
	bool m_fadeOutFlag;

	int m_fadeCount;

	int m_text;

	int m_count;

	int m_BGM;

	bool m_isEnd;
};

