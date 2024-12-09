//=============================================
//
//�G�̏���[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "player.h"
#include "effect.h"
#include "bullet.h"
#include "item.h"
#include "flow.h"
#include "score.h"
#include "game.h"
#include"sound.h"

//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 0.3f;
//�ړ���R
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//�G�l�~�[��j���������W
const float CEnemy::DEADZONE_Y = -100.0f;

//���f���p�X
const std::string CEnemy::MODEL_NAME = "data\\MODEL\\enemy_test.x";

//���f���p�X
const std::string CEnemy::FLOW_MODEL_NAME = "data\\MODEL\\flowenemy_test.x";

//���f���p�X
const std::string CEnemy::FLY_MODEL_NAME = "data\\MODEL\\jett.x";

//���f���p�X
const std::string CEnemy::BOSS_MODEL_NAME = "data\\MODEL\\boss.x";

const std::string CEnemy::TUTORIAL_MODEL_NAME = "data\\MODEL\\tutorial_enemy.x";

//�X�e�[�g�؂�ւ��t���[��
const int CEnemy::STATE_FRAME = 30;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy::m_pMesh = nullptr;

DWORD CEnemy::m_dwNumMat = 0;

//�G�l�~�[�̑���
int CEnemy::m_nNumEnemy = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority):CCharacter(nPriority), m_bLockOn(false)
{
	//�������Z
	m_nNumEnemy++;
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
	//�������炷
	m_nNumEnemy--;
}

