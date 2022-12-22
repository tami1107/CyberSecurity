#pragma once

#include "Vec2.h"

class SceneMain;

class MobEnemies
{
public:
	// 定数定義

	// プレイヤーグラフィック分割数
	static constexpr int kMobEnemiesGraphicDivX = 3;
	static constexpr int kMobEnemiesGraphicDivY = 4;
	static constexpr int kMobEnemiesGraphicDivNum = kMobEnemiesGraphicDivX * kMobEnemiesGraphicDivY;

	// エフェクトグラフィック
	static constexpr int kMobEnemiesEffectDivX = 50;
	static constexpr int kMobEnemiesEffectDivY = 1;
	static constexpr int kMobEnemiesEffectDivNum = kMobEnemiesEffectDivX * kMobEnemiesEffectDivY;

	MobEnemies();
	virtual ~MobEnemies();

	// SceneMainを設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEffect(int index, int handle) { m_effect[index] = handle; }


	// プレイヤーの初期化
	void init();

	// 処理
	void update();

	// 描画
	void draw();

	// エフェクト処理
	void effect();

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }
	
	

	// 情報の取得
	Vec2 getPos() const { return m_pos; }


private:

	SceneMain* m_pMain;
	// モブエネミーのグラフィック
	int m_handle[kMobEnemiesGraphicDivNum];
	int m_effect[kMobEnemiesEffectDivNum];



	// フレーム数をカウントする
	int m_frameCount;

	// ショットのフラグ
	bool m_shotFlag;

	// キャラクターのアニメーション
	int m_charAnimeNo;	// 表示する番号
	int m_charAnimeFrame;
	int m_charDirNo;

	// エフェクトのアニメーション
	int m_effectAnimeNo;	// 表示する番号
	int m_effectAnimeFrame;
	int m_effectDirNo;

	int m_shotSound;

	int m_bombSound;

	int m_count;

	// 存在フラグ
	bool m_isExist;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

};