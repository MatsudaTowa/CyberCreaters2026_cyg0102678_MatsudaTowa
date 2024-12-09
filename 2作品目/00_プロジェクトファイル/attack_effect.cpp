//=============================================
//
//�U���G�t�F�N�g[attack_effect.h]
//Auther Matsuda Towa
//
//=============================================
#include "attack_effect.h"
#include "manager.h"
//�摜������
const int CAttack_Effect::TEX_SPLIT_X = 1;
//�摜������
const int CAttack_Effect::TEX_SPLIT_Y = 1;
//�摜�؂�ւ��J�E���g
const int CAttack_Effect::ANIMATION_FRAME = 5;

//tex�p�X
const std::string CAttack_Effect::TEXTURE_NAME = "data\\TEXTURE\\effect000.jpg";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CAttack_Effect::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CAttack_Effect::CAttack_Effect(int nPriority):CBillboard(nPriority)
{
	SetSize(D3DXVECTOR3(0.0f,0.0f,0.0f));
}

//=============================================
//�f�X�g���N�^
//=============================================
CAttack_Effect::~CAttack_Effect()
{
}

//=============================================
//������
//=============================================
HRESULT CAttack_Effect::Init()
{
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAttack_Effect::Uninit()
{
 	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CAttack_Effect::Update()
{
	CObject3D::Update();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================
//�`��
//=============================================
void CAttack_Effect::Draw()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//
	CBillboard::Draw();

	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//�g��
//=============================================
void CAttack_Effect::SizeChange(float fRatioFrame)
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

//=============================================
//�T�C�Y���Z�b�g
//=============================================
void CAttack_Effect::SizeReset()
{
	SetSize(m_DefaultSize);
}

//=============================================
//����
//=============================================
CAttack_Effect* CAttack_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CAttack_Effect* pAttack_Effect = new CAttack_Effect;

	// null�Ȃ�null��Ԃ�
	if (pAttack_Effect == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	pAttack_Effect->SetPos(pos); //pos�ݒ�

	pAttack_Effect->m_DefaultSize = size; //�T�C�Y�ݒ�

	pAttack_Effect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���̐ݒ�

	pAttack_Effect->m_col = col; //�J���[�̐ݒ�

	pAttack_Effect->SetType(OBJECT_TYPE_ATTACK_EFFECT); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pAttack_Effect->Init(); //�G�t�F�N�g�̏���������

	return pAttack_Effect;
}
