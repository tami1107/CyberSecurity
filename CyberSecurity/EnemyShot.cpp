#include "DxLib.h"
#include "EnemyShot.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 5.0f;
	// 当たり判定
	static constexpr int  kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (エネミーショットの円形の当たり判定の大きさ)
	
	static constexpr int  kPlayerHitCircleSize = SceneMain::kPlayerHitCircleSize;	// (エネミーの円形の当たり判定の大きさ)
}

EnemyShot::EnemyShot() :
	m_handle(-1),// ショットのグラフィックハンドル
	m_GraphicSizeX(),// ショットのグラフィックサイズX
	m_GraphicSizeY(),// ショットのグラフィックサイズY
	// ショットの中心位置
	m_CenterPosX(),
	m_CenterPosY(),
	// エネミーのサイズ
	m_PlayerGraphicX(),
	m_PlayerGraphicY(),
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
	// 弾を上方向へ飛ばす
	m_vec.y = kShotSpeed;
}

void EnemyShot::update()
{
	// ショットのグラフィックサイズを求める
	GetGraphSize(m_handle, &m_GraphicSizeX, &m_GraphicSizeY);

	// ショットの中心位置
	m_CenterPosX = m_pos.x + (m_GraphicSizeX / 2);
	m_CenterPosY = m_pos.y + (m_GraphicSizeY / 2);



	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	if (CheckHit() == true)
	{
		

	}
	m_pos += m_vec;

	// 弾が画面外に出たとき存在を消す
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}
// 表示
void EnemyShot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist)return;

	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);


	// デバッグ
#if true
	// ショットの当たり判定
	DrawCircle((int)m_CenterPosX, (int)m_CenterPosY, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
#endif
}





// 弾がプレイヤーに当たったかどうか
bool EnemyShot::CheckHit()
{
	//当たり判定
	float dx = (m_player.getPos().x + m_PlayerGraphicX / 2) - m_CenterPosX;
	float dy = (m_player.getPos().y + m_PlayerGraphicY / 2) - m_CenterPosY;
	float dr = dx * dx + dy * dy;// A²＝B²＋C²

	float ar = kPlayerShotCircleSize + kPlayerHitCircleSize;// 当たり判定の大きさ
	float dl = ar * ar;

	// プレイヤーとエネミーが接触したとき
	if (dr < dl)
	{
		return true;
	}
	// プレイヤーとエネミーが接触していないとき
	return false;
}


//#include "DxLib.h"
//#include "EnemyShot.h"
//#include "game.h"
//#include "SceneMain.h"
//#include "SceneTitle.h"
//
//namespace
//{
//	// ショットスピード
//	constexpr float kShotSpeed = 5.0f;
//	// 当たり判定
//	static constexpr int  kPlayerShotCircleSize = SceneMain::kPlayerShotCircleSize;	// (エネミーショットの円形の当たり判定の大きさ)
//
//	static constexpr int  kPlayerHitCircleSize = SceneMain::kPlayerHitCircleSize;	// (エネミーの円形の当たり判定の大きさ)
//}
//
//EnemyShot::EnemyShot() :
//	m_handle(-1),// ショットのグラフィックハンドル
//	m_GraphicSizeX(),// ショットのグラフィックサイズX
//	m_GraphicSizeY(),// ショットのグラフィックサイズY
//	// ショットの中心位置
//	m_CenterPosX(),
//	m_CenterPosY(),
//	// エネミーのサイズ
//	m_PlayerGraphicX(),
//	m_PlayerGraphicY(),
//	m_isExist(false),
//	m_pos(),
//	m_vec()
//{
//}
//
//EnemyShot::~EnemyShot()
//{
//}
//
//void EnemyShot::start(Vec2 pos)
//{
//	m_isExist = true;
//	m_pos = pos;
//	// 弾を上方向へ飛ばす
//	m_vec.y = kShotSpeed;
//}
//
//void EnemyShot::update()
//{
//	// ショットのグラフィックサイズを求める
//	GetGraphSize(m_handle, &m_GraphicSizeX, &m_GraphicSizeY);
//
//	// ショットの中心位置
//	m_CenterPosX = m_pos.x + (m_GraphicSizeX / 2);
//	m_CenterPosY = m_pos.y + (m_GraphicSizeY / 2);
//
//
//
//	// 弾が存在しなかった場合、ここで処理を終了する
//	if (!m_isExist) return;
//
//	if (CheckHit() == true)
//	{
//
//
//	}
//	m_pos += m_vec;
//
//	// 弾が画面外に出たとき存在を消す
//	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
//		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
//	{
//		m_isExist = false;
//	}
//}
//// 表示
//void EnemyShot::draw()
//{
//	// 弾が存在しなかった場合、ここで処理を終了する
//	if (!m_isExist)return;
//
//	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
//
//
//	// デバッグ
//#if true
//	// ショットの当たり判定
//	DrawCircle((int)m_CenterPosX, (int)m_CenterPosY, kPlayerShotCircleSize, GetColor(255, 0, 0), FALSE);
//#endif
//}
