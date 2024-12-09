//=============================================
//
//�G�̏���[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_H_
#include "main.h"
#include "character.h"
#include "colision_view.h"
#include "lockon.h"
#include "attack_effect.h"

//=============================================
//�G�l�~�[�N���X
//=============================================
class CEnemy : public CCharacter
{
public:
	static const int ENEMY_PRIORITY = 4; //�`�揇
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�	 

	static const int NORMAL_SHOT_FRAME = 140; //���˂���J�E���g
	//�G�l�~�[�̗񋓒�`
	typedef enum
	{
		ENEMY_TYPE_NORMAL = 0,
		ENEMY_TYPE_FLOW,
		ENEMY_TYPE_FLY,
		ENEMY_TYPE_BOSS,
		ENEMY_TYPE_TUTORIAL,
		ENEMY_TYPE_MAX,
	}ENEMY_TYPE;

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	virtual void EnemyMove() = 0; //�G�l�~�[�ړ�����

	//�G�l�~�[�쐬
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const ENEMY_TYPE& type);

	void Damage(int nDamage); //�����蔻��

	bool PlayerDistance(); //�v���C���[�Ƃ̋����𑪂�֐�

	void LockOn();

	void LockOn_Flow();	//�W���a�����Ə��ɍ��킹�ďo��

	ENEMY_TYPE m_Type; //�G�l�~�[�̎��

	static int m_nNumEnemy; //�G�l�~�[�̑���

private:
	static const std::string MODEL_NAME;	//���f���̖��O  
	static const std::string FLOW_MODEL_NAME;	//���f���̖��O  
	static const std::string FLY_MODEL_NAME;	//���f���̖��O 
	static const std::string BOSS_MODEL_NAME;	//���f���̖��O  
	static const std::string TUTORIAL_MODEL_NAME;	//���f���̖��O  
	static const int STATE_FRAME; //�X�e�[�g�ύX�t���[����
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEADZONE_Y; //������߂�����j��
	static const int EFFECT_LIFE = 3; //�G�t�F�N�g�̗̑�

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����

	bool m_bLockOn; //���b�N�I����Ԃ��ǂ���

	CLockOn*m_pLockOn; //���b�N�I���̏��

	CColision_View* m_pColisionView; //�G�l�~�[�̓����蔻��

};

//=============================================
//�ʏ�̓G�N���X
//=============================================
class CNormalEnemy : public CEnemy
{
public:
	static const int NORMAL_ENEMY_TURNFRAME = 90; //�m�[�}���̃G�l�~�[�̈ړ��܂�Ԃ��t���[��
	static const int ENEMY_NORMAL_LIFE = 4; //�G�l�~�[�̗̑�

	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	~CNormalEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;

	CAttack_Effect* m_pAttackEffect; //�U���G�t�F�N�g
private:
	int m_nShotCnt; //�e�𔭎˂���J�E���g
	int m_nTurnFrameCnt; //�܂�Ԃ��t���[�����J�E���g����ϐ�
	bool m_bOldWay; //�ߋ��̕���
};

//=============================================
//�W���a���̓G�N���X
//=============================================
class CFlowEnemy : public CEnemy
{
public:
	static const int FLOW_ENEMY_TURNFRAME = 120; //�m�[�}���̃G�l�~�[�̈ړ��܂�Ԃ��t���[��
	static const int ENEMY_FLOW_LIFE = 3; //�G�l�~�[�̗̑�

	CFlowEnemy(int nPriority = ENEMY_PRIORITY);
	~CFlowEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;
private:
	int m_nShotCnt; //�e�𔭎˂���J�E���g
	int m_nTurnFrameCnt; //�܂�Ԃ��t���[�����J�E���g����ϐ�
	bool m_bOldWay; //�ߋ��̕���
	bool m_bLockOnShot; //���b�N�I�����Ă邩�ǂ���

};

//=============================================
//���ł�̓G�N���X
//=============================================
class CFlyEnemy : public CEnemy
{
public:
	static const int FLY_ENEMY_TURNFRAME = 30; //�m�[�}���̃G�l�~�[�̈ړ��܂�Ԃ��t���[��
	static const int ENEMY_FLY_LIFE = 1; //�G�l�~�[�̗̑�

	CFlyEnemy(int nPriority = ENEMY_PRIORITY);
	~CFlyEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;
private:
	int m_nShotCnt; //�e�𔭎˂���J�E���g
	int m_nTurnFrameCnt; //�܂�Ԃ��t���[�����J�E���g����ϐ�
	bool m_bOldWay; //�ߋ��̕���
	bool m_bLockOnShot; //���b�N�I�����Ă邩�ǂ���
};

//=============================================
//�{�X�̓G�N���X
//=============================================
class CBossEnemy : public CEnemy
{
public:
	//�萔
	static const int BOSS_SHOT_FRAME = 20; //���˂���J�E���g
	static const int CREATE_BULLET = 6; //��������e�̐�
	static const float BOSS_MOVE; //�ʏ펞�̈ړ�	 
	static const float CREATE_RADIUS; //��������e�̈ʒu

	CBossEnemy(int nPriority = ENEMY_PRIORITY);
	~CBossEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;

	static bool m_BossDeath;
private:
	static const int BOSS_ENEMY_TURNFRAME = 120; //���ł�G�l�~�[�̈ړ��܂�Ԃ��t���[��
	static const int ENEMY_BOSS_LIFE = 10; //�G�l�~�[�̗̑�

	int m_nShotCnt; //�e�𔭎˂���J�E���g
	int m_nNumBullet; //�N���G�C�g���ꂽ�e�𐔂���
	int m_nTurnFrameCnt; //�܂�Ԃ��t���[�����J�E���g����ϐ�
	bool m_bOldWay; //�ߋ��̕���
	bool m_bShot; //�e�𔭎˂��邩�ǂ���
	//CElecBullet*pBullet[CREATE_BULLET]; //�{�X�p�̒e�̃|�C���^
};

//=============================================
//�ʏ�̓G�N���X
//=============================================
class CTutorialEnemy : public CEnemy
{
public:
	static const int NORMAL_ENEMY_TURNFRAME = 90; //�m�[�}���̃G�l�~�[�̈ړ��܂�Ԃ��t���[��
	static const int ENEMY_NORMAL_LIFE = 3; //�G�l�~�[�̗̑�

	CTutorialEnemy(int nPriority = ENEMY_PRIORITY);
	~CTutorialEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;

private:
};
#endif