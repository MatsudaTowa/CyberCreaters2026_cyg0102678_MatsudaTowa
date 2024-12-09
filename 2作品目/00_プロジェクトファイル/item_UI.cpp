//=============================================
//
//�A�C�e����UI[item_UI.h]
//Auther Matsuda Towa
//
//=============================================
#include "item_UI.h"
#include "manager.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CItem_UI::m_pTexture = nullptr;
const std::string CItem_UI::SLASH_TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";
const std::string CItem_UI::FLOW_TEXTURE_NAME = "data\\TEXTURE\\item_book001.png";
//=============================================
//�R���X�g���N�^
//=============================================
CItem_UI::CItem_UI(int nPriority):CObject2D(nPriority),m_type(CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_NONE)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�^�C�v������
}

//=============================================
//�f�X�g���N�^
//=============================================
CItem_UI::~CItem_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CItem_UI::Init()
{
	//�e�N���X�̏�����
	CObject2D::Init();

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CItem_UI::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CItem_UI::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================
//�`��
//=============================================
void CItem_UI::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

void CItem_UI::SetTex(ITEM_UI_TYPE type)
{
	m_type = type;
	CTexture* pTexture = CManager::GetTexture();
	switch (m_type)
	{
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_NONE:
		SetSize(D3DXVECTOR2(0.0f,0.0f));
		break;
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_PANETRARING_SLASH:
		SetSize(D3DXVECTOR2(80.0f, 80.0f));
		CItem_UI::BindTexture(pTexture->GetAddress(pTexture->Regist(&SLASH_TEXTURE_NAME))); //�e�N�X�`���̐ݒ�
		break;
	case CItem_UI::ITEM_UI_TYPE::ITEM_UI_TYPE_FLOW:
		SetSize(D3DXVECTOR2(80.0f, 80.0f));
		CItem_UI::BindTexture(pTexture->GetAddress(pTexture->Regist(&FLOW_TEXTURE_NAME)));	//�e�N�X�`���̐ݒ�
		break;
	default:
		break;
	}
}

//=============================================
//����
//=============================================
CItem_UI* CItem_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CItem_UI* pItem_UI = new CItem_UI;

    // null�Ȃ�null��Ԃ�
    if (pItem_UI == nullptr) { return nullptr; }

    pItem_UI->SetPos(pos); //pos�ݒ�

    pItem_UI->SetSize(size); //size�ݒ�

    pItem_UI->SetType(OBJECT_TYPE_ITEM_UI); //�I�u�W�F�N�g�^�C�v�ݒ�

    pItem_UI->Init(); //����������

    return pItem_UI;
}
