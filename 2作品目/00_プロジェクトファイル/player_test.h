//=============================================
//
//3DTemplate[player_test.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_TEST_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_TEST_H_
#include "main.h"
#include "model_parts.h"
#include "character.h"
//�v���C���[�N���X
class CPlayer_test:public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //�`�揇
	static const int PLAYER_PARTS = 10; //�p�[�c��
	static const int PARTS_PARENT[PLAYER_PARTS]; //�p�[�c��
	static const std::string PLAYERPARTS_NAME[PLAYER_PARTS]; //�t�@�C���p�X

	CPlayer_test(int nPriority = PLAYER_PRIORITY);
	~CPlayer_test();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();


	//�v���C���[�쐬
	static CPlayer_test* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

	void Damage(int nDamage); //�����蔻��

	bool m_OldPress; //���N���b�N������Ă邩�ǂ���

	static bool m_PlayerDeath;

private:

	//�v���C���[�̈ړ��֘A
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int MAX_JUMPCNT; //�W�����v��
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	//�a���֘A
	static const int SLASH_COST = 5; //�a���R�X�g
	static const int CHARGE_INTERVAL = 5; //�i�K���オ��Ԋu
	static const int MAX_CHARGE; //�ŏI�i�K

	static const int MELEE_DAMAGE = 1; //�ߐڃ_���[�W

	void ReSpawn(); //���X�|�[��
	void PlayerMove(); //�v���C���[�ړ�����
	void PerformMelee(D3DXVECTOR3 pos, bool bWay); //�ߐڍU������

	D3DXVECTOR3 m_SlashSize; //�a���̃T�C�Y
	bool m_bSize; //�T�C�Y�ύX���邩�ǂ���
	int m_PressCnt; //���b�ԉ����ꂽ��
	int m_nJumpCnt; //�W�����v�J�E���g
	int m_nChargeCnt; //���i�K�ڂ��J�E���g
	int m_nSlashDamage; //�a���̃_���[�W(�����n���p)

	CModel_Parts*m_apModel[PLAYER_PARTS];

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����
};
#endif