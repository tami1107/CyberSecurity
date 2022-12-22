#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "game.h"

namespace
{
	// モブエネミー撃退ライン
	constexpr int kMobEnemiesRepelLine = 20;

	// プレイヤーのHP
	constexpr int kPlayerHP = 3;

	// エネミーのHP
	constexpr int kEnemyHP = 100;

	// 防衛ラインの耐久値
	constexpr int kDefenseLinePoint = 3;

	// 背景１
	const char* const kBackGround1 = "data/BackGround1.png";

	// 背景２
	const char* const kBackGround2 = "data/BackGround2.png";

	// ボード
	const char* const kBoard = "data/Board.png";

	// ボード
	const char* const kBossText = "data/ボスロゴ.png";

	// HPバーの長さ
	constexpr int kHPwidth = Game::kScreenWidth - 80;

	// フェードインアウトのスピード
	constexpr int kFadeSpeed = 5;

	const char* const kPlayerDamageSound = "bgm/プレイヤーダメージ.wav";

	const char* const kAlarmSound = "bgm/アラーム.mp3";

	const char* const kEnemyDamageSound = "bgm/エネミーダメージ.wav";

	const char* const kDefenseLineSound = "bgm/防衛ライン音.wav";

	const char* const kDefenseLineSound2 = "bgm/警告音.mp3";

	const char* const kBgm1 = "bgm/モブエネミーBGM.wav";

	const char* const kBgm2 = "bgm/ボスエネミーBGM.mp3";
}


SceneMain::SceneMain() :
	// グラフィック
	m_hShotGraphic(-1),		// ショットのグラフィック
	m_hEnemyShotGraphic(-1),// エネミーのショットのグラフィック
	m_hEnemyRevShotGraphic(-1),	// エネミーの回転ショットのグラフィック
	m_hBackGround1(-1), // 背景のグラフィック
	m_hBackGround2(-1),

	// すべてのモブエネミーを倒したかどうか
	m_allMobEnemiesKill(false),

	// モブエネミーを倒した数
	m_MobKillCount(0),

	// ショットの角度更新
	m_angle(10),

	// カウンター
	m_hCount(0),

	// 防衛ラインのカウント
	m_DefenseLineCount(kDefenseLinePoint),

	// プレイヤーHP
	m_playerHP(kPlayerHP),
	// エネミーのHP
	m_enemyHP(kEnemyHP),
	m_maxHP(kEnemyHP),

	// フレームカウント
	m_frameCount(0),

	// プレイヤーがダメージを受けたかどうかの判定
	m_playerDamageFlag(false),

	// フェードインフラグ
	m_fadeInFlag(true),
	// フェードアウトフラグ
	m_fadeOutFlag(false),
	// プレイヤーエフェクト
	m_playerEffect(false),
	// プレイヤーが倒されたかどうか
	m_playerKillFrag(false),
	// エネミーが倒されたかどうか
	m_enemyKillFrag(false),
	// エネミーが動くかどうかの判定
	m_enemyMove(false),
	// ボス戦に行くためのフラグ
	m_bossFlag(false),
	m_count(0),
	// 暗転
	m_ChangeFlag(false),
	m_fadeCount(0),

	m_textCount(0),

	m_bossText(-1),

	m_textStop(0),

	m_posX(0),

	m_playerDamageSound(),
	m_playerDamageSoundCount(0),
	// プレイヤーエフェクトカウンター
	m_playerEffectCount(0),
	m_alarm(),
	m_alarmflag(0),
	m_waitFlag(true),
	m_angleflag(false),
	m_enemyDamageSound(),
	m_DefenseLineSound(),
	m_DefenseLineSound2(),
	m_BGM(),
	m_BossBGM()
{
	// プレイヤーのグラフィック
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	// プレイヤーのエフェクト
	for (auto& handle : m_hPlayerEffect)
	{
		handle = -1;
	}
	// プレイヤーのエフェクト
	for (auto& handle : m_hPlayerEffect2)
	{
		handle = -1;
	}
	// エネミーのグラフィック
	for (auto& handle : m_hEnemyGraphic)
	{
		handle = -1;
	}
	// エネミーのエフェクト
	for (auto& handle : m_hEnemyEffect)
	{
		handle = -1;
	}
	// モブエネミー
	for (auto& handle : m_hMobEnemiesGraphic)
	{
		handle = -1;
	}
	// 防衛ラインのグラフィック
	for (auto& handle : m_hDefenseLineGreenGraphic)
	{
		handle = -1;
	}
	for (auto& handle : m_hDefenseLineYellowGraphic)
	{
		handle = -1;
	}
	for (auto& handle : m_hDefenseLineRedGraphic)
	{
		handle = -1;
	}
}

SceneMain::~SceneMain()
{
}

// 初期化
void SceneMain::init()
{
	//////////////////////////////////////////
	//				プレイヤー
	//////////////////////////////////////////

	// プレイヤーのグラフィックサイズを取得
	int playerW = {};
	int playerH = {};
	int playerG = LoadGraph(kPlayerGraphicFilename);
	GetGraphSize(playerG,&playerW, &playerH);

	// プレイヤーエフェクトのグラフィックサイズを取得
	int pEffectW = {};
	int pEffectH = {};
	int pEffectG = LoadGraph(kPlayerEffectFilename);
	GetGraphSize(pEffectG, &pEffectW, &pEffectH);

	// モブエネミーエフェクトのグラフィックサイズを取得
	int pEffect2W = {};
	int pEffect2H = {};
	int pEffect2G = LoadGraph(kMobEnemiesEffectFilename);
	GetGraphSize(pEffect2G, &pEffect2W, &pEffect2H);

	// m_hPlayerGraphicの中にプレイヤーの画像を入れる
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		playerW / Player::kPlayerGraphicDivX, playerH / Player::kPlayerGraphicDivY, m_hPlayerGraphic);

	// m_hPlayerEffectの中にプレイヤーの画像を入れる
	LoadDivGraph(kPlayerEffectFilename, Player::kPlayerEffectDivNum,
		Player::kPlayerEffectDivX, Player::kPlayerEffectDivY,
		pEffectW / Player::kPlayerEffectDivX, pEffectH / Player::kPlayerEffectDivY, m_hPlayerEffect);


	// m_hPlayerEffectの中にプレイヤーの画像を入れる
	LoadDivGraph(kMobEnemiesEffectFilename, Player::kEffectDivNum,
		Player::kEffectDivX, Player::kEffectDivY,
		pEffect2W / Player::kEffectDivX, pEffect2H / Player::kEffectDivY, m_hPlayerEffect2);


	m_player.setMain(this);


	// player.hにプレイヤーの画像を送る
	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}

	// player.hにプレイヤーエフェクトの画像を送る
	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setEffect(i, m_hPlayerEffect[i]);
	}

	// player.hにプレイヤーエフェクト2の画像を送る
	for (int i = 0; i < Player::kEffectDivNum; i++)
	{
		m_player.setEffect2(i, m_hPlayerEffect2[i]);
	}

	m_player.init();// m_playerのinit(初期設定)を行う
	

	//////////////////////////////////////////
	//				エネミー
	//////////////////////////////////////////
	// エネミーのグラフィックサイズを取得
	int EnemyW = {};
	int EnemyH = {};
	int EnemyG = LoadGraph(kMobEnemiesGraphicFilename);
	GetGraphSize(EnemyG, &EnemyW, &EnemyH);


	// エネミーエフェクトのグラフィックサイズを取得
	int eEffectW = {};
	int eEffectH = {};
	int eEffectG = LoadGraph(kMobEnemiesEffectFilename);
	GetGraphSize(eEffectG, &eEffectW, &eEffectH);

	// m_hEnemyGraphicの中にモブエネミーの画像を入れる
	LoadDivGraph(kMobEnemiesGraphicFilename, Enemy::kEnemyGraphicDivNum,
		Enemy::kEnemyGraphicDivX, Enemy::kEnemyGraphicDivY,
		EnemyW / Enemy::kEnemyGraphicDivX, EnemyH / Enemy::kEnemyGraphicDivY, m_hEnemyGraphic);

	// m_hMobEnemiesGraphicの中にモブエネミーのエフェクトを入れる
	LoadDivGraph(kMobEnemiesEffectFilename, Enemy::kEnemyEffectDivNum,
		Enemy::kEnemyEffectDivX, Enemy::kEnemyEffectDivY,
		eEffectW / Enemy::kEnemyEffectDivX, eEffectH / Enemy::kEnemyEffectDivY, m_hEnemyEffect);

	m_enemy.setMain(this);

	//  エネミーの画像を送る
	for (int i = 0; i < Enemy::kEnemyGraphicDivNum; i++)
	{
		m_enemy.setHandle(i, m_hEnemyGraphic[i]);
	}
	//  エネミーのエフェクトを送る
	for (int i = 0; i < Enemy::kEnemyEffectDivNum; i++)
	{
		m_enemy.setEffect(i, m_hEnemyEffect[i]);
	}
	m_enemy.init();// m_enemyのinit(初期設定)を行う


	//////////////////////////////////////////
	//				モブエネミー
	//////////////////////////////////////////


	// モブエネミーのグラフィックサイズを取得
	int mobEnemyW = {};
	int mobEnemyH = {};
	int mobEnemyG = LoadGraph(kMobEnemiesGraphicFilename);
	GetGraphSize(mobEnemyG, &mobEnemyW, &mobEnemyH);

	// モブエネミーエフェクトのグラフィックサイズを取得
	int mEffectW = {};
	int mEffectH = {};
	int mEffectG = LoadGraph(kMobEnemiesEffectFilename );
	GetGraphSize(mEffectG, &mEffectW, &mEffectH);


	// m_hMobEnemiesGraphicの中にモブエネミーの画像を入れる
	LoadDivGraph(kMobEnemiesGraphicFilename, MobEnemies::kMobEnemiesGraphicDivNum,
		MobEnemies::kMobEnemiesGraphicDivX, MobEnemies::kMobEnemiesGraphicDivY,
		mobEnemyW / MobEnemies::kMobEnemiesGraphicDivX, mobEnemyH / MobEnemies::kMobEnemiesGraphicDivY, m_hMobEnemiesGraphic);

	// m_hMobEnemiesGraphicの中にモブエネミーのエフェクトを入れる
	LoadDivGraph(kMobEnemiesEffectFilename, MobEnemies::kMobEnemiesEffectDivNum,
		MobEnemies::kMobEnemiesEffectDivX, MobEnemies::kMobEnemiesEffectDivY,
		mEffectW / MobEnemies::kMobEnemiesEffectDivX, mEffectH / MobEnemies::kMobEnemiesEffectDivY, m_hMobEnemiesEffect);

	for (auto& mobObject : m_mobEnemy)
	{
		mobObject.setMain(this);
	}

	//  m_hMobEnemies.hにモブエネミーの画像を送る
	for (int i = 0; i < MobEnemies::kMobEnemiesGraphicDivNum; i++)
	{
		for (auto& mobObject : m_mobEnemy)
		{
			mobObject.setHandle(i, m_hMobEnemiesGraphic[i]);
		}
	}

	//  m_hMobEnemies.hにモブエネミーのエフェクトを送る
	for (int i = 0; i < MobEnemies::kMobEnemiesEffectDivNum; i++)
	{
		for (auto& mobObject : m_mobEnemy)
		{
			mobObject.setEffect(i, m_hMobEnemiesEffect[i]);
		}
	}



	//////////////////////////////////////////
	//				ショット
	//////////////////////////////////////////

	// m_hShotGraphicの中にプレイヤーショットの画像を入れる
	m_hShotGraphic = LoadGraph(kPlayerShotGraphic);

	// m_hEnemyShotGraphicの中にエネミーのショットの画像を入れる
	m_hEnemyShotGraphic = LoadGraph(kEnemyShotGraphic);	

	// m_hShotGraphicの中にエネミーの回転ショットの画像を入れる
	m_hEnemyRevShotGraphic = LoadGraph(kEnemyRevShotGraphic);	


	// プレイヤーのすべてのショットにショットの画像を入れる
	for (auto& shot : m_shot)
	{
		shot.setHandle(m_hShotGraphic);
	}

	// エネミーのすべてのショットにショットの画像を入れる(直線ショット)
	for (auto& shot : m_EnemyShot)
	{
		shot.setHandle(m_hEnemyShotGraphic);
	}

	// エネミーのすべてのショットにショットの画像を入れる(回転ショット)
	for (auto& shot : m_EnemyRevShot)
	{
		shot.setHandle(m_hEnemyRevShotGraphic);
	}

	//////////////////////////////////////////
	//		   防衛ラインのエフェクト
	//////////////////////////////////////////
	// 防衛ラインのグラフィックサイズを取得
	int DefenseLineW = {};
	int DefenseLineH = {};
	int DefenseLineGreenG = LoadGraph(kDefenseLineFilenameGreen);
	GetGraphSize(DefenseLineGreenG, &DefenseLineW, &DefenseLineH);

	// m_hDefenseLineGraphicGreenの中に防衛ラインの画像を入れる
	LoadDivGraph(kDefenseLineFilenameGreen, DefenseLineEffect::kDefenseLineEffectDivNum,
		DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineEffect::kDefenseLineEffectDivY,
		DefenseLineW / DefenseLineEffect:: kDefenseLineEffectDivX, DefenseLineH / DefenseLineEffect::kDefenseLineEffectDivY,
		m_hDefenseLineGreenGraphic);

	// m_hDefenseLineGraphicYellowの中に防衛ラインの画像を入れる
	LoadDivGraph(kDefenseLineFilenameYellow, DefenseLineEffect::kDefenseLineEffectDivNum,
		DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineEffect::kDefenseLineEffectDivY,
		DefenseLineW / DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineH / DefenseLineEffect::kDefenseLineEffectDivY,
		m_hDefenseLineYellowGraphic);

	// m_hDefenseLineGraphicRedの中に防衛ラインの画像を入れる
	LoadDivGraph(kDefenseLineFilenameRed, DefenseLineEffect::kDefenseLineEffectDivNum,
		DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineEffect::kDefenseLineEffectDivY,
		DefenseLineW / DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineH / DefenseLineEffect::kDefenseLineEffectDivY,
		m_hDefenseLineRedGraphic);

	// 防衛ラインにすべての画像を入れる
	for (int i = 0; i < DefenseLineEffect::kDefenseLineEffectDivNum; i++)
	{
		m_DefenseLine.setEffectG(i, m_hDefenseLineGreenGraphic[i]);
		m_DefenseLine.setEffectY(i, m_hDefenseLineYellowGraphic[i]);
		m_DefenseLine.setEffectR(i, m_hDefenseLineRedGraphic[i]);
	}

	m_DefenseLine.setSizeX(DefenseLineW / DefenseLineEffect::kDefenseLineEffectDivX);

	m_DefenseLine.init();// m_DefenseLineのinit(初期設定)を行う

	//////////////////////////////////////////
	//		   　背景のグラフィック
	//////////////////////////////////////////

	m_hBackGround1 = LoadGraph(kBackGround1);
	m_hBackGround2 = LoadGraph(kBackGround2);
	m_hBoard = LoadGraph(kBoard);
	m_bossText = LoadGraph(kBossText);

	m_playerDamageSound = LoadSoundMem(kPlayerDamageSound);

	m_alarm = LoadSoundMem(kAlarmSound);

	m_enemyDamageSound = LoadSoundMem(kEnemyDamageSound);

	m_DefenseLineSound = LoadSoundMem(kDefenseLineSound);

	m_DefenseLineSound2 = LoadSoundMem(kDefenseLineSound2); 

	m_BGM = LoadSoundMem(kBgm1);

	m_BossBGM = LoadSoundMem(kBgm2);
}

