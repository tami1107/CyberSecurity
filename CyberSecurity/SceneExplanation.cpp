#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneExplanation.h"
#include "game.h"

namespace
{
	// タイトルの項目数
	constexpr int kNumberOfItems = 4;
	// キーインターバル
	constexpr int kTInterval = 15;
	// テキスト位置
	constexpr int kTextPosition = 600;
	// テキストずらし
	constexpr int kTextSlide = 20;
	// 背景
	const char* const kBackGround1 = "data/画像1.png";
	const char* const kBackGround2 = "data/画像2.png";
	const char* const kBackGround3 = "data/画像3.png";
	const char* const kBackGround4 = "data/画像4.png";

	// フェードインアウトのスピード
	constexpr int kFadeSpeed = 5;

	const char* const kDecisionSound = "bgm/決定ボタンを押す.mp3";

	const char* const kCursorSound = "bgm/カーソル移動.mp3";

	const char* const kTitleSound = "bgm/タイトルBGM.wav";
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

	// フェードインフラグ
	m_fadeInFlag = true;

	// フェードアウトフラグ
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


	// 計算フェーズ 
	m_Interval--;
	if (m_Interval < 0) m_Interval = 0;



	if (m_Interval <= 0)
	{
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (m_count == 0)
		{
			// 計算フェーズ 
			if (padState & PAD_INPUT_RIGHT) { // 下キーが押された瞬間だけ処理

				m_selectNum = (m_selectNum + 1) % kNumberOfItems; // 現在の選択項目を一つ下にずらす(ループする)

				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
			if (padState & PAD_INPUT_LEFT) { // 上キーが押された瞬間だけ処理

				m_selectNum = (m_selectNum + (kNumberOfItems - 1)) % kNumberOfItems; // 現在の選択項目を一つ上にずらす(逆ループする)

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
					// サウンドハンドルの削除
					DeleteSoundMem(m_bgm1);
					return(new SceneTitle);

				}
			}
			if (m_fadeOutFlag == false)
			{

				if (padState & PAD_INPUT_1)
				{
					// 読みこんだ音をノーマル再生します(『PlaySoundMem』関数使用)
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

	int Cr = GetColor(255, 255, 255);    // 白色の値を取得

	DrawGraph(0, 0, m_BackGround[m_selectNum], TRUE);

	// 文字列の描画
	DrawString(10, 0, "十字キー、または十字ボタンの左右で移動", Cr);
}