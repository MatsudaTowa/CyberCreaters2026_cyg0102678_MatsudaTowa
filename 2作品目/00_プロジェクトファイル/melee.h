//=============================================
//
//�ߐڍU��[melee.h]
//Auther Matsuda Towa
//
//=============================================

#ifndef _MELEE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MELEE_H_

#include"main.h"
#include "attack_manager.h"
class CMelee : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int MELEE_PRIORITY = 30; //�`�揇
	CMelee(int nPriority = MELEE_PRIORITY);
	~CMelee()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�ߐڍU���쐬
	static CMelee* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,int nDamage);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif