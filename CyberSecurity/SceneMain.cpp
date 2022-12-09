﻿#include <DxLib.h>
#include <cassert>
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"


SceneMain::SceneMain() :
	// グラフィック
	m_hShotGraphic(-1),		// ショットのグラフィック
	m_hEnemyGraphic(-1),	// エネミーのグラフィック
	m_hEnemyShotGraphic(-1),// エネミーのショットのグラフィック
	m_hEnemyRevShotGraphic(-1),	// エネミーの回転ショットのグラフィック

	// エネミーやショットを消す
	m_allDelete(false),

	// すべてのモブエネミーを倒したかどうか
	m_allMobEnemiesKill(false),

	// モブエネミーを倒した数
	m_MobKillCount(),

	// ショットの角度
	m_angle(),
	// カウンター
	m_hCount(0),
	
	// エネミーのHP
	m_enemyHP(kEnemyHP)	
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
	// モブエネミー
	for (auto& handle : m_hMobEnemiesGraphic)
	{
		handle = -1;
	}
	// 防衛ラインのグラフィック
	for (auto& handle : m_hDefenseLineGraphic)
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


	// m_hPlayerGraphicの中にプレイヤーの画像を入れる
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		playerW / Player::kPlayerGraphicDivX, playerH / Player::kPlayerGraphicDivY, m_hPlayerGraphic);

	// m_hPlayerEffectの中にプレイヤーの画像を入れる
	LoadDivGraph(kPlayerEffectFilename, Player::kPlayerEffectDivNum,
		Player::kPlayerEffectDivX, Player::kPlayerEffectDivY,
		pEffectW / Player::kPlayerEffectDivX, pEffectH / Player::kPlayerEffectDivY, m_hPlayerEffect);


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


	m_player.init();// m_playerのinit(初期設定)を行う
	

	//////////////////////////////////////////
	//				エネミー
	//////////////////////////////////////////

	m_hEnemyGraphic = LoadGraph(kEnemyGraphic);	// m_hEnemyGraphicの中にkEnemyGraphic(エネミーの画像)を入れる
	m_enemy.setMain(this);
	m_enemy.setHandle(m_hEnemyGraphic);// SceneEnemyにkEnemyGraphic(エネミーの画像)を送る
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
	int DefenseLineG = LoadGraph(kDefenseLineFilename);
	GetGraphSize(DefenseLineG, &DefenseLineW, &DefenseLineH);

	// m_hDefenseLineGraphicの中にモブエネミーの画像を入れる
	LoadDivGraph(kDefenseLineFilename, DefenseLineEffect::kDefenseLineEffectDivNum,
		DefenseLineEffect::kDefenseLineEffectDivX, DefenseLineEffect::kDefenseLineEffectDivY,
		DefenseLineW / DefenseLineEffect:: kDefenseLineEffectDivX, DefenseLineH / DefenseLineEffect::kDefenseLineEffectDivY,
		m_hDefenseLineGraphic);

	// 防衛ラインにすべての画像を入れる
	for (int i = 0; i < DefenseLineEffect::kDefenseLineEffectDivNum; i++)
	{
		m_DefenseLine.setEffect(i, m_hDefenseLineGraphic[i]);
	}

	m_DefenseLine.setSizeX(DefenseLineW / DefenseLineEffect::kDefenseLineEffectDivX);

	m_DefenseLine.init();// m_DefenseLineのinit(初期設定)を行う


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

	DeleteGraph(m_hEnemyGraphic);	// エネミーのグラフィックを削除する

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
	for (auto& handle : m_hDefenseLineGraphic)
	{
		DeleteGraph(handle);
	}

	DeleteGraph(m_hShotGraphic);	// ショットのグラフィックを削除する
	DeleteGraph(m_hEnemyRevShotGraphic);	// 回転するエネミーショットのグラフィックを削除する
}

// 毎フレームの処理
SceneBase* SceneMain::update()
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


	// プレイヤー処理のアップデート
	m_player.update();
	// エネミー処理のアップデート
	//m_enemy.update();
	

	// モブエネミー処理のアップデート
	for (auto& mobObject : m_mobEnemy)
	{
		mobObject.update();
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

	//////////////////////////////////////////
	//				当たり判定
	//////////////////////////////////////////

	// プレイヤーとエネミーが接触した場合、タイトルにもどる
	if (playerEnemyCheckHit())
	{
		// Titleに切り替え
		return(new SceneTitle);
	}

	// プレイヤーのショットがモブエネミーに当たった場合の処理
	if (pShotMobCheckHit())
	{
	
	}

	// プレイヤーのショットがエネミーに当たった場合の処理
	if (pShotEnemyCheckHit())
	{
		// エネミーのHPを減らす
		m_enemyHP--;

		// エネミーのHPが0以下のとき
		if (m_enemyHP <= 0)
		{
			// Titleに切り替え
			return(new SceneTitle);
		}
	}

	// モブエネミーのショットがプレイヤーに当たった場合の処理
	if (playerMobShotCheckHit())
	{
		// エネミーやショットを消す
		m_allDelete = true;
	}
	

	// プレイヤーがモブエネミーに接触したかどうか
	if (playerMobCheckHit())
	{
		// エネミーやショットを消す
		m_allDelete = true;
	}

	// モブエネミーが防衛ラインに当たった場合の処理
	if (MobDefenseLineCheckHit())
	{
		// エネミーやショットを消す
		m_allDelete = true;
		//return(new SceneGameClear);
	}
	
	// エネミーやショットを消す
	if (m_allDelete == true)
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
		// 消す処理が終わった後、falseに戻す
		m_allDelete = false;
	}


	return this;
}

// 毎フレームの描画
void SceneMain::draw()
{

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

	// プレイヤーの表示
	m_player.draw();
	// エネミーの表示
	m_enemy.draw();
	for (auto& mobObject : m_mobEnemy)
	{
	// モブエネミーの表示
		mobObject.draw();
	}

	// m_DefenseLineの描画
	m_DefenseLine.draw();

	// デバッグ
#if false
	// 角度の取得
	DrawFormatString(0, 45, GetColor(255, 255, 255), "角度=%f", m_angle);
	// エネミーのHP表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "enemyHP:%d", m_enemyHP);
#endif
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

			if (m_angle >= 350) m_angle = 0;
			else m_angle += 10.0;

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
	//for (auto& shot : m_shot)
	//{
	//	// 弾が存在するとき
	//	if (shot.isExist())
	//	{
	//		// 円形の当たり判定
	//		float dx = shot.getPos().x - m_enemy.getPos().x;
	//		float dy = shot.getPos().y - m_enemy.getPos().y;
	//		float dr = dx * dx + dy * dy;// A²＝B²＋C²

	//		float ar = kPlayerShotCircleSize + kEnemyHitCircleSize;// 当たり判定の大きさ
	//		float dl = ar * ar;

	//		if (dr < dl)
	//		{
	//			// エネミーに当たったショットを消す
	//			shot.setExist(false);
	//			// エネミーにプレイヤーの弾が当たったとき
	//			return true;
	//		}
	//	}
	//}
	//// エネミーにプレイヤーの弾は当たっていないとき
	return false;
}


