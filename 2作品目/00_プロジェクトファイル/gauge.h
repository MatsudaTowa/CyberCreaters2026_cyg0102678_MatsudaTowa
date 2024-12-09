//=============================================
//
//�Q�[�W�Ǘ�[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"

//=============================================
//�Q�[�W�N���X
//=============================================
class CGauge : public CObject2D
{
public:

	typedef enum
	{
		GAUGE_TYPE_SLASH = 0,
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_MAX,

	}GAUGE_TYPE;
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int GAUGE_PRIORITY = 81;  //�`�揇
	static const float MAX_GAUGE_WIDE;  //�Q�[�W�̍ő�l
	CGauge(int nPriority = GAUGE_PRIORITY);
	~CGauge()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void AddGauge();
	void SubGauge(float fCost);
	void SetGaugeVtx(float rhw, D3DCOLOR col);
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,GAUGE_TYPE type,D3DXCOLOR col);
	GAUGE_TYPE m_type;
private:
	D3DXCOLOR m_col; //�J���[�ۑ��p
	//static LPDIRECT3DTEXTURE9 m_pTexture;
};

//=============================================
//�U���Q�[�W�N���X
//=============================================
class CGauge_Slash : public CGauge
{
public:
	CGauge_Slash(int nPriority = GAUGE_PRIORITY);
	~CGauge_Slash()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//=============================================
//�̗̓Q�[�W�N���X
//=============================================
class CGauge_Life : public CGauge
{
public:
	CGauge_Life(int nPriority = GAUGE_PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	};
#endif