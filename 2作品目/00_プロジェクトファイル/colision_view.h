//=============================================
//
//�����蔻�����[colision_view.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _COLISION_VIEW_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _COLISION_VIEW_H_

#include "main.h"
#include "object3D.h"

//=============================================
//�����蔻������N���X
//=============================================
class CColision_View :public CObject3D
{
public:
	static const int COLIVISON_VIEW_PRIORITY = 20;  //�`�揇

	CColision_View(int nPriority = COLIVISON_VIEW_PRIORITY);
	~CColision_View()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CColision_View* Create(D3DXVECTOR3 pos, D3DXVECTOR3 Minpos,D3DXVECTOR3 Maxpos, D3DCOLOR col);

private:
	void SetVtxColision_View(D3DXVECTOR3 nor, D3DCOLOR col); //���_����
	D3DCOLOR m_Col; //�J���[
	D3DXVECTOR3 m_Minpos; //�ŏ��l
	D3DXVECTOR3 m_Maxpos; //�ő�l
};
#endif