// 終了処理
void SceneMain::end()
{
	// プレイヤーのグラフィックを削除する
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	// プレイヤーのエフェクトを削除する
	for (auto& handle : m_hPlayerEffect)
	{
		DeleteGraph(handle);
	}

	// エネミーのグラフィックを削除する
	for (auto& handle : m_hEnemyGraphic)
	{
		DeleteGraph(handle);	
	}

	// モブエネミーのグラフィックを削除する
	for (auto& handle : m_hMobEnemiesGraphic)
	{
		DeleteGraph(handle);
	}
	// モブエネミーのエフェクトを削除する
	for (auto& handle : m_hMobEnemiesEffect)
	{
		DeleteGraph(handle);
	}

	// 防衛ラインのグラフィックを削除する
	for (auto& handle : m_hDefenseLineGreenGraphic)
	{
		DeleteGraph(handle);
	}

	DeleteGraph(m_hShotGraphic);	// ショットのグラフィックを削除する
	DeleteGraph(m_hEnemyRevShotGraphic);	// 回転するエネミーショットのグラフィックを削除する
}

// 毎フレームの処理
SceneBase* SceneMain::update()
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


	if (!m_playerHP == 0)
	{
		// プレイヤー処理のアップデート
		m_player.update();

	}

	// モブエネミーを撃退ラインまで倒していないとき
	if (m_allMobEnemiesKill == false)
	{
		m_hCount++;

		if (m_hCount >= 60)
		{
			// モブエネミーのinit(初期設定)を行う
			for (auto& mobObject : m_mobEnemy)
			{
				if (!mobObject.isExist())
				{
					mobObject.init();
					m_hCount = 0;
					break;
				}
			}
		}
		// モブエネミー処理のアップデート
		for (auto& mobObject : m_mobEnemy)
		{
			mobObject.update();
		}
	}
	
	if (m_enemyMove == true)
	{
		if (m_textCount >= 800)
		{

			if (m_enemyKillFrag == false)
			{
				m_enemy.update();
			}
		}
	}

	
	// プレイヤーのすべてのショットのアップデート
	for (auto& shot : m_shot)
	{
		shot.update();
	}

	// エネミーのすべてのショットのアップデート(直線ショット)
	for (auto& shot : m_EnemyShot)
	{
		shot.update();
	}

	// エネミーのすべてのショットのアップデート(回転ショット)
	for (auto& shot : m_EnemyRevShot)
	{
		shot.update();
	}

	// m_DefenseLineのアップデート
	m_DefenseLine.update();	


	if (m_count == 0)
	{
		if (m_allMobEnemiesKill == true)
		{
			DeleteSoundMem(m_BGM);
			m_alarmflag = 1;
			m_fadeOutFlag = true;
			if (m_fadeCount == 0)
			{

				m_ChangeFlag = true;
				m_count = 1;
			}
		}
	}
	if(m_count == 1)
	{
		
		m_fadeInFlag = true;
		if (m_fadeCount == 255)
		{
			
			m_enemyMove = true;
			m_count = 2;
		}
		

	}
	//////////////////////////////////////////
	//				当たり判定
	//////////////////////////////////////////

	// モブエネミーを撃退ラインまで倒したとき
	if (m_MobKillCount >= kMobEnemiesRepelLine)
	{
		// モブエネミーをすべて消す
		for (auto& mobObject : m_mobEnemy)
		{
			mobObject.setExist(false);
		}
		// モブエネミーのショットをすべて消す
		for (auto& mobShot : m_EnemyShot)
		{
			mobShot.setExist(false);
		}
		m_allMobEnemiesKill = true;
	}

	// モブエネミーを撃退ラインまで倒していないとき
	if (m_allMobEnemiesKill == false)
	{
		if (CheckSoundMem(m_BGM) == 0)
		{
			PlaySoundMem(m_BGM, DX_PLAYTYPE_BACK);
		}






		if (m_playerDamageFlag == false)
		{
			// プレイヤーのショットがモブエネミーに当たった場合の処理
			if (pShotMobCheckHit())
			{
				m_MobKillCount++;
			}

			// プレイヤーにモブエネミーのショットが当たった場合の処理
			if (playerMobShotCheckHit())
			{
				// プレイヤーのHPを減らす
				m_playerHP--;
				m_playerDamageSoundCount = 1;
				
				// プレイヤーがダメージを受けたかの判定
				m_playerDamageFlag = true;

				// モブエネミーをすべて消す
				for (auto& mobObject : m_mobEnemy)
				{
					mobObject.setExist(false);
				}
				// モブエネミーのショットをすべて消す
				for (auto& mobShot : m_EnemyShot)
				{
					mobShot.setExist(false);
				}
			}

			// プレイヤーがモブエネミーに接触したかどうか
			if (playerMobCheckHit())
			{
				// プレイヤーのHPを減らす
				m_playerHP--;
				m_playerDamageSoundCount = 1;
				
				// プレイヤーがダメージを受けたかの判定
				m_playerDamageFlag = true;

				// モブエネミーをすべて消す
				for (auto& mobObject : m_mobEnemy)
				{
					mobObject.setExist(false);
				}
				// モブエネミーのショットをすべて消す
				for (auto& mobShot : m_EnemyShot)
				{
					mobShot.setExist(false);
				}
			}

			// モブエネミーが防衛ラインに当たった場合の処理
			if (MobDefenseLineCheckHit())
			{
				PlaySoundMem(m_DefenseLineSound, DX_PLAYTYPE_BACK);
				// ディフェンスラインカウントを減らす
				m_DefenseLineCount--;

				m_DefenseLine.setColorChange(m_DefenseLineCount);


				if (m_DefenseLineCount == 1)
				{
					PlaySoundMem(m_DefenseLineSound2, DX_PLAYTYPE_BACK);
				}
				// モブエネミーをすべて消す
				for (auto& mobObject : m_mobEnemy)
				{
					mobObject.setExist(false);
				}
				// モブエネミーのショットをすべて消す
				for (auto& mobShot : m_EnemyShot)
				{
					mobShot.setExist(false);
				}
			}

		}

	}
	
	
	if (m_enemyMove == true)
	{
		if (CheckSoundMem(m_BossBGM) == 0)
		{
			PlaySoundMem(m_BossBGM, DX_PLAYTYPE_BACK);
		}

		if (m_playerDamageFlag == false && m_enemyKillFrag == false)
		{
			if (m_textCount >= 800)
			{

				// プレイヤーとエネミーが接触した場合の処理
				if (playerEnemyCheckHit())
				{
					// プレイヤーのHPを減らす
					m_playerHP--;
					m_playerDamageSoundCount = 1;
					// プレイヤーがダメージを受けたかの判定
					m_playerDamageFlag = true;

					// エネミーのショットをすべて消す
					for (auto& Shot : m_EnemyRevShot)
					{
						Shot.setExist(false);
					}
				}
				// プレイヤーがエネミーショットに接触場合の処理
				if (playerEnemyShotCheckHit())
				{
					// プレイヤーのHPを減らす
					m_playerHP--;
					m_playerDamageSoundCount = 1;
					// プレイヤーがダメージを受けたかの判定
					m_playerDamageFlag = true;
					// エネミーのショットをすべて消す
					for (auto& Shot : m_EnemyRevShot)
					{
						Shot.setExist(false);
					}
				}

				// プレイヤーのショットがエネミーに当たった場合の処理
				if (pShotEnemyCheckHit())
				{
					// エネミーのHPを減らす
					m_enemyHP--;
					PlaySoundMem(m_enemyDamageSound, DX_PLAYTYPE_BACK);
					// エネミーのHPが0以下のとき
					if (m_enemyHP <= 0)
					{
						m_enemyKillFrag = true;
					}
				}
			}

		}
	}

	// プレイヤーのHPが0になったときの処理
	if (m_playerHP <= 0 || m_DefenseLineCount<=0)
	{
		if (m_waitFlag == true)
		{
			WaitTimer(500);

			m_waitFlag = false;
		}

		m_fadeOutFlag = true;
		
		m_playerKillFrag = true;

		if (m_fadeCount == 0)
		{
			DeleteSoundMem(m_BGM);
			DeleteSoundMem(m_BossBGM);
			// ゲームオーバーシーンに移行
			return(new SceneGameOver);
		}
	}

	// エネミーを倒した時の処理
	if (m_enemyKillFrag == true)
	{
		if (m_waitFlag == true)
		{
			WaitTimer(500);

			m_waitFlag = false;
		}
		m_fadeOutFlag = true;

		if (m_fadeCount <= 20)
		{
			DeleteSoundMem(m_BossBGM);
			// ゲームクリアシーンに移行
			return(new SceneGameClear);
		}
	}

	return this;
}

