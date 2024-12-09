//=============================================
//
//�����蔻�����[colision_view.h]
//Auther Matsuda Towa
//
//=============================================
#include "colision_view.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CColision_View::CColision_View(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CColision_View::~CColision_View()
{
}

//=============================================
//������
//=============================================
HRESULT CColision_View::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CColision_View::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CColision_View::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	//���_���W
	SetVtxColision_View(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_Col);
}

//=============================================
//�`��
//=============================================
void CColision_View::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//����
//=============================================
CColision_View* CColision_View::Create(D3DXVECTOR3 pos, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, D3DCOLOR col)
{
	CColision_View* pColision_View = new CColision_View();

	//null�Ȃ�null��Ԃ�
	if (pColision_View == nullptr) { return nullptr; }

	pColision_View->SetPos(pos); //pos���
	pColision_View->m_Minpos = MinPos; //size���
	pColision_View->m_Maxpos = MaxPos; //size���
	pColision_View->m_Col = col; //�J���[���
	pColision_View->SetType(OBJECT_TYPE_COLISION_VIEW); //�^�C�v�ݒ�
	pColision_View->Init();

	return pColision_View;
}

//=============================================
//���_����
//=============================================
void CColision_View::SetVtxColision_View(D3DXVECTOR3 nor, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();
	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	pBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Minpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Minpos.x
		, m_Minpos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Minpos.y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//�A�����b�N
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}
