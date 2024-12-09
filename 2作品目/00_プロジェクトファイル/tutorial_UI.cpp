//=============================================
//
//�`���[�g���A��UI[tutorial_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial_UI.h"
#include "manager.h"

const std::string CTutorial_UI::TEXTURE_NAME_MOVE_PAD = "data\\TEXTURE\\tutorial_move_pad.png";
const std::string CTutorial_UI::TEXTURE_NAME_MOVE_KEYBOARD = "data\\TEXTURE\\tutorial_move_keyboard.png";
const std::string CTutorial_UI::TEXTURE_NAME_MELEE_PAD = "data\\TEXTURE\\tutorial_melee_pad_B.png";
const std::string CTutorial_UI::TEXTURE_NAME_MELEE_MOUSE = "data\\TEXTURE\\tutorial_melee_mouse_R.png";
const std::string CTutorial_UI::TEXTURE_NAME_SLASH_PAD = "data\\TEXTURE\\tutorial_slash_pad_X.png";
const std::string CTutorial_UI::TEXTURE_NAME_SLASH_MOUSE = "data\\TEXTURE\\tutorial_slash_mouse_L.png";
const std::string CTutorial_UI::TEXTURE_NAME_GAUGE = "data\\TEXTURE\\tutorial_gauge.png";

//=============================================
//�R���X�g���N�^
//=============================================
CTutorial_UI::CTutorial_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTutorial_UI::~CTutorial_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorial_UI::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorial_UI::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTutorial_UI::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	switch (m_type)
	{
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_KEYBOARD))); //�e�N�X�`���̐ݒ�
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_MOUSE))); //�e�N�X�`���̐ݒ�
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH:
		if (pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_MOUSE))); //�e�N�X�`���̐ݒ�
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_GAUGE:
		BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_GAUGE))); //�e�N�X�`���̐ݒ�
		break;
	default:
		break;
	}
}

//=============================================
//�`��
//=============================================
void CTutorial_UI::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//����
//=============================================
CTutorial_UI* CTutorial_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TUTORIAL_TYPE type)
{
	CTutorial_UI* pTutorialUI = new CTutorial_UI;

	// null�Ȃ�null��Ԃ�
	if (pTutorialUI == nullptr) { return nullptr; }

	pTutorialUI->SetPos(pos); //pos�ݒ�

	pTutorialUI->SetSize(size); //�T�C�Y�ݒ�

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	CInputPad* pPad = CManager::GetPad();

	pTutorialUI->m_type = type;

	switch (pTutorialUI->m_type)
	{
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MOVE_KEYBOARD))); //�e�N�X�`���̐ݒ�
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_MELEE_MOUSE))); //�e�N�X�`���̐ݒ�
		}
		break;
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH:
		if (pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_PAD))); //�e�N�X�`���̐ݒ�
		}
		else if (!pPad->GetConnet())
		{
			pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_SLASH_MOUSE))); //�e�N�X�`���̐ݒ�
		}
		break;	
	case CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_GAUGE:
		pTutorialUI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_GAUGE))); //�e�N�X�`���̐ݒ�
		break;
	default:
		break;
	}

	pTutorialUI->SetType(OBJECT_TYPE_TUTORIAL_UI); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pTutorialUI->Init();

	return pTutorialUI;
}