// 毎フレームの描画
void SceneMain::draw()
{
	
	// フェード
	SetDrawBright(m_fadeCount, m_fadeCount, m_fadeCount);

	// 背景の表示
	DrawGraph(0, 0, m_hBackGround2, true);
	// ボードの表示
	DrawGraph(0, 0, m_hBoard, FALSE);
	//エネミーのHPバー
	DrawLine(38, 20, 38 + kHPwidth, 20, GetColor(255, 0, 0), FALSE);//メーターの枠を描画
	DrawLine(38, 20, 38 + kHPwidth * m_enemyHP / m_maxHP, 20, GetColor(0, 255, 0), false);//メーターの中身を描画
	// エネミーのHP表示
	DrawFormatString(8, 20, GetColor(255, 255, 255), "enemyHP:%d/%d", m_enemyHP, kEnemyHP);
	// プレイヤーのHP表示
	DrawFormatString(8, 37, GetColor(255, 255, 255), "playerHP:%d/%d", m_playerHP, kPlayerHP);
	


	if (m_enemyKillFrag)
	{
		m_enemy.effect();
	}
	else
	{
		// エネミーの表示
		m_enemy.draw();
	}

	// モブエネミーを撃退ラインまで倒していないとき
	if (m_ChangeFlag == false)
	{
		
		// 背景の表示
		DrawGraph(0, 0, m_hBackGround1, FALSE);

		// ボードの表示
		DrawGraph(0, 0, m_hBoard, FALSE);
		// モブエネミーキル数
		DrawFormatString(8,15, GetColor(255, 255, 255), "モブエネミーキル数:%d/%d", m_MobKillCount, kMobEnemiesRepelLine);
		// プレイヤーのHP表示
		DrawFormatString(8, 32, GetColor(255, 255, 255), "playerHP:%d/%d", m_playerHP, kPlayerHP);
		// ディフェンスラインの耐久値
		DrawFormatString(8,50, GetColor(255, 255, 255), "防衛ラインの耐久値:%d/%d", 
			m_DefenseLineCount, kDefenseLinePoint);

		for (auto& mobObject : m_mobEnemy)
		{
			if (!mobObject.isExist())
			{
				mobObject.effect();
			}
		// モブエネミーの表示
			mobObject.draw();
		}
		
	}
	
	// プレイヤーのショットの表示
	for (auto& shot : m_shot)
	{
		shot.draw();
	}

	// エネミーのショットの表示(直線)
	for (auto& shot : m_EnemyShot)
	{
		shot.draw();
	}

	// エネミーのショットの表示(回転)
	for (auto& shot : m_EnemyRevShot)
	{
		shot.draw();
	}

	// プレイヤーの点滅表示
	if (m_playerDamageFlag == true)
	{
		if (m_playerKillFrag)
		{
			
			m_player.effect();
		}
		else
		{
			m_frameCount++;
			if (m_frameCount == 10 || m_frameCount == 20 || m_frameCount == 30 || m_frameCount == 40 || m_frameCount == 50)
			{
				m_player.draw();
			}
			if (m_frameCount >= 60)
			{
				m_playerDamageFlag = false;

				m_frameCount = 0;
			}
		}

	}
	else
	{
		// プレイヤーの表示
		m_player.draw();
	}

	if (m_playerDamageSoundCount == 1)
	{
		PlaySoundMem(m_playerDamageSound, DX_PLAYTYPE_BACK);
		if (m_playerHP == 1)
		{
			PlaySoundMem(m_DefenseLineSound2, DX_PLAYTYPE_BACK);
		}

		m_playerDamageSoundCount = 0;
	}


	// m_DefenseLineの描画
	m_DefenseLine.draw();

	if (m_ChangeFlag == true)
	{
	
	
		if (m_textCount <= 1000)
		{
			
			if (m_textCount == 400)
			{
				m_textStop++;
				if (m_textStop >= 30)
				{
					m_textCount = 401;
					m_textStop = 0;
				}
			}
			else
			{
				m_textCount+=8;
			}
			
			// ボスロゴの表示
			DrawRotaGraph(m_textCount, 250, 1.0f, 0, m_bossText, TRUE);
		}
	}

	if (m_alarmflag == 1)
	{
		PlaySoundMem(m_alarm, DX_PLAYTYPE_BACK);
		m_alarmflag = 0;
	}


}

