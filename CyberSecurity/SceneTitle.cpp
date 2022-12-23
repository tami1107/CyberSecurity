#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "game.h"
#include "SceneExplanation.h"

namespace
{
	// �^�C�g���̍��ڐ�
	constexpr int kNumberOfItems = 3;
	// �L�[�C���^�[�o��
	constexpr int kTInterval = 15;
	// �e�L�X�g�ʒu
	constexpr int kTextPosition = 600;
	// �e�L�X�g���炵
	constexpr int kTextSlide = 20;
	// �w�i
	const char* const kBackGround = "data/�w�i�^�C�g��.png";
	// �J�[�\��
	const char* const kCursor = "data/�^�[�Q�b�g.png";
	// �^�C�g�����S
	const char* const kTitleLogo = "data/�^�C�g�����S.png";
	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	const char* const kDecisionSound = "bgm/����{�^��������.mp3";

	const char* const kCursorSound = "bgm/�J�[�\���ړ�.mp3";

	const char* const kTitleSound = "bgm/�^�C�g��BGM.wav";
}


// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
} MenuElement_t;

// ���j���[���ڗv�f��5���
MenuElement_t MenuElement[kNumberOfItems] =
{
	{  (kTextPosition - kTextSlide), 150, "�Q�[���X�^�[�g" },
	{ kTextPosition, 250, "�w���v" },
	{ kTextPosition, 350, "�Q�[���I��" },
};

SceneTitle::SceneTitle()
{
}

void SceneTitle::init()
{
	m_selectNum = 0;

	m_Interval = kTInterval;

	m_isEnd = false;

	m_BackGround = LoadGraph(kBackGround);

	m_Cursor = LoadGraph(kCursor);

	m_TitleLogo = LoadGraph(kTitleLogo);

	m_CursorY = 0;

	m_fadeCount = 0;

	m_decisionSound = LoadSoundMem(kDecisionSound);

	m_cursorSound = LoadSoundMem(kCursorSound);

	m_bgm1 = LoadSoundMem(kTitleSound);

	PlaySoundMem(m_bgm1, DX_PLAYTYPE_BACK);

	m_angle = 0;

	m_count = 0;

	// �t�F�[�h�C���t���O
	m_fadeInFlag = true;

	// �t�F�[�h�A�E�g�t���O
	m_fadeOutFlag = false;
}

SceneBase* SceneTitle::update()
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
			if (padState & PAD_INPUT_DOWN) { // ���L�[�������ꂽ�u�Ԃ�������

				m_selectNum = (m_selectNum + 1) % kNumberOfItems; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
				
				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
			if (padState & PAD_INPUT_UP) { // ��L�[�������ꂽ�u�Ԃ�������

				m_selectNum = (m_selectNum + (kNumberOfItems - 1)) % kNumberOfItems; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
		
				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
		}
		// ���j���[���ڐ��ł���5���[�v����
		for (int i = 0; i < kNumberOfItems; i++) 
		{              
			// ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			if (i == m_selectNum) 
			{          
				MenuElement[i].x = (kTextPosition - kTextSlide);
			}
			// ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
			else
			{                       
				MenuElement[i].x = kTextPosition;
			}
		}
		
		if (m_fadeInFlag == false)
		{

			if (m_fadeCount == 0)
			{
				if (m_selectNum == 0)
				{
					// �T�E���h�n���h���̍폜
					DeleteSoundMem(m_bgm1);
					return(new SceneMain);

				}
				if (m_selectNum == 1)
				{
					// �T�E���h�n���h���̍폜
					DeleteSoundMem(m_bgm1);
					return(new SceneExplanation);

				}
			}
			if (m_fadeOutFlag == false)
			{

				if (padState & PAD_INPUT_1)
				{
					// �ǂ݂��񂾉����m�[�}���Đ����܂�(�wPlaySoundMem�x�֐��g�p)
					PlaySoundMem(m_decisionSound, DX_PLAYTYPE_BACK);
					if (m_selectNum == 0)
					{
						m_fadeOutFlag = true;
						m_count = 1;
					}
					if (m_selectNum == 1)
					{
						m_fadeOutFlag = true;
						m_count = 1;
					}
					if (m_selectNum == 2)
					{
						// �Q�[���I��
						DxLib_End();
					}
				}
			}
		}
	}


	switch (m_selectNum)
	{
	case 0:
		m_CursorY = 155;
		break;

	case 1:
		m_CursorY = 255;
		break;

	case 2:
		m_CursorY = 355;
		break;
	default:
		m_CursorY = 155;
		break;
	}

	m_angle++;

	if (m_angle >= 359)
	{
		m_angle = 0;
	}


	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeCount, m_fadeCount, m_fadeCount);

	// �w�i�̕\��
	DrawGraph(0, 0, m_BackGround, TRUE);
	// �^�C�g�����S�̕\��
	DrawGraph(100, 200, m_TitleLogo, true);


	// ���j���[���ڂ�`��
	for (int i = 0; i < kNumberOfItems; i++)
	{
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 
		GetColor(255, 255, 255), MenuElement[i].name);
	}


	// �ǂ݂��񂾃O���t�B�b�N����]�`��
	DrawRotaGraph(550, m_CursorY, 0.8f, m_angle + DX_PI / 2 / 2, m_Cursor, TRUE);

	// ������̕`��
	DrawString(10, 0, "�\���L�[�A�܂��͏\���{�^���̏㉺�ňړ��@Z�L�[�A�܂���1�{�^���Ō���", 0xffffff);
}