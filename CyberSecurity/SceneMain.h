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
	const char* const kMobEnemiesEffectFilename = "data/explosion_45.png";	// ���u�G�l�~�[�̃G�t�F�N�g
	const char* const kPlayerShotGraphic = "data/PlayerShot.png";	// �v���C���[�V���b�g�̃O���t�B�b�N
	const char* const kEnemyShotGraphic = "data/EnemyShot.png";	// �v���C���[�V���b�g�̃O���t�B�b�N
	const char* const kEnemyRevShotGraphic = "data/EnemyShot.png";	// �G�l�~�[�̉�]�V���b�g�̃O���t�B�b�N
	const char* const kDefenseLineFilenameGreen = "data/lineGreen.png";	// �h�q���C���̃G�t�F�N�g�ΐF
	const char* const kDefenseLineFilenameYellow = "data/lineYellow.png";	// �h�q���C���̃G�t�F�N�g���F
	const char* const kDefenseLineFilenameRed = "data/lineRed.png";	// �h�q���C���̃G�t�F�N�g�ԐF


	// �����蔻��̑傫��
	static constexpr float kPlayerHitCircleSize = 4;	// �v���C���[�̉~�`�̓����蔻��̑傫��
	static constexpr float kEnemyHitCircleSize = 30;	// �G�l�~�[�̉~�`�̓����蔻��̑傫��
	static constexpr float kMobEnemiesHitCircleSize = 20;	// ���u�G�l�~�[�̉~�`�̓����蔻��̑傫��
	static constexpr float kPlayerShotCircleSize = 5;	// �v���C���[�V���b�g�̉~�`�̓����蔻��̑傫��
	static constexpr float kEnemyShotCircleSize = 5;	// �G�l�~�[�V���b�g�̉~�`�̓����蔻��̑傫��
	static constexpr float kGrazeCircleSize = 20;		// �v���C���[�̃O���C�Y�̉~�`�̓����蔻��̑傫��

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
	virtual bool playerEnemyCheckHit();

	// �v���C���[���G�l�~�[�V���b�g�ɐڐG�������ǂ���
	virtual bool playerEnemyShotCheckHit();


	// �v���C���[�̒e���G�l�~�[�ƐڐG�������ǂ���
	virtual bool pShotEnemyCheckHit();
	
	// �v���C���[�̒e�ƃ��u�G�l�~�[���ڐG�������ǂ���
	virtual bool pShotMobCheckHit();

	// �v���C���[�����u�G�l�~�[�̒e�ɐڐG�������ǂ���
	virtual bool playerMobShotCheckHit();

	// �v���C���[�����u�G�l�~�[�ɐڐG�������ǂ���
	virtual bool playerMobCheckHit();

	// ���u�G�l�~�[���h�q���C���𒴂������ǂ���
	virtual bool MobDefenseLineCheckHit();

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerEffect[Player::kPlayerEffectDivNum];
	int m_hPlayerEffect2[Player::kEffectDivNum];

	

	// �G�l�~�[�̃O���t�B�b�N�n���h��
	int m_hEnemyGraphic[Enemy::kEnemyGraphicDivNum];
	int m_hEnemyEffect[Enemy::kEnemyEffectDivNum];

	// ���u�G�l�~�[�̃O���t�B�b�N�n���h��
	int m_hMobEnemiesGraphic[MobEnemies::kMobEnemiesGraphicDivNum];
	int m_hMobEnemiesEffect[MobEnemies::kMobEnemiesEffectDivNum];


	// �h�q���C���̃O���t�B�b�N�n���h��
	int m_hDefenseLineGreenGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];
	int m_hDefenseLineYellowGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];
	int m_hDefenseLineRedGraphic[DefenseLineEffect::kDefenseLineEffectDivNum];

	// �V���b�g�̃O���t�B�b�N�n���h��
	int m_hShotGraphic;
	int m_hEnemyShotGraphic;
	int m_hEnemyRevShotGraphic;

	// �w�i�̃O���t�B�b�N�n���h��
	int m_hBackGround1;
	int m_hBackGround2;
	int m_hBoard;

	// �J�E���^�[
	int m_hCount;

	// �v���C���[HP
	int m_playerHP;

	// �G�l�~�[HP
	int m_enemyHP;
	int m_maxHP;


	// �V���b�g�̊p�x�X�V
	float m_angle;

	bool m_angleflag;

	// ���ׂẴ��u�G�l�~�[��|�������ǂ���
	bool m_allMobEnemiesKill;

	// ���u�G�l�~�[��|������
	int m_MobKillCount;


	// �h�q���C���̃J�E���g
	int m_DefenseLineCount;
	
	// �t���[���J�E���g
	int m_frameCount;

	// �v���C���[���_���[�W���󂯂����̔���
	bool m_playerDamageFlag;

	// �t�F�[�h�C���t���O
	bool m_fadeInFlag;

	// �t�F�[�h�A�E�g�t���O
	bool m_fadeOutFlag;

	// �v���C���[�G�t�F�N�g
	bool m_playerEffect;

	// �v���C���[���|���ꂽ���ǂ���
	bool m_playerKillFrag;

	// �G�l�~�[���|���ꂽ���ǂ���
	bool m_enemyKillFrag;

	// �G�l�~�[���������ǂ����̔���
	bool m_enemyMove;

	// �{�X��ɍs�����߂̃t���O
	bool m_bossFlag;

	// �Ó]
	bool m_ChangeFlag;

	int m_count;

	int m_fadeCount;

	int m_textCount;

	int m_bossText;

	int m_textStop;

	int m_posX;

	int m_playerDamageSound;

	int m_playerDamageSoundCount;

	int m_alarm;

	int m_alarmflag;

	bool m_waitFlag;

	int m_enemyDamageSound;

	int m_DefenseLineSound;

	int m_DefenseLineSound2;

	int m_BGM;

	int m_BossBGM;

	// �v���C���[�G�t�F�N�g�J�E���^�[
	int m_playerEffectCount;
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