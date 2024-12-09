//=============================================
//
//�A�C�e������[item.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "item.h"
#include "effect.h"
#include "manager.h"
#include "player.h"
#include "colision.h"
#include "score.h"
#include "game.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CItem::m_pTextureTemp = nullptr;
const std::string CItem::SLASH_TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";
const std::string CItem::FLOW_TEXTURE_NAME = "data\\TEXTURE\\item_book001.png";

//=============================================
//�R���X�g���N�^
//=============================================
CItem::CItem(int nPriority):CBillboard(nPriority)
{
}
//=============================================
//�f�X�g���N�^
//=============================================
CItem::~CItem()
{
}

//=============================================
//������
//=============================================
HRESULT CItem::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pButton_UI = nullptr;

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CItem::Uninit()
{
	if (m_pButton_UI != nullptr)
	{
		//�A�C�e���̍폜
		m_pButton_UI->Uninit();
		m_pButton_UI = nullptr;
	}
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CItem::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	HitItem();

}

//=============================================
//�`��
//=============================================
void CItem::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CItem* CItem::Create(ITEMTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CItem* pItem = new CItem;

	if (pItem == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pItem->m_ItemType = type; //�A�C�e���^�C�v�ݒ�

	pItem->SetPos(pos); //pos�ݒ�
	pItem->SetSize(size); //size�ݒ�
	pItem->SetRot(rot); //rot�ݒ�
	switch (pItem->m_ItemType)
	{
	case CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH:
		pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&SLASH_TEXTURE_NAME))); //�e�N�X�`���̐ݒ�
		break;
	case CItem::ITEMTYPE::ITEMTYPE_FLOW:
		pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&FLOW_TEXTURE_NAME)));	//�e�N�X�`���̐ݒ�
		break;
	default:
		break;
	}

	pItem->SetType(OBJECT_TYPE_ITEM); //�^�C�v�ݒ�

	pItem->Init();

	return pItem;
}

//=============================================
//�����蔻��
//=============================================
void CItem::HitItem()
{
	//�ʒu�擾
	D3DXVECTOR3 Itempos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Itemsize = GetSize();

	//�L�[�{�[�h���擾
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputPad* pPad = CManager::GetPad();

	//�v���C���[�A�^�b�N�^�C�v�̃|�C���^������
	CPlayer::PLAYER_ATTACK pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_MELEE; 

	switch (m_ItemType)
	{//�^�C�v�ɉ����ăv���C���[�̃A�^�b�N�^�C�v�ύX
	case CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH:
		pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_PANETRARING_SLASH;
		break;

	case CItem::ITEMTYPE::ITEMTYPE_FLOW:
		pPlayerAttack = CPlayer::PLAYER_ATTACK::PLAYER_ATTACK_FLOW;
		break;
	default:
		break;
	}

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				CColision::COLISION colision = CColision::CheckItemColision(Itempos, Itemsize,pPlayer->GetPos(),pPlayer->GetMinPos(),pPlayer->GetMaxPos());

				if (colision != CColision::COLISION::COLISON_NONE)
				{//�������Ă���
					//�U���̍폜
					if (m_pButton_UI == nullptr)
					{
						m_pButton_UI = CButton_UI::Create(D3DXVECTOR3(Itempos.x, Itempos.y + 20.0f, Itempos.z - 15.0f), D3DXVECTOR3(40.0f, 10.0f, 0.0f));
					}
					if (pKeyboard->GetTrigger(DIK_F) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_Y))
					{
						if (pPlayer->m_Attack != pPlayerAttack)
						{
							pPlayer->m_Attack = pPlayerAttack;
						}
						else if (pPlayer->m_Attack == pPlayerAttack)
						{
							CScore* pScore = CGame::GetScore();

							pScore->AddScore(100);
						}

						if (m_pButton_UI != nullptr)
						{
							//�A�C�e���̍폜
							m_pButton_UI->Uninit();
							m_pButton_UI = nullptr;
						}

						Uninit();
					}
				}
				else
				{
					if (m_pButton_UI != nullptr)
					{
						m_pButton_UI->Uninit();
						m_pButton_UI = nullptr;
					}
				}
			}
		}
	}
}
