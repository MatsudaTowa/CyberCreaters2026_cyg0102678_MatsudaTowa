//=============================================
//
//�X�L�b�vUI[skip_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "skip_UI.h"
#include "manager.h"
#include "object.h"

//tex�p�X
const std::string CSkip_UI::BUTTON_START_TEXTURE_NAME = "data\\TEXTURE\\skip_start.png";
const std::string CSkip_UI::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\skip_enter.png";

//=============================================
//�R���X�g���N�^
//=============================================
CSkip_UI::CSkip_UI(int nPriority) :CObject2D(nPriority), m_nChangeCnt(0),m_col(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)),m_bPress(false)
{
	//�����l���
	m_col = D3DXCOLOR(0.2f,0.2f,0.2f,1.0f);
}

//=============================================
//�f�X�g���N�^
//=============================================
CSkip_UI::~CSkip_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CSkip_UI::Init()
{

	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(m_col));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSkip_UI::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSkip_UI::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();

	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	if (pPad->GetConnet())
	{
		BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_START_TEXTURE_NAME)));
	}
	else if (!pPad->GetConnet())
	{
		BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
	}

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(m_col));
}

//=============================================
//�`��
//=============================================
void CSkip_UI::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CSkip_UI* CSkip_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CSkip_UI* pSkip_UI = new CSkip_UI;
	CInputPad* pPad = CManager::GetPad();

	//null�Ȃ�null��Ԃ�
	if (pSkip_UI == nullptr) { return nullptr; }

	pSkip_UI->SetPos(pos); //pos�ݒ�

	pSkip_UI->SetSize(size); //size�ݒ�

	if (pPad->GetConnet())
	{
		pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_START_TEXTURE_NAME)));
	}
	else if (!pPad->GetConnet())
	{
		pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));
	}

	pSkip_UI->SetType(OBJECT_TYPE_TUTORIAL); //�^�C�v�ݒ�

	pSkip_UI->Init();

	return pSkip_UI;
}

void CSkip_UI::ColorChange()
{
	m_nChangeCnt++;
	if (m_nChangeCnt >= CHANGE_FRAME)
	{
		if (m_bPress && m_col.r < 1.0f && m_col.g < 1.0f&& m_col.b < 1.0f)
		{
			m_col.r += 0.1f;
			m_col.g += 0.1f;
			m_col.b += 0.1f;
		}
		else if (!m_bPress && m_col.r > 0.2f && m_col.g > 0.2f && m_col.b > 0.2f)
		{
			m_col.r -= 0.1f;
			m_col.g -= 0.1f;
			m_col.b -= 0.1f;
		}
		m_nChangeCnt = 0;

	}
}