//=============================================
//������
//=============================================
HRESULT CEnemy::Init()
{
	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�u�l���
	SetMove(move);

#ifdef _DEBUG
	//�����蔻�����
	m_pColisionView = CColision_View::Create(GetPos(), GetMinPos(), GetMaxPos(), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
#endif

	m_pLockOn = nullptr;
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy::Uninit()
{
#ifdef _DEBUG
	if (m_pColisionView != nullptr)
	{//�������ꂽ�����蔻��j��
		m_pColisionView->Uninit();
		m_pColisionView = nullptr;
	}
#endif // _DEBUG

	if (m_pLockOn != nullptr)
	{
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
	}
	
	//�e�N���X�̏I��
	CCharacter::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy::Update()
{
	if (m_Type != CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS && m_Type != CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLY)
	{//��ԓz�ȊO�Ȃ�
		//�d�͏���
		Gravity();
	}

	//�ړ�����
	EnemyMove();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ߋ��̈ʒu
	D3DXVECTOR3 oldpos = GetOldPos();

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//��Ԏ擾
	CCharacter::CHARACTER_STATE state = GetState();

	
	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//��Ԃ̃J�E���g���擾
		int nStateCnt = GetStateCnt();

		//�X�e�[�g�ύX�J�E���g�i�߂�
		nStateCnt++;

		if (nStateCnt >= STATE_FRAME)
		{
			//�ʏ�ɖ߂�
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//�X�e�[�g�J�E���g���Z�b�g
			nStateCnt = 0;

			//��ԑ��
			SetState(state);
		}

		//�X�e�[�g�J�E���g���
		SetStateCnt(nStateCnt);
	}

	//�ړ��ʂ��X�V(�����j
	move *= 1.0f - DAMPING_COEFFICIENT;

	SetMove(move);

	oldpos = pos;

	//�ߋ��̈ʒu���
	SetOldPos(oldpos);

	pos += move;

	//���W���X�V
	SetPos(pos);

#ifdef _DEBUG
	//�������ꂽ�����蔻��𓮂���
	m_pColisionView->SetPos(pos);
#endif
	
	if(m_pLockOn != nullptr)
	{//�Ə����G�l�~�[�ɍ��킹�ē�����
		m_pLockOn->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
	}

	//�v���C���[�Ƃ̐ڐG����
	HitPlayer();

	//�G�l�~�[�Ƃ̐ڐG����
	HitEnemy();

	//�u���b�N�Ƃ̐ڐG����
	HitBlock();

	//���Ƃ̐ڐG����
	HitField();

	if (pos.y < DEADZONE_Y)
	{//�j������
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CEnemy::Draw()
{
	//�e�N���X�̕`��
	CCharacter::Draw();
}

//=============================================
//����
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
		break;
	case ENEMY_TYPE_FLOW:
		pEnemy = new CFlowEnemy;
		break;
	case ENEMY_TYPE_FLY:
		pEnemy = new CFlyEnemy;
		break;
	case ENEMY_TYPE_BOSS:
		pEnemy = new CBossEnemy;
		break;
	case ENEMY_TYPE_TUTORIAL:
		pEnemy = new CTutorialEnemy;
		break;
	default:
		break;
	}

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type; //�G�l�~�[�̃^�C�v�ݒ�

	pEnemy->SetPos(pos); //pos�ݒ�
	pEnemy->SetRot(rot); //rot�ݒ�
	pEnemy->SetType(OBJECT_TYPE_ENEMY); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	//���f�����擾
	CModel* pModel = CManager::GetModel();

	switch (pEnemy->m_Type)
	{
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
		//X�t�@�C���ǂݍ���
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat, //�}�e���A���擾
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat, //�}�e���A�����擾
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh); //���b�V�����擾
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW:
		//X�t�@�C���ǂݍ���
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).pBuffMat, //�}�e���A���擾
			pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).dwNumMat, //�}�e���A�����擾
			pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).pMesh); //���b�V�����擾
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLY:
		//X�t�@�C���ǂݍ���
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&FLY_MODEL_NAME)).pBuffMat, //�}�e���A���擾
			pModel->GetModelInfo(pModel->Regist(&FLY_MODEL_NAME)).dwNumMat, //�}�e���A�����擾
			pModel->GetModelInfo(pModel->Regist(&FLY_MODEL_NAME)).pMesh); //���b�V�����擾
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
		//X�t�@�C���ǂݍ���
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).pBuffMat, //�}�e���A���擾
			pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).dwNumMat, //�}�e���A�����擾
			pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).pMesh); //���b�V�����擾
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_TUTORIAL:
		//X�t�@�C���ǂݍ���
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&TUTORIAL_MODEL_NAME)).pBuffMat, //�}�e���A���擾
			pModel->GetModelInfo(pModel->Regist(&TUTORIAL_MODEL_NAME)).dwNumMat, //�}�e���A�����擾
			pModel->GetModelInfo(pModel->Regist(&TUTORIAL_MODEL_NAME)).pMesh); //���b�V�����擾
		break;
	default:
		break;
	}

	pEnemy->Init(); //�G�l�~�[�̏���������

	return pEnemy;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CEnemy::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//�_���[�W��ԈȊO��HP���c���Ă���
		nLife -= nDamage;

		if (nLife < 0)
		{
			nLife = 0;
		}

		//�_���[�W��ԂɕύX
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//��ԑ��
		SetState(state);

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//�j��
		//CItem* pItem = nullptr;

		CSound* pSound = CManager::GetSound();

		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SLASH);

		switch (m_Type)
		{
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
			/*pItem = */CItem::Create(CItem::ITEMTYPE_PANETRARING_SLASH, D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), GetRot());
			break;
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW:
			/*pItem = */CItem::Create(CItem::ITEMTYPE_FLOW, D3DXVECTOR3(GetPos().x, GetPos().y + 10.0f, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), GetRot());
			break;

		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLY:
			break;

		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
			break;
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_TUTORIAL:
			CEnemy::Create(D3DXVECTOR3(-200.0f,10.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_TUTORIAL);
			break;
		default:
			assert(false);
			break;
		}
		
		if (m_pLockOn != nullptr)
		{//�Ə��j��
			m_pLockOn->Uninit();
			m_pLockOn = nullptr;
			m_bLockOn = false;
		}

		if (m_Type == CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS)
		{
			CBossEnemy::m_BossDeath = true;
			//CManager::SetMode(CScene::MODE::MODE_RESULT);
		}

		return;
	}
}

