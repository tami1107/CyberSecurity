#pragma once


#include "shot.h"
#include "Enemy.h"
#include "MobEnemies.h"
#include "EnemyShot.h"
#include "EnemyRevShot.h"
#include "SceneBase.h"
#include "DefenseLineEffect.h"

class SceneMain : public SceneBase
{
public:

	// グラフィックファイル名
	const char* const kPlayerGraphicFilename = "data/Player.png";	// プレイヤーのグラフィック
	const char* const kPlayerEffectFilename = "data/engine.png";	// プレイヤーのエフェクト
	const char* const kEnemyGraphic = "data/player.bmp";	// エネミーのグラフィック
	const char* const kMobEnemiesGraphicFilename = "data/MobEnemies.png";	// モブエネミーのグラフィック
	const char* const kPlayerShotGraphic = "data/PlayerShot.png";	// プレイヤーショットのグラフィック
	const char* const kEnemyShotGraphic = "data/EnemyShot.png";	// プレイヤーショットのグラフィック
	const char* const kEnemyRevShotGraphic = "data/EnemyShot.png";	// エネミーの回転ショットのグラフィック
	const char* const kDefenseLineFilename = "data/Path.png";	// 防衛ラインのエフェクト

	// 当たり判定の大きさ
	static constexpr int kPlayerHitCircleSize = 4;	// プレイヤーの円形の当たり判定の大きさ
	static constexpr int kEnemyHitCircleSize = 40;	// エネミーの円形の当たり判定の大きさ
	static constexpr int kMobEnemiesHitCircleSize = 20;	// モブエネミーの円形の当たり判定の大きさ
	static constexpr int kPlayerShotCircleSize = 5;	// プレイヤーショットの円形の当たり判定の大きさ
	static constexpr int kEnemyShotCircleSize = 5;	// エネミーショットの円形の当たり判定の大きさ
	static constexpr int kGrazeCircleSize = 20;		// プレイヤーのグレイズの円形の当たり判定の大きさ

	
	
	// 防衛ラインエフェクトアニメーションの速度
	int kDefenseLineAnimeChangeFrame = 8;

	// エネミーのHP
	static constexpr int kEnemyHP = 5;

	// 最大数
	static constexpr int kObjectMax = 128;

	
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	virtual	void init() override;;
	// 終了処理
	virtual void end() override;;

	// 毎フレームの処理
	virtual SceneBase* update() override;
	// 毎フレームの描画
	virtual void draw() override;;

	// プレイヤーがショットを撃つ
	bool createShot(Vec2 pos);

	// エネミーがショットを撃つ(直線ショット)
	bool createEnemyShot(Vec2 pos);

	// エネミーがショットを撃つ(回転ショット)
	bool createEnemyRevShot(Vec2 pos);

	// プレイヤーとエネミーが接触したかどうか
	virtual bool CheckHit();

	// プレイヤーの弾がエネミーと接触したかどうか
	virtual bool EnemyHit();
	
	// プレイヤーとモブエネミーが接触したかどうか
	virtual bool playerMobCheckHit();

	// プレイヤーの弾とモブエネミーが接触したかどうか
	virtual bool MobShotCheckHit();

	// モブエネミーが防衛ラインを超えたかどうか
	virtual bool MobDefenseLineCheckHit();


private:
	

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerEffect[Player::kPlayerEffectDivNum];


	// エネミーのグラフィックハンドル
	int m_hEnemyGraphic;


	// モブエネミーのグラフィックハンドル
	int m_hMobEnemiesGraphic[MobEnemies::kMobEnemiesGraphicDivNum];

	// 防衛ラインのグラフィックハンドル
	int m_hDefenseLineGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];



	// ショットのグラフィックハンドル
	int m_hShotGraphic;
	int m_hEnemyShotGraphic;
	int m_hEnemyRevShotGraphic;


	// カウンター
	int m_hCount;


	// エネミーHP
	int m_enemyHP;

	float m_angle;

	// プレイヤー
	Player m_player;
	// エネミー
	Enemy m_enemy;
	// モブエネミー
	MobEnemies m_mobEnemy[kObjectMax];
	// ショット
	Shot m_shot[kObjectMax];
	// エネミーショット
	EnemyShot m_EnemyShot[kObjectMax];
	// 回転照射するエネミーショット
	EnemyRevShot m_EnemyRevShot[kObjectMax];
	// 防衛ラインのエフェクト
	DefenseLineEffect m_DefenseLine;

};