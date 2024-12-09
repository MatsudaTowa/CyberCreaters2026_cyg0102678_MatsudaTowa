//=============================================
//
//3DTemplate[item.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ITEM_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ITEM_H_
#include "main.h"
#include "billboard.h"
#include "button_UI.h"
#include "item_UI.h"

class CItem : public CBillboard
{
public:
	static const std::string SLASH_TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const std::string FLOW_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int ITEM_PRIORITY = 3; //�`�揇
	typedef enum
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_PANETRARING_SLASH, //�a���̌�
		ITEMTYPE_FLOW, //�W���a���̌�
		ITEMTYPE_MAX,
	}ITEMTYPE;

	CItem(int nPriority = ITEM_PRIORITY);
	~CItem()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�u���b�N�쐬
	static CItem* Create(ITEMTYPE type, D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXVECTOR3 rot);
private:

	ITEMTYPE m_ItemType; //�A�C�e���̃^�C�v
	void HitItem(); //�A�C�e���Ƃ̓����蔻��
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh; //���b�V�����
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����;

	CButton_UI*m_pButton_UI; //�uF�ŏE���v3DUI
};
#endif