//=============================================
//�v���C���[�Ƃ̋����𑪂�
//=============================================
bool CEnemy::PlayerDistance()
{
	bool bNear = false; //�߂�������true��Ԃ�

	bool bWay = GetWay(); //�������擾

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

				float fDistance = 0.0f; //�v���C���[�Ƃ̋���
				
				fDistance = GetPos().x - pPlayer->GetPos().x;

				if (fDistance >= 0.0f && fDistance < 150.0f)
				{//�G�l�~�[��min�ɋ߂�
					bNear = true;
					
					bWay = false; //�������v���C���[�̂ق��ɐ؂�ւ���
				}
				else if (fDistance <= 0.0f && fDistance > -150.0f)
				{//�G�l�~�[��max�ɋ߂�
					bNear = true;

					bWay = true; //�������v���C���[�̂ق��ɐ؂�ւ���
				}
				else
				{//�߂��Ȃ�
					bNear = false;
				}
			}
		}
	}
	//��������
	SetWay(bWay);
	return bNear;
}

//=============================================
//lock-on����
//=============================================
void CEnemy::LockOn()
{
	if (m_bLockOn != true)
	{
		m_pLockOn = CLockOn::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bLockOn = true;
}

//=============================================
//�W���a�����Ə��ɍ��킹�ďo��
//=============================================
void CEnemy::LockOn_Flow()
{
	if (m_pLockOn != nullptr)
	{
		int nFlowLife = 0;
		if (m_pLockOn->GetSize().x <= m_pLockOn->MIN_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE)
		{//�ŏ��_���[�W�̂Ƃ�
			nFlowLife = 30;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//���_���[�W�̂Ƃ�
			nFlowLife = 60;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//���_���[�W�̂Ƃ�
			nFlowLife = 120;
		}
		CFlow::Create(D3DXVECTOR3(m_pLockOn->GetPos().x, m_pLockOn->GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(10.0f, 10.0f, 0.0f), nFlowLife,1,CFlow::FLOW_TYPE::FLOW_TYPE_PLAYER);
		CSound* pSound = CManager::GetSound();

		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_FLOW);
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}
}

//=============================================
//�R���X�g���N�^
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority),m_nTurnFrameCnt(0), m_bOldWay(false), m_nShotCnt(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CNormalEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();

	m_pAttackEffect = nullptr;

	if (m_pAttackEffect == nullptr)
	{//��������ĂȂ�������
		m_pAttackEffect = CAttack_Effect::Create(GetPos(), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	SetLife(ENEMY_NORMAL_LIFE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CNormalEnemy::Uninit()
{
	if (m_pAttackEffect != nullptr)
	{
		//m_pAttackEffect->Uninit();
		m_pAttackEffect->SetSize(D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_pAttackEffect = nullptr;
	}
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CNormalEnemy::Update()
{
	//�e�N���X�̍X�V
	CEnemy::Update();


	if (m_pAttackEffect != nullptr)
	{//�G�t�F�N�g���G�l�~�[�ɍ��킹�ē�����
		m_pAttackEffect->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
	}

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//�߂�������
		//�������擾
		bool bWay = GetWay();

		//�V���b�g�J�E���g���Z
		m_nShotCnt++;

		if (m_pAttackEffect != nullptr)
		{
			//�T�C�Y�ύX
			m_pAttackEffect->SizeChange(((float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));
		}

		if (m_nShotCnt >= NORMAL_SHOT_FRAME)
		{//�t���[�����ɒB������

			//�e����
			ShotBullet(GetPos(),2.0f, D3DXVECTOR3(6.0f, 12.0f, 0.0f), bWay, 1, CBullet::BULLET_ALLEGIANCE_ENEMY,CBullet::BULLET_TYPE_PANETRARING_SLASH);

			//�G�t�F�N�g�T�C�Y���Z�b�g
			if (m_pAttackEffect != nullptr)
			{
				//�T�C�Y�ύX
				m_pAttackEffect->SizeReset();
			}

			//�V���b�g�J�E���g���Z�b�g
			m_nShotCnt = 0;
		}
	}
	else if (bDistance == false)
	{
		if (m_pAttackEffect != nullptr)
		{
			//�T�C�Y�ύX
			m_pAttackEffect->SizeChange(((float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));
		}
		//�V���b�g�J�E���g�_�E��
		if (m_nShotCnt > 0)
		{
			m_nShotCnt--;
		}
	}
}

//=============================================
//�`��
//=============================================
void CNormalEnemy::Draw()
{
	//�e�N���X�̕`����Ă�
	CEnemy::Draw();
}

//=============================================
//�ړ�����
//=============================================
void CNormalEnemy::EnemyMove()
{
	//�J�E���g���Z
	m_nTurnFrameCnt++;

	//�������擾
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//�ߋ��̌����ƈ������t���[�����Z�b�g
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= NORMAL_ENEMY_TURNFRAME)
	{//�w��t���[�����ɓ��B������

		//�i�ޕ�����؂�ւ���
		bWay = bWay ? false : true;
		SetWay(bWay);

		//�ߋ��̌����ɍ��̌�������
		m_bOldWay = bWay;
		//�J�E���g���Z�b�g
		m_nTurnFrameCnt = 0;
	}

	//�ړ��p�P�ʃx�N�g��������
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//�E�����ɐi�ނȂ�
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//�������ɐi�ނȂ�
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
	}

	rot.y = rotMoveY + D3DX_PI;

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = false;

	bDistance = PlayerDistance();

	SetRot(rot); //rot����

	//if (bDistance == false)
	{
		SetMove(move);//�ړ��ʑ��
	}

	//���n���Ă邩���
	SetLanding(bLanding);
}

//=============================================
//�R���X�g���N�^
//=============================================
CFlowEnemy::CFlowEnemy(int nPriority) :CEnemy(nPriority), m_nTurnFrameCnt(0), m_bOldWay(false), m_bLockOnShot(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFlowEnemy::~CFlowEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CFlowEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();
	SetLife(ENEMY_FLOW_LIFE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFlowEnemy::Uninit()
{
	if (m_bLockOnShot == true)
	{
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

					pPlayer->Delete_LockOn();
				}
			}
		}
	}
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFlowEnemy::Update()
{
	//�e�N���X�̍X�V
	CEnemy::Update();

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//�߂�������
		//�������擾
		bool bWay = false;
		bWay = GetWay();
		m_bLockOnShot = true;

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

					pPlayer->LockOn();

					pPlayer->LockOn_ChangeSize((1.0f- (float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));

					//�V���b�g�J�E���g���Z
					m_nShotCnt++;

					if (m_nShotCnt >= NORMAL_SHOT_FRAME)
					{//�t���[�����ɒB������
						//�e����

						if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
						{
							pPlayer->LockOn_Flow();
						}

						//�V���b�g�J�E���g���Z�b�g
						m_nShotCnt = 0;
					}

				}
			}
		}
	}
	else if(bDistance == false)
	{
		if (m_bLockOnShot == true)
		{
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

						pPlayer->Delete_LockOn();
					}
				}
			}
		}
		//�V���b�g�J�E���g�_�E��
		if (m_nShotCnt >= 0)
		{
			m_nShotCnt--;
		}
	}
}

