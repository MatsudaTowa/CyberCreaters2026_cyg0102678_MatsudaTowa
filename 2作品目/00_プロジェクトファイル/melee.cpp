//=============================================
//
//�ߐڍU��[melee.h]
//Auther Matsuda Towa
//
//=============================================
#include "melee.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"

const std::string CMelee::TEXTURE_NAME = "data\\TEXTURE\\melee_effect.png";

//=============================================
//�R���X�g���N�^
//=============================================
CMelee::CMelee(int nPriority) :CAttack_Manager(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMelee::~CMelee()
{
}

//=============================================
//������
//=============================================
HRESULT CMelee::Init()
{
	//�e�N���X�̏�����
	CAttack_Manager::Init();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CMelee::Uninit()
{
	//�e�N���X�̏I��
	CAttack_Manager::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMelee::Update()
{
	//�e�N���X�̍X�V
	CAttack_Manager::Update();

	//�̗͎擾
	int nLife = GetLife();

	if (nLife > 0)
	{//���C�t������Ώ������s

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);

			if (pObj != nullptr)
			{//�k���|�C���^����Ȃ����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pPlayer = (CPlayer*)pObj;

					//�������g��pos�擾
					D3DXVECTOR3 pos = GetPos();

					//�v���C���[��pos�������ɑ��
					pos.y = pPlayer->GetPos().y + pPlayer->GetMaxPos().y * 0.5f;
					pos.z = pPlayer->GetPos().z;

					if (pPlayer->GetWay() == true)
					{//�E�����Ă�Ȃ�
						pos.x = pPlayer->GetPos().x + pPlayer->GetMaxPos().x;
					}
					else if (pPlayer->GetWay() == false)
					{//�������Ă�Ȃ�
						pos.x = pPlayer->GetPos().x + pPlayer->GetMinPos().x;
					}
					//pos����
					SetPos(pos);
				}
			}

		}

		//�����蔻��`�F�b�N�ϐ�
		bool bHitCheck = false; 

		//�G�Ƃ̓����蔻��
		bHitCheck = HitEnemy();

		if (bHitCheck == true)
		{
			Uninit();
			return;
		}

		//�u���b�N�Ƃ̓����蔻��
		bHitCheck = HitBlock();

		if (bHitCheck == true)
		{
			Uninit();
			return;
		}
	}
	else
	{
		//�I��
		Uninit();
		return;
	}
}

//=============================================  
//�`��
//=============================================
void CMelee::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//�ߐڍU���쐬
//=============================================
CMelee* CMelee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,int nDamage)
{
	CMelee* pMelee = new CMelee;
	//null�Ȃ�null��Ԃ�
   if(pMelee ==nullptr) {return nullptr;}

   CTexture* pTexture = CManager::GetTexture();

   pMelee->SetPos(pos); //pos�ݒ�
   pMelee->SetSize(size); //�T�C�Y�ݒ�
   pMelee->SetRot(rot); //�����ݒ�
   pMelee->SetLife(nLife); //�������
   pMelee->SetDamage(nDamage); //�_���[�W���
   pMelee->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���̐ݒ�
   pMelee->SetType(OBJECT_TYPE_MELEE); //�^�C�v�ݒ�

   pMelee->Init(); //������

   return pMelee;
 }
