//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
#include "bullet.h"
//�v���C���[�N���X
class CCharacter : public CObjectX
{
public:
	static const int CHARACTER_PRIORITY = 8; //�`�揇
	static const float  BOSS_FIELD_X; //�{�X���X���W

	typedef enum
	{
		CHARACTER_NORMAL = 0, //�ʏ���
		CHARACTER_DAMAGE, //�_���[�W���
		CHARACTER_STATE_MAX,
	}CHARACTER_STATE;

	CCharacter(int nPriority = CHARACTER_PRIORITY);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Gravity(); //�d�͏���
	void HitBlock(); //�u���b�N�����蔻��
	void HitField(); //�������蔻��
	void HitPlayer(); //�v���C���[�Ƃ̓����蔻��
	void HitEnemy(); //�G�Ƃ̓����蔻��
	void ShotBullet(D3DXVECTOR3 pos,float move, D3DXVECTOR3 size, bool bWay, int nDamage,CBullet::BULLET_ALLEGIANCE Allegiance, CBullet::BULLET_TYPE type); //�e���ˏ���

	//�ړ��ʑ��
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos���
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//���n���Ă邩�ǂ�������
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//�ǂ��������Ă邩�ǂ�������(true:�Efalse:��)
	void SetWay(bool bWay)
	{
		m_bWay = bWay;
	}

	//�̗͑��
	void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	//��ԑ��
	void SetState(CHARACTER_STATE state)
	{
		m_State = state;
	}

	//�X�e�[�g�J�E���g���
	void SetStateCnt(int nStateCnt)
	{
		m_nStateCnt = nStateCnt;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3& GetMove();

	//�ߋ��̈ʒu�擾
	D3DXVECTOR3& GetOldPos();

	//���n���Ă邩�ǂ����擾
	bool& GetLaunding();

	//�ǂ��������Ă邩�ǂ������擾(true:�Efalse:��)
	bool& GetWay();

	//�̗͎擾
	int& GetLife();

	//��Ԏ擾
	CHARACTER_STATE& GetState();

	//�X�e�[�g�J�E���g�擾
	int& GetStateCnt();

private:
	static const float GRAVITY_MOVE; //�d�͒l
	static const float GRAVITY_MAX; //�d�͍ő�l

	D3DXVECTOR3 m_move; //���x
	D3DXVECTOR3 m_oldpos; //�ߋ��̈ʒu
	bool m_bLanding; //���n���Ă邩�ǂ���
	bool m_bWay; //�ǂ��������Ă邩(true:�Efalse:��)
	int m_nLife; //�̗�
	int m_nStateCnt; //�X�e�[�g�؂�ւ��v���J�E���g
	CHARACTER_STATE m_State; //�v���C���[���
	D3DXCOLOR m_col; //�J���[
};
#endif