#include <DxLib.h>
#include "SceneGameClear.h"
#include "SceneTitle.h"

namespace
{
	// �w�i
	const char* const kBackGround = "data/�w�i��.png";

	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	const char* const kText = "data/�Q�[���N���A.png";


	const char* const kSound = "bgm/�N���ABGM.mp3";
}

void SceneGameClear::init()
{
	

	m_BackGround = LoadGraph(kBackGround);

	m_text = LoadGraph(kText);

	// �t�F�[�h�C���t���O
	m_fadeInFlag = true;

	// �t�F�[�h�A�E�g�t���O
	m_fadeOutFlag = false;

	m_fadeCount = 0;

	m_count = 0;

	m_BGM = LoadSoundMem(kSound);

	PlaySoundMem(m_BGM, DX_PLAYTYPE_BACK);

	m_isEnd = false;
}

SceneBase* SceneGameClear::update()
{
	if (m_fadeInFlag == true)
	{

		m_fadeCount += kFadeSpeed;
		if (m_fadeCount >= 255)
		{
			m_fadeCount = 255;
			m_fadeInFlag = false;
		}

	}
	if (m_fadeOutFlag == true)
	{
		m_fadeCount -= kFadeSpeed;
		if (m_fadeCount <= 0)
		{
			m_fadeCount = 0;
			m_fadeOutFlag = false;
		}
	}

	
	if(m_count < 20)
	{
		m_count++;
	}

	

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeInFlag == false)
	{
		if (padState & PAD_INPUT_1)
		{
			m_fadeOutFlag = true;
		}
	}

	if (m_fadeOutFlag == true)
	{
		if (m_fadeCount <= 10)
		{
			
			// �`�悪�I�����̂ŃO���t�B�b�N���������ォ��폜����
			DeleteGraph(m_BackGround);
			DeleteSoundMem(m_BGM);
			// Main�ɐ؂�ւ�
			return(new SceneTitle);
		}

	}
	return this;
}

void SceneGameClear::draw()
{
	// �t�F�[�h
	SetDrawBright(m_fadeCount, m_fadeCount, m_fadeCount);
	// �w�i�̕\��
	DrawGraph(0, 0, m_BackGround, true);

	DrawRotaGraph(400, 300, m_count * 0.1, 0, m_text, TRUE);
	
	// ������̕`��
	DrawString(10, 0, "Z�L�[�A�܂���1�{�^���Ń^�C�g���ɖ߂�", 0xffffff);
}
