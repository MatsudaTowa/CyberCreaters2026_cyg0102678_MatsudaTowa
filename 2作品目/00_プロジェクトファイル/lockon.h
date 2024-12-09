//=============================================
//
//�Ə�[lockon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _LOCKON_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _LOCKON_H_
#include "main.h"
#include "billboard.h"

class CLockOn : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int LOCKON_PRIORITY = 10; //�`�揇
	static const float MAX_DAMAGE_LOCKON_SIZE; //�ő�_���[�W��^���郍�b�N�I���T�C�Y
	static const float MIN_DAMAGE_LOCKON_SIZE; //�З͂���ԒႢ���b�N�I������T�C�Y
	static const float MEDIUM_DAMAGE_LOCKON_SIZE; //�����炢�̃_���[�W���b�N�I������T�C�Y
	CLockOn(int nPriority = LOCKON_PRIORITY);
	~CLockOn()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void ChangeSize();
	void ChangeSize(float fRatioFrame);
	void SizeReset();
	//�G�t�F�N�g�쐬
	static CLockOn* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXVECTOR3 m_DefaultSize;
	D3DXCOLOR m_col;
};
#endif