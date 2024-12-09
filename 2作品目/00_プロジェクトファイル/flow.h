//=============================================
//
//�W���a��[flow.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _FLOW_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FLOW_H_

class CFlow : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int FLOW_PRIORITY = 10; //�`�揇
	static const int PLAYER_DAMAGE_FRAME = 60; //�_���[�W��^����t���[���Ԋu
	static const int ENEMY_DAMAGE_FRAME = 10; //�_���[�W��^����t���[���Ԋu
	static const int TEX_SPLIT_X = 4; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y = 1; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME = 7; //�A�j���[�V�����t���[����

	typedef enum
	{
		FLOW_TYPE_PLAYER = 0,
		FLOW_TYPE_ENEMY,
		FLOW_TYPE_MAX,
	}FLOW_TYPE;

	CFlow(int nPriority = FLOW_PRIORITY);
	~CFlow()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�e�쐬
	static CFlow* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size, int nLife,int nDamage,  FLOW_TYPE type);
private:
	int m_nDamageCnt; //�_���[�W��^����܂ł��v������J�E���g
	FLOW_TYPE m_type;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif