#pragma once

#include "Vec2.h"
#include "SceneBase.h"
#include "Player.h"

class EnemyShot
{
public:
	EnemyShot();
	virtual ~EnemyShot();

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
	void setExist (bool isExist) { m_isExist = isExist; }


	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:
	// グラフィックハンドル
	int m_handle;

	// 存在フラグ
	bool m_isExist;

	// プレイヤー
	Player m_player;

	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;
};