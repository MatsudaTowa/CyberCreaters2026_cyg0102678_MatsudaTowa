//=============================================
//
//�U���G�t�F�N�g[attack_effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ATTACK_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ATTACK_EFFECT_H_
#include "main.h"
#include "billboard.h"

class CAttack_Effect : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int ATTACK_EFFECT_PRIORITY = 3; //�`�揇
	static const int TEX_SPLIT_X; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME; //�A�j���[�V�����t���[����
	CAttack_Effect(int nPriority = ATTACK_EFFECT_PRIORITY);
	~CAttack_Effect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SizeChange(float fRatioFrame);
	void SizeReset();

	//�G�t�F�N�g�쐬
	static CAttack_Effect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_DefaultSize;
};
#endif