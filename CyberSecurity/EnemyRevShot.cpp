#include "DxLib.h"
#include "EnemyRevShot.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 5.0f;
	// 当たり判定
	static constexpr float kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (エネミーショットの円形の当たり判定の大きさ)

}

EnemyRevShot::EnemyRevShot() :
	m_handle(-1),// ショットのグラフィックハンドル
	m_rad(),// ラジアン
	m_isExist(false),
	m_pos(),
	m_vec()
{
}

EnemyRevShot::~EnemyRevShot()
{
}

void EnemyRevShot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	// 弾を上方向へ飛ばす
	m_vec.y = kShotSpeed;
}

void EnemyRevShot::update()
{
	m_vec.x += cosf(m_rad) * kShotSpeed;
	m_pos.y += sinf(m_rad) * kShotSpeed;
	//m_vec *= kShotSpeed;

	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	//m_pos += m_vec;

	// 弾が画面外に出たとき存在を消す
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
	// ショットが防衛ラインに当たったとき、存在を消す
	if (m_pos.y >= DefenseLineEffect::kDefenseLinePosY)
	{
		m_isExist = false;
	}
}
// 表示
void EnemyRevShot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist)return;

	DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.5, m_rad, m_handle, true);
	// デバッグ
#if true
	// ショットの当たり判定
	DrawCircle((float)m_pos.x, (float)m_pos.y, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}

void EnemyRevShot::setDir(float m_angle)
{
	m_rad = m_angle * DX_PI_F / 180.0f;
}
