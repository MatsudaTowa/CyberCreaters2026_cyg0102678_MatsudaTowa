//=============================================
//
//�`���[�g���A��UI[tutorial_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TUTORIAL_UI_H_
#include "main.h"
#include "billboard.h"

class CTutorial_UI : public CBillboard
{
public:
	typedef enum
	{
		TUTORIAL_TYPE_NONE = 0,
		TUTORIAL_TYPE_MOVE,
		TUTORIAL_TYPE_MELEE,
		TUTORIAL_TYPE_SLASH,
		TUTORIAL_TYPE_GAUGE,
		TUTORIAL_TYPE_MAX,
	}TUTORIAL_TYPE;

	static const std::string TEXTURE_NAME_MOVE_PAD;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_MOVE_KEYBOARD;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_MELEE_PAD;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_MELEE_MOUSE;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_SLASH_PAD;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_SLASH_MOUSE;	//�e�N�X�`���̖��O
	static const std::string TEXTURE_NAME_GAUGE;	//�e�N�X�`���̖��O
	static const int TUTORIAL_UI_PRIORITY = 20; //�`�揇
	CTutorial_UI(int nPriority = TUTORIAL_UI_PRIORITY);
	~CTutorial_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�G�t�F�N�g�쐬
	static CTutorial_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TUTORIAL_TYPE type);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	TUTORIAL_TYPE m_type;
};
#endif