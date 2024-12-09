//=============================================
//
//3DTemplate[effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "effect.h"
#include "manager.h"

//�摜������
const int CEffect::TEX_SPLIT_X = 1;
//�摜������
const int CEffect::TEX_SPLIT_Y = 1;
//�摜�؂�ւ��J�E���g
const int CEffect::ANIMATION_FRAME = 5;

//tex�p�X
const std::string CEffect::TEXTURE_NAME = "data\\TEXTURE\\120.png";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEffect::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CEffect::CEffect(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEffect::~CEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CEffect::Init()
{
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);

	////�e�N�X�`���ړ��ʎ擾
	//D3DXVECTOR2 tex_move = GetTexMove();
	//tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	//tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//�e�N�X�`���ړ��ʑ��
	//SetTexMove(tex_move);

	//�e�N�X�`�����W�擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 1.0f;
	tex_pos.y = 1.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);
	
	////�A�j���[�V�����t���[�����
	//SetAnimFrame(ANIMATION_FRAME);

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f,0.0f,-1.0f), m_col);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEffect::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEffect::Update()
{
	//�e�N�X�`�����擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	//D3DXVECTOR2 tex_move = GetTexMove();
	//AnimationTex(tex_pos, tex_move);

	D3DXVECTOR3 size = GetSize();
	if (m_nLife > 0)
	{
		m_nLife--;
		size.x -= 0.2f;
		size.y -= 0.2f;
	}
	else
	{
		Release();
		return;
	}
	SetSize(size);
	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
}

//=============================================  
//�`��
//=============================================
void CEffect::Draw()
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
//�G�t�F�N�g����
//=============================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	CEffect* pEffect = new CEffect;

	// null�Ȃ�null��Ԃ�
	if (pEffect == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	pEffect->SetPos(pos); //pos�ݒ�

	pEffect->SetSize(size); //�T�C�Y�ݒ�

	pEffect->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���̐ݒ�

	pEffect->m_col = col; //�J���[�̐ݒ�

	pEffect->m_nLife = nLife; //�����̎�������

	pEffect->SetType(OBJECT_TYPE_EFFECT); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pEffect->Init(); //�G�t�F�N�g�̏���������

	return pEffect;
}
