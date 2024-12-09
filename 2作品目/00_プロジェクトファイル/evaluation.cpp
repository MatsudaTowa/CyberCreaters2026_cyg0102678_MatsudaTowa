//=============================================
//
//�]��[evaluation.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "evaluation.h"
#include "manager.h"

const std::string CEvaluation::TEX_EVALUATION_S = "data\\TEXTURE\\evaluation_S.png";
const std::string CEvaluation::TEX_EVALUATION_A = "data\\TEXTURE\\evaluation_A.png";
const std::string CEvaluation::TEX_EVALUATION_B = "data\\TEXTURE\\evaluation_B.png";
const std::string CEvaluation::TEX_EVALUATION_C = "data\\TEXTURE\\evaluation_C.png";

//=============================================
//�R���X�g���N�^
//=============================================
CEvaluation::CEvaluation(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEvaluation::~CEvaluation()
{
}

//=============================================
//������
//=============================================
HRESULT CEvaluation::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEvaluation::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEvaluation::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CEvaluation::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CEvaluation* CEvaluation::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, EVALUATION evaluation)
{
	CEvaluation* pEvaluation = new CEvaluation;

	// null�Ȃ�null��Ԃ�
	if (pEvaluation == nullptr) { return nullptr; }

	pEvaluation->SetPos(pos); //pos�ݒ�

	pEvaluation->SetSize(size); //�T�C�Y�ݒ�

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	switch (evaluation)
	{
	case CEvaluation::EVALUATION::EVALUATION_S:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_S))); //�e�N�X�`���̐ݒ�
		break;
	case CEvaluation::EVALUATION::EVALUATION_A:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_A))); //�e�N�X�`���̐ݒ�
		break;
	case CEvaluation::EVALUATION::EVALUATION_B:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_B))); //�e�N�X�`���̐ݒ�
		break;
	case CEvaluation::EVALUATION::EVALUATION_C:
		pEvaluation->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_EVALUATION_C))); //�e�N�X�`���̐ݒ�
		break;
	default:
		break;
	}

	pEvaluation->SetType(OBJECT_TYPE_EVALUATION); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pEvaluation->Init();

	return pEvaluation;
}
