#include "DxLib.h"
#include "shot.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 10.0f;
	// 当たり判定
	static constexpr int  kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (エネミーショットの円形の当たり判定の大きさ)

}

Shot::Shot():
	m_handle(-1),// ショットのグラフィックハンドル
	m_isExist(false),
	m_pos(),
	m_vec()
{
}

Shot::~Shot()
{
}

void Shot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	// 弾を上方向へ飛ばす
	m_vec.y = -kShotSpeed;
}

void Shot::update()
{

	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	m_pos += m_vec;

	// 弾が画面外に出たとき存在を消す
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}
// 表示
void Shot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist)return;

	// 弾の表示
	DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.0, 0.0, m_handle, true);
	// デバッグ
#if false
	// ショットの当たり判定
	DrawCircle((int)m_pos.x, (int)m_pos.y, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}
