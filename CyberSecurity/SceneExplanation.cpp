#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneExplanation.h"
#include "game.h"

namespace
{
	// �^�C�g���̍��ڐ�
	constexpr int kNumberOfItems = 4;
	// �L�[�C���^�[�o��
	constexpr int kTInterval = 15;
	// �e�L�X�g�ʒu
	constexpr int kTextPosition = 600;
	// �e�L�X�g���炵
	constexpr int kTextSlide = 20;
	// �w�i
	const char* const kBackGround1 = "data/�摜1.png";
	const char* const kBackGround2 = "data/�摜2.png";
	const char* const kBackGround3 = "data/�摜3.png";
	const char* const kBackGround4 = "data/�摜4.png";

	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	const char* const kDecisionSound = "bgm/����{�^��������.mp3";

	const char* const kCursorSound = "bgm/�J�[�\���ړ�.mp3";

	const char* const kTitleSound = "bgm/�^�C�g��BGM.wav";
}



SceneExplanation::SceneExplanation()
{
}

void SceneExplanation::init()
{
	m_selectNum = 0;

	m_Interval = kTInterval;

	m_isEnd = false;

	m_BackGround[0] = LoadGraph(kBackGround1);

	m_BackGround[1] = LoadGraph(kBackGround2);

	m_BackGround[2] = LoadGraph(kBackGround3);

	m_BackGround[3] = LoadGraph(kBackGround4);

	

	m_fadeCount = 0;

	m_decisionSound = LoadSoundMem(kDecisionSound);

	m_cursorSound = LoadSoundMem(kCursorSound);

	m_bgm1 = LoadSoundMem(kTitleSound);

	PlaySoundMem(m_bgm1, DX_PLAYTYPE_BACK);


	m_count = 0;

	// �t�F�[�h�C���t���O
	m_fadeInFlag = true;

	// �t�F�[�h�A�E�g�t���O
	m_fadeOutFlag = false;
}

SceneBase* SceneExplanation::update()
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


	// �v�Z�t�F�[�Y 
	m_Interval--;
	if (m_Interval < 0) m_Interval = 0;



	if (m_Interval <= 0)
	{
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (m_count == 0)
		{
			// �v�Z�t�F�[�Y 
			if (padState & PAD_INPUT_RIGHT) { // ���L�[�������ꂽ�u�Ԃ�������

				m_selectNum = (m_selectNum + 1) % kNumberOfItems; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)

				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
			if (padState & PAD_INPUT_LEFT) { // ��L�[�������ꂽ�u�Ԃ�������

				m_selectNum = (m_selectNum + (kNumberOfItems - 1)) % kNumberOfItems; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)

				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
		}


		if (m_fadeInFlag == false)
		{

			if (m_fadeCount == 0)
			{
				if (m_selectNum == 3)
				{
					// �T�E���h�n���h���̍폜
					DeleteSoundMem(m_bgm1);
					return(new SceneTitle);

				}
			}
			if (m_fadeOutFlag == false)
			{

				if (padState & PAD_INPUT_1)
				{
					// �ǂ݂��񂾉����m�[�}���Đ����܂�(�wPlaySoundMem�x�֐��g�p)
					PlaySoundMem(m_decisionSound, DX_PLAYTYPE_BACK);
					if (m_selectNum == 3)
					{
						m_fadeOutFlag = true;
						m_count = 1;
					}
				}
			}
		}
	}



	return this;
}

void SceneExplanation::draw()
{
	//SetDrawBright(255, 255, 255);
	SetDrawBright(m_fadeCount, m_fadeCount, m_fadeCount);

	int Cr = GetColor(255, 255, 255);    // ���F�̒l���擾

	DrawGraph(0, 0, m_BackGround[m_selectNum], TRUE);

	// ������̕`��
	DrawString(10, 0, "�\���L�[�A�܂��͏\���{�^���̍��E�ňړ�", Cr);
}