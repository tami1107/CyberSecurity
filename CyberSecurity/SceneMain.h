#pragma once


#include "shot.h"
#include "Enemy.h"
#include "MobEnemies.h"
#include "EnemyShot.h"
#include "EnemyRevShot.h"
#include "SceneBase.h"
#include "DefenseLineEffect.h"

class SceneMain : public SceneBase
{
public:

	// �O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphicFilename = "data/Player.png";	// �v���C���[�̃O���t�B�b�N
	const char* const kPlayerEffectFilename = "data/engine.png";	// �v���C���[�̃G�t�F�N�g
	const char* const kEnemyGraphic = "data/player.bmp";	// �G�l�~�[�̃O���t�B�b�N
	const char* const kMobEnemiesGraphicFilename = "data/MobEnemies.png";	// ���u�G�l�~�[�̃O���t�B�b�N
	const char* const kPlayerShotGraphic = "data/PlayerShot.png";	// �v���C���[�V���b�g�̃O���t�B�b�N
	const char* const kEnemyShotGraphic = "data/EnemyShot.png";	// �v���C���[�V���b�g�̃O���t�B�b�N
	const char* const kEnemyRevShotGraphic = "data/EnemyShot.png";	// �G�l�~�[�̉�]�V���b�g�̃O���t�B�b�N
	const char* const kDefenseLineFilename = "data/Path.png";	// �h�q���C���̃G�t�F�N�g

	// �����蔻��̑傫��
	static constexpr int kPlayerHitCircleSize = 4;	// �v���C���[�̉~�`�̓����蔻��̑傫��
	static constexpr int kEnemyHitCircleSize = 40;	// �G�l�~�[�̉~�`�̓����蔻��̑傫��
	static constexpr int kMobEnemiesHitCircleSize = 20;	// ���u�G�l�~�[�̉~�`�̓����蔻��̑傫��
	static constexpr int kPlayerShotCircleSize = 5;	// �v���C���[�V���b�g�̉~�`�̓����蔻��̑傫��
	static constexpr int kEnemyShotCircleSize = 5;	// �G�l�~�[�V���b�g�̉~�`�̓����蔻��̑傫��
	static constexpr int kGrazeCircleSize = 20;		// �v���C���[�̃O���C�Y�̉~�`�̓����蔻��̑傫��

	
	
	// �h�q���C���G�t�F�N�g�A�j���[�V�����̑��x
	int kDefenseLineAnimeChangeFrame = 8;

	// �G�l�~�[��HP
	static constexpr int kEnemyHP = 5;

	// �ő吔
	static constexpr int kObjectMax = 128;

	
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	virtual	void init() override;;
	// �I������
	virtual void end() override;;

	// ���t���[���̏���
	virtual SceneBase* update() override;
	// ���t���[���̕`��
	virtual void draw() override;;

	// �v���C���[���V���b�g������
	bool createShot(Vec2 pos);

	// �G�l�~�[���V���b�g������(�����V���b�g)
	bool createEnemyShot(Vec2 pos);

	// �G�l�~�[���V���b�g������(��]�V���b�g)
	bool createEnemyRevShot(Vec2 pos);

	// �v���C���[�ƃG�l�~�[���ڐG�������ǂ���
	virtual bool CheckHit();

	// �v���C���[�̒e���G�l�~�[�ƐڐG�������ǂ���
	virtual bool EnemyHit();
	
	// �v���C���[�ƃ��u�G�l�~�[���ڐG�������ǂ���
	virtual bool playerMobCheckHit();

	// �v���C���[�̒e�ƃ��u�G�l�~�[���ڐG�������ǂ���
	virtual bool MobShotCheckHit();

	// ���u�G�l�~�[���h�q���C���𒴂������ǂ���
	virtual bool MobDefenseLineCheckHit();


private:
	

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerEffect[Player::kPlayerEffectDivNum];


	// �G�l�~�[�̃O���t�B�b�N�n���h��
	int m_hEnemyGraphic;


	// ���u�G�l�~�[�̃O���t�B�b�N�n���h��
	int m_hMobEnemiesGraphic[MobEnemies::kMobEnemiesGraphicDivNum];

	// �h�q���C���̃O���t�B�b�N�n���h��
	int m_hDefenseLineGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];



	// �V���b�g�̃O���t�B�b�N�n���h��
	int m_hShotGraphic;
	int m_hEnemyShotGraphic;
	int m_hEnemyRevShotGraphic;


	// �J�E���^�[
	int m_hCount;


	// �G�l�~�[HP
	int m_enemyHP;

	float m_angle;

	// �v���C���[
	Player m_player;
	// �G�l�~�[
	Enemy m_enemy;
	// ���u�G�l�~�[
	MobEnemies m_mobEnemy[kObjectMax];
	// �V���b�g
	Shot m_shot[kObjectMax];
	// �G�l�~�[�V���b�g
	EnemyShot m_EnemyShot[kObjectMax];
	// ��]�Ǝ˂���G�l�~�[�V���b�g
	EnemyRevShot m_EnemyRevShot[kObjectMax];
	// �h�q���C���̃G�t�F�N�g
	DefenseLineEffect m_DefenseLine;

};