// プレイヤーがショットを打つ
bool SceneMain::createShot(Vec2 pos)
{
	// すべてのショットをみる
	for (auto& shot : m_shot)
	{
		// 存在していないショットを探す
		if (!shot.isExist())
		{
			// ショットを打つ
			shot.start(Vec2(pos));
			
			return true;
		}
	}
	return false;
}

// エネミーがショットを打つ(直線ショット)
bool SceneMain::createEnemyShot(Vec2 pos)
{
	// すべてのショットをみる
	for (auto& shot : m_EnemyShot)
	{
		// 存在していないショットを探す
		if (!shot.isExist())
		{
			// ショットを打つ
			shot.start(Vec2(pos));

			return true;
		}
	}
	return false;
}

// エネミーがショットを打つ(回転ショット)
bool SceneMain::createEnemyRevShot(Vec2 pos)
{
	// すべてのショットをみる
	for (auto& shot : m_EnemyRevShot)
	{
		// 存在していないショットを探す
		if (!shot.isExist())
		{
			shot.setDir(m_angle);
			// ショットを打つ
			shot.start(Vec2(pos));

			if (m_angle <= 10)
			{
				m_angleflag = true;
			}
			else if (m_angle >= 170)
			{
				m_angleflag = false;
			}

			if (m_angleflag == true)
			{
				m_angle += 10.0;
			}
			else
			{
				m_angle -= 10.0;
			}

			//if (m_angle >= 350) m_angle = 0;
			//else m_angle += 10.0;

			return true;
		}
	}
	return false;
}


