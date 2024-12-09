//=============================================
//
//�v���C���[����[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "character.h"
#include "manager.h"
#include "gauge.h"
#include "item_UI.h"
#include "lockon.h"
//�v���C���[�N���X
class CPlayer : public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //�`�揇

	typedef enum
	{
		PLAYER_ATTACK_MELEE = 0, //�ߋ����U���̂�
		PLAYER_ATTACK_PANETRARING_SLASH, //�ђʎa��
		PLAYER_ATTACK_FLOW, //�W���a��
		PLAYER_ATTACK_MAX,
	}PLAYER_ATTACK;

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void LockOn();

	void LockOn_ChangeSize(float fRatioFrame);

	void LockOn_Flow();	//�W���a�����Ə��ɍ��킹�ďo��

	void Delete_LockOn();	//�Ə��폜

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	bool m_OldPress; //���N���b�N������Ă邩�ǂ���

	bool m_OldRelease; //���N���b�N�����ꂽ�ǂ���

	PLAYER_ATTACK m_Attack; //�v���C���[�̍U�����@

	static bool m_PlayerDeath;

	bool m_bLockOn; //���b�N�I����Ԃ��ǂ���

	CLockOn* m_pLockOn; //���b�N�I���̏��

private:
	static const std::string MODEL_NAME;	//���f���̖��O

	//�v���C���[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int MAX_JUMPCNT; //�W�����v��
	static const int STATE_FRAME; //�X�e�[�g�ύX�t���[����
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	//�a���֘A
	static const int SLASH_COOLTIME = 30; //�N�[���^�C��
	static const int SLASH_COST = 5; //�a���R�X�g
	static const int CHARGE_INTERVAL = 10; //�i�K���オ��Ԋu
	static const int MAX_CHARGE; //�ŏI�i�K

	static const int MELEE_DAMAGE = 1; //�ߐڃ_���[�W

	void Gauge(CGauge*pGauge);

	void ReSpawn(); //���X�|�[��
	void PlayerMove(); //�v���C���[�ړ�����
	void PerformMelee(D3DXVECTOR3 pos, bool bWay); //�ߐڍU������

	D3DXVECTOR3 m_SlashSize; //�a���̃T�C�Y
	bool m_bSize; //�T�C�Y�ύX���邩�ǂ���
	bool m_bFlow; //�W����Ԃ��ǂ���
	int m_PressCnt; //���b�ԉ����ꂽ��
	int m_ReleaseCnt; //�����Ă���̃J�E���g
	int m_nJumpCnt; //�W�����v�J�E���g
	int m_nChargeCnt; //���i�K�ڂ��J�E���g
	int m_nSlashDamage; //�a���̃_���[�W(�����n���p)

	CItem_UI* m_pItemUI; //���������Ă�̂���2DUI

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����
};
#endif