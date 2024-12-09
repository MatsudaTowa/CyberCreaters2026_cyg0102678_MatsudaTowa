//=============================================
//
//�Ə�[lockon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "lockon.h"
#include "manager.h"

//tex�p�X
const std::string CLockOn::TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//�ő�_���[�W��^���郍�b�N�I���T�C�Y
const float CLockOn::MAX_DAMAGE_LOCKON_SIZE = 10.0f;
//�З͂���ԒႢ���b�N�I������T�C�Y
const float CLockOn::MIN_DAMAGE_LOCKON_SIZE = 70.0f;
//�����炢�̃_���[�W���b�N�I������T�C�Y
const float CLockOn::MEDIUM_DAMAGE_LOCKON_SIZE = 40.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CLockOn::CLockOn(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CLockOn::~CLockOn()
{
}

//=============================================
//������
//=============================================
HRESULT CLockOn::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CLockOn::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CLockOn::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	ChangeSize();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================
//�`��
//=============================================
void CLockOn::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//�T�C�Y�ύX
//=============================================
void CLockOn::ChangeSize()
{
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	if (size.x > CLockOn::MAX_DAMAGE_LOCKON_SIZE && size.y > CLockOn::MAX_DAMAGE_LOCKON_SIZE)
	{
		size.x-=1.2f;
		size.y-=1.2f;
	}

	SetSize(size);

}

//=============================================
//�T�C�Y���Z�b�g
//=============================================
void CLockOn::SizeReset()
{
	SetSize(m_DefaultSize);
}

//=============================================
//����
//=============================================
CLockOn* CLockOn::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CLockOn* pLockOn = new CLockOn;

	// null�Ȃ�null��Ԃ�
	if (pLockOn == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	pLockOn->SetPos(pos); //pos�ݒ�

	pLockOn->SetSize(size); //�T�C�Y�ݒ�

	pLockOn->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���̐ݒ�

	pLockOn->m_DefaultSize = size;

	pLockOn->m_col = col; //�J���[�̐ݒ�

	pLockOn->SetType(OBJECT_TYPE_LOCKON); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pLockOn->Init(); //�G�t�F�N�g�̏���������

	return pLockOn;
}

//=============================================
//�T�C�Y�`�F���W
//=============================================
void CLockOn::ChangeSize(float fRatioFrame)
{
	float fAddSize = m_DefaultSize.x * fRatioFrame;
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//if (size.x < m_DefaultSize.x)
	{
		size.x = fAddSize;
		size.y = fAddSize;
	}

	SetSize(size);
}
