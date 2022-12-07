#pragma once

#include "Vec2.h"

class SceneMain;

class DefenseLineEffect
{
public:
	// 防衛ラインのエフェクトグラフィック
	static constexpr int kDefenseLineEffectDivX = 4;
	static constexpr int kDefenseLineEffectDivY = 1;
	static constexpr int kDefenseLineEffectDivNum = kDefenseLineEffectDivX * kDefenseLineEffectDivY;

public:
	DefenseLineEffect();
	virtual ~DefenseLineEffect();

	void setEffect(int index, int handle) { m_effect[index] = handle; }

	void setSizeX(int size) { m_sizeX = size; }

	// SceneMainを設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }


	// 初期化
	void init();

	// 処理
	void update();

	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }
private:
	SceneMain* m_pMain;

	int m_effect[kDefenseLineEffectDivNum];

	int m_sizeX;

	// 防衛ラインの数
	int m_number;

	// 防衛ラインのエフェクトのアニメーション
	int m_animeNo;	// 表示する番号
	int m_animeFrame;
	int m_dirNo;


	// 表示位置
	Vec2 m_pos;
};