// プレイヤーとエネミーが接触したかどうか
bool SceneMain::playerEnemyCheckHit()
{
	//当たり判定
	float dx = m_player.getPos().x - m_enemy.getPos().x;
	float dy = m_player.getPos().y - m_enemy.getPos().y;
	float dr = dx * dx + dy * dy;// A²＝B²＋C²

	float ar = kPlayerHitCircleSize + kEnemyHitCircleSize;// 当たり判定の大きさ
	float dl = ar * ar;

	// プレイヤーとエネミーが接触したとき
	if (dr < dl)
	{
		return true;
	}
	// プレイヤーとエネミーが接触していないとき
	return false;
}

// プレイヤーがエネミーのショットに接触したかどうか
bool SceneMain::playerEnemyShotCheckHit()
{
	// すべてのエネミーのショットを見る
	for (auto& shot : m_EnemyRevShot)
	{
		// エネミーのしょっとが存在するとき
		if (shot.isExist())
		{
			// 円形の当たり判定
			float dx = shot.getPos().x - m_player.getPos().x;
			float dy = shot.getPos().y - m_player.getPos().y;
			float dr = dx * dx + dy * dy;// A²＝B²＋C²

			float ar = kPlayerHitCircleSize + kEnemyShotCircleSize;// 当たり判定の大きさ
			float dl = ar * ar;

			// プレイヤーとエネミーが当たったとき
			if (dr < dl)
			{
				return true;
			}
		}
	}
	// プレイヤーとモブエネミーが当たっていないとき
	return false;
}

