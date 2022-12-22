#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	// 定数定義

	// プレイヤーグラフィック分割数
	static constexpr int kPlayerGraphicDivX = 3;
	static constexpr int kPlayerGraphicDivY = 5;
	static constexpr int kPlayerGraphicDivNum = kPlayerGraphicDivX * kPlayerGraphicDivY;

	// エンジングラフィック分割数
	static constexpr int kPlayerEffectDivX = 4;
	static constexpr int kPlayerEffectDivY = 4;
	static constexpr int kPlayerEffectDivNum = kPlayerEffectDivX * kPlayerEffectDivY;

	// エフェクトグラフィック
	static constexpr int kEffectDivX = 50;
	static constexpr int kEffectDivY = 1;
	static constexpr int kEffectDivNum = kEffectDivX * kEffectDivY;

	// 最大数
	static constexpr int kObjectMax = 128;

public:
	Player();
	virtual ~Player();

	// SceneMainを設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// グラフィックデータ設定

	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEffect(int index, int handle) { m_effect[index] = handle; }
	void setEffect2(int index, int handle) { m_effect2[index] = handle; }

	// プレイヤーの初期化
	void init();

	// 処理
	void update();

	// 描画
	void draw();

	// 爆発エフェクトの表示
	void effect();


	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:

	SceneMain* m_pMain;
	// プレイヤーのグラフィック
	int m_handle[kPlayerGraphicDivNum] ;
	int m_effect[kPlayerEffectDivNum] ;
	int m_effect2[kEffectDivNum];

	// ショットの発生間隔
	int m_shotInterval;

	// キャラクターのアニメーション
	int m_charAnimeNo;	// 表示する番号

	// エフェクトのアニメーション
	int m_effectAnimeNo;	// 表示する番号
	int m_effectAnimeFrame;
	int m_effectDirNo;

	// エフェクト2のアニメーション
	int m_effect2AnimeNo;	// 表示する番号
	int m_effect2AnimeFrame;
	int m_effect2DirNo;

	int m_shotSound;
	
	int m_bombSound;
	
	int m_count;
	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
};