#include "DxLib.h"
#include "EnemyShot.h"
#include "game.h"
#include "SceneMain.h"
#include "DefenseLineEffect.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 5.0f;
	// 当たり判定
	static constexpr float  kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (エネミーショットの円形の当たり判定の大きさ)
	
	static constexpr float  kPlayerHitCircleSize = SceneMain::kPlayerHitCircleSize;	// (エネミーの円形の当たり判定の大きさ)
}

EnemyShot::EnemyShot() :
	m_handle(-1),// ショットのグラフィックハンドル

	m_isExist(false),
	m_pos(),
	m_vec()
{
}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
	// ショットを下方向へ飛ばす
	m_vec.y = kShotSpeed;
}

void EnemyShot::update()
{
	// ショットが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;


	m_pos += m_vec;

	// ショットが防衛ラインに当たったとき、存在を消す
	if (m_pos.y >= DefenseLineEffect::kDefenseLinePosY)
	{
		m_isExist = false;
	}
}
// 表示
void EnemyShot::draw()
{
	// ショットが存在しなかった場合、ここで処理を終了する
	if (!m_isExist)return;

	// ショットの表示
	DrawRotaGraph((float)m_pos.x, (float)m_pos.y, 1.0, 0.0, m_handle, true);

	// デバッグ
#if true
	// ショットの当たり判定
	DrawCircle((float)m_pos.x, (float)m_pos.y, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}