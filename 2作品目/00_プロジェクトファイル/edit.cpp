//=============================================
//
//�G�f�B�^�[[edit.h]
//Auther Matsuda Towa
//
//=============================================
#include "edit.h"
#include "camera.h"
#include "manager.h"
#include "input.h"

//=============================================
//�R���X�g���N�^
//=============================================
CEdit::CEdit()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEdit::~CEdit()
{
}

//=============================================
//������
//=============================================
void CEdit::Init()
{
}

//=============================================
//�X�V
//=============================================
void CEdit::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		SetBlock();
	}
}

//=============================================
//�u���b�N�ݒu
//=============================================
void CEdit::SetBlock()
{
	if (m_nNumBlock < CEdit::BLOCK_MAX)
	{
		CBlock*pBlock = CBlock::Create(CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT,D3DXVECTOR3(0.0f,20.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1,false);

		CInputKeyboard * pKeyboard = CManager::GetKeyboard();

		//�u���b�N�̍��W�擾
		D3DXVECTOR3 pos = pBlock->GetPos();

		if (pKeyboard->GetPress(DIK_D))
		{
			pos.x += 1.0f;
		}

		pBlock->SetPos(pos);
	}
}

//=============================================
//�u���b�N�ۑ�
//=============================================
void CEdit::SaveBlock()
{
}
