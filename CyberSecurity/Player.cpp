#include "DxLib.h"
#include "game.h"
#include "Player.h"
#include "SceneMain.h"


namespace 
{
	// �v���C���[�̒ᑬ��
	constexpr float  kSlowSpeed = 2.0f;
	// X�����AY�����̍ő呬�x
	constexpr float kSpeed = 5.0f;
	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 8;
	// �G�t�F�N�g�A�j���[�V�����̑��x
	constexpr int kEffectAnimeChangeFrame = 8;
	// �v���C���[�̉~�`�̓����蔻��̑傫��
	static constexpr int kHitCircleSize = SceneMain::kPlayerHitCircleSize;	
}

Player::Player() :
	m_pMain(nullptr),
	m_shotInterval(0),
	m_pos(),
	m_vec(),
	m_charAnimeNo(),
	m_effectAnimeNo(),
	m_effectAnimeFrame(),
	m_effectDirNo()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	for (auto& handle : m_effect)
	{
		handle = -1;
	}
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_charAnimeNo = 1;
	m_effectAnimeNo = {};
	m_effectAnimeFrame = {};
	m_effectDirNo = {};

	m_shotInterval = kShotInterval;
}

void Player::update()
{
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_charAnimeNo = 1;
	m_effectDirNo = 8;

	if (padState & PAD_INPUT_UP)
	{
		m_effectDirNo = 12;
		// 3�{�^���������Ă����瑬�x��������
		if (padState & PAD_INPUT_3)m_pos.y -= (kSpeed - kSlowSpeed);
		else m_pos.y -= kSpeed;
		
	}
	if (padState & PAD_INPUT_DOWN)
	{
		m_effectDirNo = 4;
		// 3�{�^���������Ă����瑬�x��������
		if (padState & PAD_INPUT_3)m_pos.y += (kSpeed - kSlowSpeed);
		else m_pos.y += kSpeed;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		// 3�{�^���������Ă����瑬�x��������
		if (padState & PAD_INPUT_3)m_pos.x -= (kSpeed - kSlowSpeed);
		else m_pos.x -= kSpeed;
		// 0�Ԃ̉摜��\������
		m_charAnimeNo = 0;
	}
	if (padState & PAD_INPUT_RIGHT)
	{	// 3�{�^���������Ă����瑬�x��������
		if (padState & PAD_INPUT_3)m_pos.x += (kSpeed - kSlowSpeed);
		else m_pos.x += kSpeed;
		// 2�Ԃ̉摜��\������
		m_charAnimeNo = 2;
	}
	if ((padState & PAD_INPUT_LEFT)&&(padState & PAD_INPUT_RIGHT)) m_charAnimeNo = 1;// 1�Ԃ̉摜��\������
	if (padState & PAD_INPUT_3)m_effectDirNo = 0;

	// �L�[���͏���
	if (padState & PAD_INPUT_1)
	{
		if ((m_pMain) && (m_shotInterval <= 0))
		{
			m_pMain->createShot(m_pos);
			m_shotInterval = kShotInterval;
		}
	}

	m_effectAnimeFrame++;
	if (m_effectAnimeFrame >= kPlayerEffectDivX * kEffectAnimeChangeFrame)
	{
		m_effectAnimeFrame = 0;
	}



	int tempAnimeNo = m_effectAnimeFrame / kEffectAnimeChangeFrame;
	m_effectAnimeNo = m_effectDirNo + tempAnimeNo;

	m_effectDirNo = 0;


	m_pos += m_vec;
}

void Player::draw()
{
	// �v���C���[�̕\��(���W�̒��S�ɉ摜��\������)
	//DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
	//	0.7, 0.0, m_handle[m_charAnimeNo], true);
	// �v���C���[�̕\��(���W�̒��S�ɉ摜��\������)
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		2.0, 0.0, m_effect[m_effectAnimeNo], true);
#if true
	// �v���C���[�̓����蔻��̑傫��
	DrawCircle((int)m_pos.x, (int)m_pos.y, kHitCircleSize, GetColor(0, 255, 255), FALSE);
#endif
}