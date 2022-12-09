#include <DxLib.h>
#include "SceneGameClear.h"
#include "SceneTitle.h"



void SceneGameClear::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

SceneBase* SceneGameClear::update()
{
	// �����̈ړ�
	m_textPosY += m_textVecY;
	if (m_textPosY < 0)
	{
		m_textPosY = 0;
		m_textVecY = 4;
	}
	if (m_textPosY > 200)
	{
		m_textPosY = 200;
		m_textVecY = -4;
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		// Main�ɐ؂�ւ�
		return(new SceneTitle);
	}

	return this;
}

void SceneGameClear::draw()
{
	DrawString(0, m_textPosY, "GameClear���", GetColor(255, 255, 255));
}