// プレイヤーのショットがモブエネミーが接触したかどうか
bool SceneMain::pShotMobCheckHit()
{
	// モブエネミーを見る
	for (auto& mobObject : m_mobEnemy)
	{
		// モブエネミーが存在するとき
		if (mobObject.isExist())
		{
			// すべてのプレイヤーの弾をみる
			for (auto& shot : m_shot)
			{
				// プレイヤーのショットが存在するとき
				if (shot.isExist())
				{
					// 円形の当たり判定
					float dx = shot.getPos().x - mobObject.getPos().x;
					float dy = shot.getPos().y - mobObject.getPos().y;
					float dr = dx * dx + dy * dy;// A²＝B²＋C²

					float ar = kPlayerShotCircleSize + kMobEnemiesHitCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;

					// プレイヤーのショットにモブエネミーが当たったとき
					if (dr < dl)
					{
						// モブエネミーに当たったプレイヤーの弾を消す
						shot.setExist(false);
						// プレイヤーのショットに当たったモブエネミーを消す
						mobObject.setExist(false);
						
						return true;
					}
				}
			}
		}
	}
	// プレイヤーの弾にモブエネミーが当たっていないとき
	return false;
}

// プレイヤーがモブエネミーのショットと接触したかどうか
bool SceneMain::playerMobShotCheckHit()
{
	// すべてのモブエネミーのショットを見る
	for (auto& shot : m_EnemyShot)
	{
		// モブエネミーのしょっとが存在するとき
		if (shot.isExist())
		{	
			// 円形の当たり判定
			float dx = shot.getPos().x - m_player.getPos().x;
			float dy = shot.getPos().y - m_player.getPos().y;
			float dr = dx * dx + dy * dy;// A²＝B²＋C²

			float ar = kPlayerHitCircleSize + kEnemyShotCircleSize;// 当たり判定の大きさ
			float dl = ar * ar;

			// プレイヤーとモブエネミーが当たったとき
			if (dr < dl)
			{
				return true;
			}
		}
	}
	// プレイヤーとモブエネミーが当たっていないとき
	return false;
}

