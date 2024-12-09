//=============================================
//
//�Q�[�W�t���[���Ǘ�[gauge_fream.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "manager.h"
#include "gauge.h"

//tex�p�X
const std::string CGauge_Fream::TEXTURE_NAME = "data\\TEXTURE\\slashgauge_frame.png";

//=============================================
//�R���X�g���N�^
//=============================================
CGauge_Fream::CGauge_Fream(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge_Fream::~CGauge_Fream()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge_Fream::Init()
{
    //�e�N���X�̏��������Ă�
    CObject2D::Init();

    //�e�N�X�`�����W�ݒ�
    SetTexPos(D3DXVECTOR2(1.0f,1.0f));

    //���_�ݒ�
    SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

    //�Q�[�W����
    CGauge::Create(D3DXVECTOR3(GetPos().x - GetSize().x * 0.5f,GetPos().y - 10.0f,GetPos().z),D3DXVECTOR2(0.0f, 30.0f),CGauge::GAUGE_TYPE_SLASH,D3DXCOLOR(1.0f,0.5f,0.0f,1.0f));

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge_Fream::Uninit()
{
    //�e�N���X�̏I���Ă�
    CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge_Fream::Update()
{
    //�e�N���X�̍X�V�Ă�
    CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CGauge_Fream::Draw()
{
    //�e�N���X�̕`��Ă�
    CObject2D::Draw();
}

//=============================================
//����
//=============================================
CGauge_Fream* CGauge_Fream::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CGauge_Fream* pGauge_Fream = new CGauge_Fream;

    // null�Ȃ�null��Ԃ�
    if(pGauge_Fream == nullptr) {return nullptr;}

    pGauge_Fream->SetPos(pos); //pos�ݒ�

    pGauge_Fream->SetSize(size); //size�ݒ�

    pGauge_Fream->SetType(OBJECT_TYPE_GAUGE_FREAM); //�^�C�v�ݒ�

    pGauge_Fream->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�

    pGauge_Fream->Init(); //����������

    return pGauge_Fream;
}