//=============================================
//�`��
//=============================================
void CFlowEnemy::Draw()
{
	//�e�N���X�̕`��
	CEnemy::Draw();
}

//=============================================
//�ړ�����
//=============================================
void CFlowEnemy::EnemyMove()
{
	//�J�E���g���Z
	m_nTurnFrameCnt++;

	//�������擾
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//�ߋ��̌����ƈ������t���[�����Z�b�g
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= FLOW_ENEMY_TURNFRAME)
	{//�w��t���[�����ɓ��B������

		//�i�ޕ�����؂�ւ���
		bWay = bWay ? false : true;
		SetWay(bWay);

		//�ߋ��̌����ɍ��̌�������
		m_bOldWay = bWay;
		//�J�E���g���Z�b�g
		m_nTurnFrameCnt = 0;
	}

	//�ړ��p�P�ʃx�N�g��������
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//�E�����ɐi�ނȂ�
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//�������ɐi�ނȂ�
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveY) * 0.0f;
		move.z += cosf(rotMoveY) * 0.0f;
	}
	rot.y = rotMoveY + D3DX_PI;

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	SetRot(rot); //rot����

	if (bDistance == false)
	{
		SetMove(move);//�ړ��ʑ��
	}

	//���n���Ă邩���
	SetLanding(bLanding);
}