// プレイヤーがモブエネミーに接触したかどうか
bool SceneMain::playerMobCheckHit()
{
	// すべてのモブエネミーをみる
	for (auto& mobObject : m_mobEnemy)
	{
		// モブエネミーが存在するとき
		if (mobObject.isExist())
		{
			// 円形の当たり判定
			float dx = m_player.getPos().x - mobObject.getPos().x;
			float dy = m_player.getPos().y - mobObject.getPos().y;
			float dr = dx * dx + dy * dy;// A²＝B²＋C²

			float ar = kPlayerHitCircleSize + kMobEnemiesHitCircleSize;// 当たり判定の大きさ
			float dl = ar * ar;

			// プレイヤーとモブエネミーが当たったとき
			if (dr < dl)
			{
				return true;
			}
		}
	}
	// プレイヤーとモブエネミーが当たっていないとき
	return false;
}

// 防衛ラインにモブエネミーが当たっているかどうか
bool SceneMain::MobDefenseLineCheckHit()
{
	// すべてのモブエネミーをみる
	for (auto& mobObject : m_mobEnemy)
	{
		// モブエネミーが存在するとき
		if (mobObject.isExist())
		{
			// モブエネミーの下先端を取得
			float mobObjectPos = mobObject.getPos().y + kMobEnemiesHitCircleSize;
	
			// 防衛ラインにモブエネミーが当たったとき
			if (mobObjectPos >= DefenseLineEffect::kDefenseLinePosY)
			{
				// 防衛ラインに当たったモブエネミーを消す
				mobObject.setExist(false);
				// 防衛ラインにモブエネミーが当たったときtrueを返す
				return true;
			}
		}
	}
	// 防衛ラインにモブエネミーが当たっていないとき
	return false;
}




// プレイヤーの弾がエネミーが接触したかどうか
bool SceneMain::pShotEnemyCheckHit()
{
	for (auto& shot : m_shot)
	{
		// 弾が存在するとき
		if (shot.isExist())
		{
			// 円形の当たり判定
			float dx = shot.getPos().x - m_enemy.getPos().x;
			float dy = shot.getPos().y - m_enemy.getPos().y;
			float dr = dx * dx + dy * dy;// A²＝B²＋C²

			float ar = kPlayerShotCircleSize + kEnemyHitCircleSize;// 当たり判定の大きさ
			float dl = ar * ar;

			if (dr < dl)
			{
				// エネミーに当たったショットを消す
				shot.setExist(false);
				// エネミーにプレイヤーの弾が当たったとき
				return true;
			}
		}
	}
	// エネミーにプレイヤーの弾は当たっていないとき
	return false;
}


