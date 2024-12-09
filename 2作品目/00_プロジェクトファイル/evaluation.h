//=============================================
//
//�]��[evaluation.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EVALUATION_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _EVALUATION_H_
#include "main.h"
#include "object2D.h"

class CEvaluation : public CObject2D
{
public:
	static const std::string TEX_EVALUATION_S;	//�e�N�X�`���̖��O
	static const std::string TEX_EVALUATION_A;	//�e�N�X�`���̖��O
	static const std::string TEX_EVALUATION_B;	//�e�N�X�`���̖��O
	static const std::string TEX_EVALUATION_C;	//�e�N�X�`���̖��O
	static const int EVALUATION_PRIORITY = 80;  //�`�揇

	typedef enum
	{
		EVALUATION_NONE = 0,
		EVALUATION_S,
		EVALUATION_A,
		EVALUATION_B,
		EVALUATION_C,
		EVALUATION_MAX,
	}EVALUATION;

	CEvaluation(int nPriority = EVALUATION_PRIORITY);
	~CEvaluation()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEvaluation* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,EVALUATION evaluation);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;

};
#endif