//=============================================
//�R���X�g���N�^
//=============================================
CFlyEnemy::CFlyEnemy(int nPriority):CEnemy(nPriority), m_nShotCnt(0), m_nTurnFrameCnt(0), m_bOldWay(false), m_bLockOnShot(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFlyEnemy::~CFlyEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CFlyEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();
	SetLife(ENEMY_FLY_LIFE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFlyEnemy::Uninit()
{
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFlyEnemy::Update()
{
	//�e�N���X�̍X�V
	CEnemy::Update();
}

//=============================================
//�`��
//=============================================
void CFlyEnemy::Draw()
{
	//�e�N���X�̕`��
	CEnemy::Draw();
}

//=============================================
//�ړ�
//=============================================
void CFlyEnemy::EnemyMove()
{
	//�J�E���g���Z
	m_nTurnFrameCnt++;

	//�������擾
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//�ߋ��̌����ƈ������t���[�����Z�b�g
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= FLY_ENEMY_TURNFRAME)
	{//�w��t���[�����ɓ��B������

		//�i�ޕ�����؂�ւ���
		bWay = bWay ? false : true;
		SetWay(bWay);

		//�ߋ��̌����ɍ��̌�������
		m_bOldWay = bWay;
		//�J�E���g���Z�b�g
		m_nTurnFrameCnt = 0;
	}

	//�ړ��p�P�ʃx�N�g��������
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//�E�����ɐi�ނȂ�
		vecDirection.x += 0.0f;
		vecDirection.y += 1.0f;
	}
	else if (bWay == false)
	{//�������ɐi�ނȂ�
		vecDirection.x -= 0.0f;
		vecDirection.y -= 1.0f;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveZ = atan2f(vecDirection.x, vecDirection.y);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveZ) * DEFAULT_MOVE * 0.5f;
		move.y += cosf(rotMoveZ) * DEFAULT_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveZ) * DEFAULT_MOVE;
		move.y += cosf(rotMoveZ) * DEFAULT_MOVE;
	}
	rot.y = rotMoveZ + D3DX_PI;

	SetRot(rot); //rot����


	SetMove(move);//�ړ��ʑ��
}

////�ʏ�̈ړ����x
//const float CBossEnemy::DEFAULT_MOVE_Y = 0.5f;

//�e�𐶐�����~���̔��a
const float CBossEnemy::CREATE_RADIUS = 35.0f;
const float CBossEnemy::BOSS_MOVE = 0.35f;

bool CBossEnemy::m_BossDeath = false;

//=============================================
//�R���X�g���N�^
//=============================================
CBossEnemy::CBossEnemy(int nPriority):CEnemy(nPriority), m_nTurnFrameCnt(0), m_nNumBullet(0),m_bOldWay(false), m_bShot(false), m_nShotCnt(0)
{
	m_BossDeath = false;
}

