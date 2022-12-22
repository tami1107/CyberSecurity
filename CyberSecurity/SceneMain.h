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
	const char* const kMobEnemiesEffectFilename = "data/explosion_45.png";	// モブエネミーのエフェクト
	const char* const kPlayerShotGraphic = "data/PlayerShot.png";	// プレイヤーショットのグラフィック
	const char* const kEnemyShotGraphic = "data/EnemyShot.png";	// プレイヤーショットのグラフィック
	const char* const kEnemyRevShotGraphic = "data/EnemyShot.png";	// エネミーの回転ショットのグラフィック
	const char* const kDefenseLineFilenameGreen = "data/lineGreen.png";	// 防衛ラインのエフェクト緑色
	const char* const kDefenseLineFilenameYellow = "data/lineYellow.png";	// 防衛ラインのエフェクト黄色
	const char* const kDefenseLineFilenameRed = "data/lineRed.png";	// 防衛ラインのエフェクト赤色


	// 当たり判定の大きさ
	static constexpr float kPlayerHitCircleSize = 4;	// プレイヤーの円形の当たり判定の大きさ
	static constexpr float kEnemyHitCircleSize = 30;	// エネミーの円形の当たり判定の大きさ
	static constexpr float kMobEnemiesHitCircleSize = 20;	// モブエネミーの円形の当たり判定の大きさ
	static constexpr float kPlayerShotCircleSize = 5;	// プレイヤーショットの円形の当たり判定の大きさ
	static constexpr float kEnemyShotCircleSize = 5;	// エネミーショットの円形の当たり判定の大きさ
	static constexpr float kGrazeCircleSize = 20;		// プレイヤーのグレイズの円形の当たり判定の大きさ

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
	virtual bool playerEnemyCheckHit();

	// プレイヤーがエネミーショットに接触したかどうか
	virtual bool playerEnemyShotCheckHit();


	// プレイヤーの弾がエネミーと接触したかどうか
	virtual bool pShotEnemyCheckHit();
	
	// プレイヤーの弾とモブエネミーが接触したかどうか
	virtual bool pShotMobCheckHit();

	// プレイヤーがモブエネミーの弾に接触したかどうか
	virtual bool playerMobShotCheckHit();

	// プレイヤーがモブエネミーに接触したかどうか
	virtual bool playerMobCheckHit();

	// モブエネミーが防衛ラインを超えたかどうか
	virtual bool MobDefenseLineCheckHit();

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerEffect[Player::kPlayerEffectDivNum];
	int m_hPlayerEffect2[Player::kEffectDivNum];

	

	// エネミーのグラフィックハンドル
	int m_hEnemyGraphic[Enemy::kEnemyGraphicDivNum];
	int m_hEnemyEffect[Enemy::kEnemyEffectDivNum];

	// モブエネミーのグラフィックハンドル
	int m_hMobEnemiesGraphic[MobEnemies::kMobEnemiesGraphicDivNum];
	int m_hMobEnemiesEffect[MobEnemies::kMobEnemiesEffectDivNum];


	// 防衛ラインのグラフィックハンドル
	int m_hDefenseLineGreenGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];
	int m_hDefenseLineYellowGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];
	int m_hDefenseLineRedGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];

	// ショットのグラフィックハンドル
	int m_hShotGraphic;
	int m_hEnemyShotGraphic;
	int m_hEnemyRevShotGraphic;

	// 背景のグラフィックハンドル
	int m_hBackGround1;
	int m_hBackGround2;
	int m_hBoard;

	// カウンター
	int m_hCount;

	// プレイヤーHP
	int m_playerHP;

	// エネミーHP
	int m_enemyHP;
	int m_maxHP;


	// ショットの角度更新
	float m_angle;

	bool m_angleflag;

	// すべてのモブエネミーを倒したかどうか
	bool m_allMobEnemiesKill;

	// モブエネミーを倒した数
	int m_MobKillCount;


	// 防衛ラインのカウント
	int m_DefenseLineCount;
	
	// フレームカウント
	int m_frameCount;

	// プレイヤーがダメージを受けたかの判定
	bool m_playerDamageFlag;

	// フェードインフラグ
	bool m_fadeInFlag;

	// フェードアウトフラグ
	bool m_fadeOutFlag;

	// プレイヤーエフェクト
	bool m_playerEffect;

	// プレイヤーが倒されたかどうか
	bool m_playerKillFrag;

	// エネミーが倒されたかどうか
	bool m_enemyKillFrag;

	// エネミーが動くかどうかの判定
	bool m_enemyMove;

	// ボス戦に行くためのフラグ
	bool m_bossFlag;

	// 暗転
	bool m_ChangeFlag;

	int m_count;

	int m_fadeCount;

	int m_textCount;

	int m_bossText;

	int m_textStop;

	int m_posX;

	int m_playerDamageSound;

	int m_playerDamageSoundCount;

	int m_alarm;

	int m_alarmflag;

	bool m_waitFlag;

	int m_enemyDamageSound;

	int m_DefenseLineSound;

	int m_DefenseLineSound2;

	int m_BGM;

	int m_BossBGM;

	// プレイヤーエフェクトカウンター
	int m_playerEffectCount;
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