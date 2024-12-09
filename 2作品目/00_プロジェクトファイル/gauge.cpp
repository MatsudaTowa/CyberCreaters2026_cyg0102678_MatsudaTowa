//=============================================
//
//�Q�[�W�Ǘ�[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"
#include "player.h"

//�Q�[�W�̍ő�l
const float CGauge::MAX_GAUGE_WIDE = 350.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CGauge::CGauge(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge::Init()
{
    //�e�N���X�̏��������Ă�
    CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

    //���_�ݒ�
	SetGaugeVtx(1.0f, m_col);

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge::Uninit()
{
    //�e�N���X�̏I���Ă�
    CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge::Update()
{
    //�e�N���X�̍X�V�Ă�
    CObject2D::Update();

	//���_�ݒ�
	SetGaugeVtx(1.0f, m_col);
}

//=============================================
//�`��
//=============================================
void CGauge::Draw()
{
    //�e�N���X�̕`��Ă�
    CObject2D::Draw();
}

//=============================================
//�Q�[�W��������
//=============================================
void CGauge::AddGauge()
{
	//�������g�̃T�C�Y�擾
   D3DXVECTOR2 size = GetSize();

   size.x += 1.5f;

   //�T�C�Y���
   SetSize(size);
}

//=============================================
//�Q�[�W��������
//=============================================
void CGauge::SubGauge(float fCost)
{
	//�������g�̃T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size.x -= fCost;

	//�T�C�Y���
	SetSize(size);
}

//=============================================
//�Q�[�W�̒��_����
//=============================================
void CGauge::SetGaugeVtx(float rhw, D3DCOLOR col)
{
    CRenderer* pRender = CManager::GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

    if (GetVtxBuff() == nullptr)
    {
        pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetVtxBuff(), NULL);
    }
    VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	GetVtxBuff()->Unlock();
}

//=============================================
//����
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE_TYPE type, D3DXCOLOR col)
{
    CGauge* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_SLASH:
		pGauge = new CGauge_Slash;
		pGauge->SetType(OBJECT_TYPE_GAUGE_SLASH); //�^�C�v�ݒ�
		break;
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		pGauge->SetType(OBJECT_TYPE_GAUGE_LIFE); //�^�C�v�ݒ�
		break;
	default:
		assert(false);
		break;
	}

    // null�Ȃ�null��Ԃ�
    if (pGauge == nullptr) { return nullptr; }

    pGauge->SetPos(pos); //pos�ݒ�

    pGauge->SetSize(size); //size�ݒ�

	pGauge->m_type = type; //�Q�[�W�̃^�C�v�ݒ�

	pGauge->m_col = col; //�J���[�ݒ�

    //pGauge->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

    pGauge->Init();

	return pGauge;
}

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_Slash::CGauge_Slash(int nPriority):CGauge(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_Slash::~CGauge_Slash()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_Slash::Init()
{
	//�e�N���X�̏�����
	CGauge::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Slash::Uninit()
{
	//�e�N���X�̏I��
	CGauge::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Slash::Update()
{
	//�e�N���X�̍X�V
	CGauge::Update();

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

				if (GetSize().x <= MAX_GAUGE_WIDE && pPlayer->m_OldPress != true &&pPlayer->m_Attack != CPlayer::PLAYER_ATTACK_MELEE)
				{//�ő�l�ȉ��ō��N���b�N������ĂȂ���������Z
					AddGauge();
				}
			}
		}
	}
}

//=============================================
//�`��
//=============================================
void CGauge_Slash::Draw()
{
	//�e�N���X�̕`��
	CGauge::Draw();
}

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_Life::CGauge_Life(int nPriority):CGauge(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_Life::Init()
{
	//�e�N���X�̏�����
	CGauge::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Life::Uninit()
{
	//�e�N���X�̏I��
	CGauge::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Life::Update()
{
	//�e�N���X�̍X�V
	CGauge::Update();
}

//=============================================
//�`��
//=============================================
void CGauge_Life::Draw()
{
	//�e�N���X�̕`��
	CGauge::Draw();
}