//=============================================
//�f�X�g���N�^
//=============================================
CBossEnemy::~CBossEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CBossEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();
	SetLife(ENEMY_BOSS_LIFE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBossEnemy::Uninit()
{
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBossEnemy::Update()
{
	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//�߂�������
		//�e�N���X�̍X�V
		CEnemy::Update();

		//�������擾
		bool bWay = false;
		bWay = GetWay();

		//�V���b�g�J�E���g���Z
		m_nShotCnt++;

		if (m_nShotCnt >= BOSS_SHOT_FRAME)
		{//�t���[�����ɒB������
			if (m_nNumBullet < CBossEnemy::CREATE_BULLET  && m_bShot == false)
			{
				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�~�`�ɃX�|�[��������
				CreatePos.x = CREATE_RADIUS * sinf((D3DX_PI * 2.0f) * ((1.0f / CBossEnemy::CREATE_BULLET) * m_nNumBullet));
				CreatePos.y = CREATE_RADIUS * cosf((D3DX_PI * 2.0f) * ((1.0f / CBossEnemy::CREATE_BULLET) * m_nNumBullet));

				//�{�X�̈ʒu����ɂ���
				CreatePos += GetPos() + (GetMaxPos() * 0.5f);

				CElecBullet::ElecCreate(CreatePos,D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f),
				D3DXVECTOR3(10.0f, 10.0f, 0.0f), 60, 1, CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_ELECBULLET);

				m_nNumBullet++;
			}
			if (m_bShot == true)
			{
				m_nNumBullet--;
				if (m_nNumBullet <= 0)
				{
					m_nNumBullet = 0;
					m_bShot = false;
				}
			}

			if (m_nNumBullet >= CBossEnemy::CREATE_BULLET)
			{
				m_bShot = true;
			}

			//�V���b�g�J�E���g���Z�b�g
			m_nShotCnt = 0;
		}
	}
}

//=============================================
//�`��
//=============================================
void CBossEnemy::Draw()
{
	//�e�N���X�̕`��
	CEnemy::Draw();
}

//=============================================
//�ړ�����
//=============================================
void CBossEnemy::EnemyMove()
{
	//�J�E���g���Z
	m_nTurnFrameCnt++;

	//�������擾
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//�ߋ��̌����ƈ������t���[�����Z�b�g
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= BOSS_ENEMY_TURNFRAME)
	{//�w��t���[�����ɓ��B������

		//�i�ޕ�����؂�ւ���
		bWay = bWay ? false : true;
		SetWay(bWay);

		//�ߋ��̌����ɍ��̌�������
		m_bOldWay = bWay;
		//�J�E���g���Z�b�g
		m_nTurnFrameCnt = 0;
	}

	//�ړ��p�P�ʃx�N�g��������
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//�E�����ɐi�ނȂ�
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//�������ɐi�ނȂ�
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveY) * BOSS_MOVE * 0.5f;
		move.z += cosf(rotMoveY) * BOSS_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveY) * BOSS_MOVE;
		move.z += cosf(rotMoveY) * BOSS_MOVE;
	}
	rot.y = rotMoveY + D3DX_PI;

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	SetRot(rot); //rot����


	SetMove(move);//�ړ��ʑ��

	//���n���Ă邩���
	SetLanding(bLanding);
}

//=============================================
//�R���X�g���N�^
//=============================================
CTutorialEnemy::CTutorialEnemy(int nPriority)
{
}


//=============================================
//�f�X�g���N�^
//=============================================
CTutorialEnemy::~CTutorialEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorialEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();
	SetLife(ENEMY_NORMAL_LIFE);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorialEnemy::Uninit()
{
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTutorialEnemy::Update()
{
	//�e�N���X�̍X�V
	CEnemy::Update();
}

//=============================================
//�`��
//=============================================
void CTutorialEnemy::Draw()
{
	//�e�N���X�̕`��
	CEnemy::Draw();
}

void CTutorialEnemy::EnemyMove()
{
}
