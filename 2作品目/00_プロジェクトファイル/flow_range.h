//=============================================
//
//�v���C���[�̏W���U���͈̔�[flow_range.h]
//Auther Matsuda Towa
//
//=============================================

#ifndef _FLOW_RANGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FLOW_RANGE_H_

#include"main.h"
#include "object3D.h"
class CFlow_Range : public CObject3D
{
public:
	static const int FLOW_RANGE_PRIORITY = 4; //�`�揇
	CFlow_Range(int nPriority = FLOW_RANGE_PRIORITY);
	~CFlow_Range()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�ߐڍU���쐬
	static CFlow_Range* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Minpos, D3DXVECTOR3 Maxpos);

	//�ŏ��l�擾
	D3DXVECTOR3& GetMinPos();

	//�ő�l�擾
	D3DXVECTOR3& GetMaxPos();

	void SizeUp(bool bWay);
private:
	D3DXVECTOR3 m_Minpos;
	D3DXVECTOR3 m_Maxpos;
	void SetVtxFlow_Range(D3DXVECTOR3 nor, D3DCOLOR col);

};
#endif