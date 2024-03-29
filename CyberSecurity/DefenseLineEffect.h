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

	// 防衛ラインの座標
	static constexpr int kDefenseLinePosY = 500;

public:
	DefenseLineEffect();
	virtual ~DefenseLineEffect();

	void setEffectG(int index, int handle) { m_effectG[index] = handle; }
	void setEffectY(int index, int handle) { m_effectY[index] = handle; }
	void setEffectR(int index, int handle) { m_effectR[index] = handle; }

	void setSizeX(int size) { m_sizeX = size; }

	void setColorChange(int num) { m_colorChange = num; }

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

	int m_effectG[kDefenseLineEffectDivNum];
	int m_effectY[kDefenseLineEffectDivNum];
	int m_effectR[kDefenseLineEffectDivNum];

	int m_sizeX;

	// 防衛ラインの数
	int m_number;

	// 防衛ラインのエフェクトのアニメーション
	int m_animeNo;	// 表示する番号
	int m_animeFrame;
	int m_dirNo;

	int m_colorChange; // 色変更

	// 表示位置
	Vec2 m_pos;
};

