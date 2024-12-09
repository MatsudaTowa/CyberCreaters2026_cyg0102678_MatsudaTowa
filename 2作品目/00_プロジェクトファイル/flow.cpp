//=============================================
//
//�W���a��[flow.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow.h"
#include "renderer.h"
#include"manager.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CFlow::m_pTextureTemp = nullptr;
const std::string CFlow::TEXTURE_NAME = "data\\TEXTURE\\flow_anim.png";

//=============================================
//�R���X�g���N�^
//=============================================
CFlow::CFlow(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFlow::~CFlow()
{
}

//=============================================
//������
//=============================================
HRESULT CFlow::Init()
{
	//�e�N���X�̏�����
	CAttack_Manager::Init();

	m_nDamageCnt = PLAYER_DAMAGE_FRAME; //�ŏ��Ƀq�b�g�����邽�߂Ƀ_���[�W�̃t���[��������

		//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//�e�N�X�`���ړ��ʑ��
	SetTexMove(tex_move);

	//�e�N�X�`�����W�擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);

	//�A�j���[�V�����t���[�����
	SetAnimFrame(ANIMATION_FRAME);

	//���_���W
	SetVtxAnim(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), tex_pos, tex_move);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFlow::Uninit()
{
	//�e�N���X�̏I��
	CAttack_Manager::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFlow::Update()
{
	//�e�N���X�̍X�V
	CAttack_Manager::Update();

	//�̗͎擾
	int nLife = GetLife();

	if (nLife > 0)
	{//���C�t������Ώ������s

		//�e�N�X�`�����擾
		D3DXVECTOR2 tex_pos = GetTexPos();
		D3DXVECTOR2 tex_move = GetTexMove();

		//���_���W
		SetVtxAnim(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.2f, 0.8f, 0.9f, 1.0f), tex_pos, tex_move);
		//�A�j���[�V������̃e�N�X�`�����W�擾
		tex_pos = GetTexPos();
		//�A�j���[�V�������J��Ԃ�
		if (tex_pos.x >= 1.0f)
		{
			tex_pos.x = 0.0f;
		}
		SetTexPos(tex_pos);

		//�����蔻��`�F�b�N�ϐ�
		bool bHitCheck = false;
		switch (m_type)
		{
		case FLOW_TYPE_PLAYER:
			m_nDamageCnt++;//�q�b�g�J�E���g�v��

			if (m_nDamageCnt >= ENEMY_DAMAGE_FRAME)
			{//�t���[�����ɓ��B������
				bHitCheck = HitEnemy();
				m_nDamageCnt = 0;
			}
			break;

		case FLOW_TYPE_ENEMY:
			
			m_nDamageCnt++;//�q�b�g�J�E���g�v��

			if(m_nDamageCnt >= PLAYER_DAMAGE_FRAME)
			{//�t���[�����ɓ��B������
				bHitCheck = HitPlayer();
				m_nDamageCnt = 0;
			}

			break;

		default:
			assert(false);
			break;
		}
	}
	else
	{
		//�I��
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CFlow::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//����
//=============================================
CFlow* CFlow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife, int nDamage , FLOW_TYPE type)
{
	CFlow* pFlow = new CFlow;

	if (pFlow == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pFlow->SetPos(pos); //pos�ݒ�
	pFlow->SetSize(size); //�T�C�Y�ݒ�
	pFlow->SetLife(nLife); //�������
	pFlow->SetDamage(nDamage); //�_���[�W���
	pFlow->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pFlow->m_type = type; //�e�̐ݒ�
	pFlow->SetType(OBJECT_TYPE_FLOW); //�^�C�v�ݒ�
	pFlow->Init();

	return pFlow;
}
