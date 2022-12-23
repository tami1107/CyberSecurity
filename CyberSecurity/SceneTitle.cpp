#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "game.h"
#include "SceneExplanation.h"

namespace
{
	// タイトルの項目数
	constexpr int kNumberOfItems = 3;
	// キーインターバル
	constexpr int kTInterval = 15;
	// テキスト位置
	constexpr int kTextPosition = 600;
	// テキストずらし
	constexpr int kTextSlide = 20;
	// 背景
	const char* const kBackGround = "data/背景タイトル.png";
	// カーソル
	const char* const kCursor = "data/ターゲット.png";
	// タイトルロゴ
	const char* const kTitleLogo = "data/タイトルロゴ.png";
	// フェードインアウトのスピード
	constexpr int kFadeSpeed = 5;

	const char* const kDecisionSound = "bgm/決定ボタンを押す.mp3";

	const char* const kCursorSound = "bgm/カーソル移動.mp3";

	const char* const kTitleSound = "bgm/タイトルBGM.wav";
}


// メニュー項目の表示に必要な構造体を用意する
typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
} MenuElement_t;

// メニュー項目要素を5つ作る
MenuElement_t MenuElement[kNumberOfItems] =
{
	{  (kTextPosition - kTextSlide), 150, "ゲームスタート" },
	{ kTextPosition, 250, "ヘルプ" },
	{ kTextPosition, 350, "ゲーム終了" },
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

	// フェードインフラグ
	m_fadeInFlag = true;

	// フェードアウトフラグ
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


	// 計算フェーズ 
	m_Interval--;
	if (m_Interval < 0) m_Interval = 0;

	

	if (m_Interval <= 0)
	{
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
		if (m_count == 0)
		{
			// 計算フェーズ 
			if (padState & PAD_INPUT_DOWN) { // 下キーが押された瞬間だけ処理

				m_selectNum = (m_selectNum + 1) % kNumberOfItems; // 現在の選択項目を一つ下にずらす(ループする)
				
				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
			if (padState & PAD_INPUT_UP) { // 上キーが押された瞬間だけ処理

				m_selectNum = (m_selectNum + (kNumberOfItems - 1)) % kNumberOfItems; // 現在の選択項目を一つ上にずらす(逆ループする)
		
				PlaySoundMem(m_cursorSound, DX_PLAYTYPE_BACK);
				m_Interval = kTInterval;
			}
		}
		// メニュー項目数である5個ループ処理
		for (int i = 0; i < kNumberOfItems; i++) 
		{              
			// 今処理しているのが、選択番号と同じ要素なら
			if (i == m_selectNum) 
			{          
				MenuElement[i].x = (kTextPosition - kTextSlide);
			}
			// 今処理しているのが、選択番号以外なら
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
					// サウンドハンドルの削除
					DeleteSoundMem(m_bgm1);
					return(new SceneMain);

				}
				if (m_selectNum == 1)
				{
					// サウンドハンドルの削除
					DeleteSoundMem(m_bgm1);
					return(new SceneExplanation);

				}
			}
			if (m_fadeOutFlag == false)
			{

				if (padState & PAD_INPUT_1)
				{
					// 読みこんだ音をノーマル再生します(『PlaySoundMem』関数使用)
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
						// ゲーム終了
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

	// 背景の表示
	DrawGraph(0, 0, m_BackGround, TRUE);
	// タイトルロゴの表示
	DrawGraph(100, 200, m_TitleLogo, true);


	// メニュー項目を描画
	for (int i = 0; i < kNumberOfItems; i++)
	{
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 
		GetColor(255, 255, 255), MenuElement[i].name);
	}


	// 読みこんだグラフィックを回転描画
	DrawRotaGraph(550, m_CursorY, 0.8f, m_angle + DX_PI / 2 / 2, m_Cursor, TRUE);

	// 文字列の描画
	DrawString(10, 0, "十字キー、または十字ボタンの上下で移動　Zキー、または1ボタンで決定", 0xffffff);
}