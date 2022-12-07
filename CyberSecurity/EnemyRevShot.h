#pragma once

#include "Vec2.h"
#include "SceneBase.h"


class EnemyRevShot
{
public:
	EnemyRevShot();
	virtual ~EnemyRevShot();

	// グラフィックを得る
	void setHandle(int handle) { m_handle = handle; }

	void setShotPos(Vec2 ShotPos) { m_pos = ShotPos; }

	// 発射
	void start(Vec2 pos);

	// 更新
	void update();
	// 表示
	void draw();

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// 飛んでいく方向を指定する(左方向を0度として時計回りの角度を指定する)
	void setDir(float angle);

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:
	// グラフィックハンドル
	int m_handle;

	// ラジアン
	float m_rad;

	// 存在フラグ
	bool m_isExist;

	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;
};
