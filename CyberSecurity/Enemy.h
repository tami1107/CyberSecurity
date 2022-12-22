#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:

	// エネミーグラフィック分割数
	static constexpr int kEnemyGraphicDivX = 3;
	static constexpr int kEnemyGraphicDivY = 4;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;

	// エフェクトグラフィック
	static constexpr int kEnemyEffectDivX = 50;
	static constexpr int kEnemyEffectDivY = 1;
	static constexpr int kEnemyEffectDivNum = kEnemyEffectDivX * kEnemyEffectDivY;

	Enemy();
	virtual ~Enemy();

	// SceneMainを設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEffect(int index, int handle) { m_effect[index] = handle; }

	// エネミーの初期化
	void init();

	// 処理
	void update();
	// 描画
	void draw();

	// エフェクト処理
	void effect();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:
	SceneMain* m_pMain;

	// モブエネミーのグラフィック
	int m_handle[kEnemyGraphicDivNum];
	int m_effect[kEnemyEffectDivNum];

	// ショットの発生間隔
	int m_shotInterval;

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

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	
};