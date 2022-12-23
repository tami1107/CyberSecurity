#include <DxLib.h>
#include "SceneGameOver.h"
#include "SceneTitle.h"

namespace
{
	// 背景
	const char* const kBackGround = "data/背景青.png";

	// フェードインアウトのスピード
	constexpr int kFadeSpeed = 5;

	const char* const kText = "data/ゲームオーバー.png";


	const char* const kSound = "bgm/ゲームオーバーBGM.mp3";
}

void SceneGameOver::init()
{


	m_BackGround = LoadGraph(kBackGround);

	m_text = LoadGraph(kText);

	// フェードインフラグ
	m_fadeInFlag = true;

	// フェードアウトフラグ
	m_fadeOutFlag = false;

	m_fadeCount = 0;

	m_count = 0;

	m_BGM = LoadSoundMem(kSound);

	PlaySoundMem(m_BGM, DX_PLAYTYPE_BACK);

	m_isEnd = false;
}

SceneBase* SceneGameOver::update()
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

	if (m_count < 20)
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

			DeleteSoundMem(m_BGM);
			// 描画が終ったのでグラフィックをメモリ上から削除する
			DeleteGraph(m_BackGround);
			// Mainに切り替え
			return(new SceneTitle);
		}

	}


	return this;
}

void SceneGameOver::draw()
{
	// フェード
	SetDrawBright(m_fadeCount, m_fadeCount, m_fadeCount);
	// 背景の表示
	DrawGraph(0, 0, m_BackGround, true);

	DrawRotaGraph(400, 300, m_count * 0.1, 0, m_text, TRUE);

	// 文字列の描画
	DrawString(10, 0, "Zキー、または1ボタンでタイトルに戻る", 0xffffff);
}
