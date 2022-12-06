#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include <cassert>


SceneMain::SceneMain():
	// グラフィック
	m_hShotGraphic(-1),		// (エネミーのグラフィック)
	m_hEnemyGraphic(-1),	// (ショットのグラフィック)
	m_hEnemyRevShotGraphic(-1),	// (エネミーの回転ショットのグラフィック)

	// ショットの角度
	m_angle(),

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

	// player.hにプレイヤーの画像を送る
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

	//// モブエネミーエフェクトのグラフィックサイズを取得
	//int mEffectW = {};
	//int mEffectH = {};
	//int mEffectG = LoadGraph(kMobEnemiesGraphic);
	//GetGraphSize(mEffectG, &mEffectW, &mEffectH);


	// m_hPlayerGraphicの中にプレイヤーの画像を入れる
	LoadDivGraph(kMobEnemiesGraphicFilename, MobEnemies::kMobEnemiesGraphicDivNum,
		MobEnemies::kMobEnemiesGraphicDivX, MobEnemies::kMobEnemiesGraphicDivY,
		mobEnemyW / MobEnemies::kMobEnemiesGraphicDivX, mobEnemyH / MobEnemies::kMobEnemiesGraphicDivY, m_hMobEnemiesGraphic);

	//// m_hPlayerEffectの中にプレイヤーの画像を入れる
	//LoadDivGraph(kPlayerEffectFilename, Player::kPlayerEffectDivNum,
	//	Player::kPlayerEffectDivX, Player::kPlayerEffectDivY,
	//	pEffectW / Player::kPlayerEffectDivX, pEffectH / Player::kPlayerEffectDivY, m_hPlayerEffect);

	m_mobEnemy.setMain(this);


	//  m_hMobEnemies.hにモブエネミーの画像を送る
	for (int i = 0; i < MobEnemies::kMobEnemiesGraphicDivNum; i++)
	{
		m_mobEnemy.setHandle(i, m_hMobEnemiesGraphic[i]);
	}

	//// player.hにプレイヤーの画像を送る
	//for (int i = 0; i < MobEnemies::kMobEnemiesGraphicDivNum; i++)
	//{
	//	m_player.setEffect(i, m_hPlayerEffect[i]);
	//}


	m_mobEnemy.init();// m_playerのinit(初期設定)を行う

	//////////////////////////////////////////
	//				ショット
	//////////////////////////////////////////

	m_hShotGraphic = LoadGraph(kPlayerShotGraphic);	// m_hShotGraphicの中にkPlayerShotGraphic(ショットの画像)を入れる
	m_hEnemyRevShotGraphic = LoadGraph(kEnemyRevShotGraphic);	// m_hShotGraphicの中に(エネミーの回転ショットの画像)を入れる


	// プレイヤーのすべてのショットにショットの画像を入れる
	for (auto& shot : m_shot)
	{
		shot.setHandle(m_hShotGraphic);
	}

	// エネミーのすべてのショットにショットの画像を入れる(直線ショット)
	for (auto& shot : m_EnemyShot)
	{
		shot.setHandle(m_hShotGraphic);
	}

	// エネミーのすべてのショットにショットの画像を入れる(回転ショット)
	for (auto& shot : m_EnemyRevShot)
	{
		shot.setHandle(m_hEnemyRevShotGraphic);
	}

}

// 終了処理
void SceneMain::end()
{
	// プレイヤーのグラフィックを削除する
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hEnemyGraphic);	// エネミーのグラフィックを削除する
	// モブエネミーのグラフィックを削除する
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hShotGraphic);	// ショットのグラフィックを削除する
	DeleteGraph(m_hEnemyRevShotGraphic);	// 回転するエネミーショットのグラフィックを削除する
}

// 毎フレームの処理
SceneBase* SceneMain::update()
{
	// プレイヤー処理のアップデート
	m_player.update();
	// エネミー処理のアップデート
	//m_enemy.update();

	// モブエネミー処理のアップデート
	m_mobEnemy.update();


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


	//////////////////////////////////////////
	//				当たり判定
	//////////////////////////////////////////

	// プレイヤーとエネミーが接触した場合、タイトルにもどる
	if (CheckHit())
	{
		// Titleに切り替え
		return(new SceneTitle);
	}

	// プレイヤーの弾がエネミーに当たった場合、タイトルに戻る
	if (EnemyHit() == true)
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
	return this;
}

// 毎フレームの描画
void SceneMain::draw()
{
	DrawBox(0, 0, 800, 600,GetColor(255,0,255), true);


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
	// モブエネミーの表示
	m_mobEnemy.draw();

	// デバッグ
#if true
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
bool SceneMain::CheckHit()
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

// プレイヤーの弾がエネミーが接触したかどうか
bool SceneMain::EnemyHit()
{
	for (auto& shot : m_shot)
	{
		// 弾が存在するとき
		if (shot.isExist())
		{
			//円形の当たり判定
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