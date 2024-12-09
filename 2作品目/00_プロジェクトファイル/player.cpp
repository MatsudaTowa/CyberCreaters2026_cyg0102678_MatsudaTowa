//=============================================
//
//�v���C���[����[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "field.h"
#include "camera.h"
#include "melee.h"
#include "game.h"
#include"renderer.h"
#include "flow_range.h"
#include "flow.h"
#include "scene.h"

//���f���p�X
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 1.0f;

//�ړ���R
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CPlayer::DEFAULT_JUMP = 30.0f;

//�W�����v��
const int CPlayer::MAX_JUMPCNT = 2;

//�X�e�[�g�؂�ւ��t���[��
const int CPlayer::STATE_FRAME = 60;

//�v���C���[�����X�|�[���������W
const float CPlayer::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;

//�ŏI�i�K
const int CPlayer::MAX_CHARGE = CGauge::MAX_GAUGE_WIDE / CHARGE_INTERVAL / SLASH_COST;

bool CPlayer::m_PlayerDeath = false;

//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority),m_nJumpCnt(0),m_OldPress(false), m_OldRelease(true), m_PressCnt(0),
m_ReleaseCnt(0),m_nChargeCnt(0),m_nSlashDamage(0), m_bFlow(false)
{//�C�j�V�����C�U�[�Ŋe�����o�ϐ�������

	//�v���C���[�̍U�����ߋ����݂̂ɂ���
	m_Attack = PLAYER_ATTACK_MELEE;

	//�X�e�[�g��ʏ��
	SetState(CCharacter::CHARACTER_STATE::CHARACTER_NORMAL);

	//����łȂ���Ԃ�
	m_PlayerDeath = false;

	//�a���̏����T�C�Y
	m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//�Q�[�W����
	CGauge* pGauge = CGauge::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR2(500.0f, 30.0f), CGauge::GAUGE_TYPE_LIFE, D3DXCOLOR(0.0f, 0.7f, 0.3f, 1.0f));
	
	//���[�u�l���
	SetMove(move);

	m_pItemUI = nullptr;

	if (m_pItemUI == nullptr)
	{
		m_pItemUI = CItem_UI::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}

	m_pLockOn = nullptr;

	return S_OK;
}

//=============================================
//������(�Z�b�g�p)
//=============================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	SetPos(pos); //pos�ݒ�
	SetRot(rot); //rot�ݒ�
	SetLife(nLife); //�̗͑��

	//x�t�@�C���ǂݍ���
	BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�V�[���̃|�C���^�擾
	CScene* pScene = CManager::GetScene();

	//CScene::MODE mode = pScene->GetSceneMode();

	//���[�u�l���
	SetMove(move);

	m_pItemUI = nullptr;

	if (m_pItemUI == nullptr)
	{
		m_pItemUI = CItem_UI::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f));
	}

	m_pLockOn = nullptr;

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CObjectX::Uninit();

}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	//SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//���݂̃V�[�����擾
	CScene::MODE pScene = CScene::GetSceneMode();

	if (pScene != CScene::MODE::MODE_TITLE)
	{
		//��Ԃ��擾
		CCharacter::CHARACTER_STATE state = GetState();

		if (m_pItemUI != nullptr)
		{
			switch (m_Attack)
			{
			case CPlayer::PLAYER_ATTACK_MELEE:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_NONE);
				break;
			case CPlayer::PLAYER_ATTACK_PANETRARING_SLASH:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_PANETRARING_SLASH);

				for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
				{
					//�I�u�W�F�N�g�擾
					CObject* pObj = CObject::Getobject(CFlow_Range::FLOW_RANGE_PRIORITY, nCnt);
					if (pObj != nullptr)
					{//�k���|�C���^����Ȃ����
						//�^�C�v�擾
						CObject::OBJECT_TYPE type = pObj->GetType();

						//�G�Ƃ̓����蔻��
						if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FLOW_RANGE)
						{
							CFlow_Range* pFlow_Range = (CFlow_Range*)pObj;

							if (pFlow_Range != nullptr)
							{
								pFlow_Range->Uninit();
							}
						}
					}
				}
				m_bFlow = false;
				break;
			case CPlayer::PLAYER_ATTACK_FLOW:
				m_pItemUI->SetTex(CItem_UI::ITEM_UI_TYPE_FLOW);
				break;
			default:
				break;
			}
		}


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

		//�d�͏���
		Gravity();

		if (m_bFlow == false)
		{
			//�ړ�����
			PlayerMove();
		}
		//�ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		//�ߋ��̈ʒu
		D3DXVECTOR3 oldpos = GetOldPos();

		//�ړ��ʎ擾
		D3DXVECTOR3 move = GetMove();

		//�ړ��ʂ��X�V(�����j
		move *= 1.0f - DAMPING_COEFFICIENT;

		//�ړ��ʑ��
		SetMove(move);

		//�ߋ��̈ʒu�ɍ��̈ʒu����
		oldpos = pos;

		//�ߋ��̈ʒu���
		SetOldPos(oldpos);

		//�ړ��ʒǉ�
		pos += move;

		//���W���X�V
		SetPos(pos);

		if (m_pLockOn != nullptr)
		{//�Ə����G�l�~�[�ɍ��킹�ē�����
			m_pLockOn->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
		}

		//�ő�ŏ��l�擾
		D3DXVECTOR3 minpos = GetMinPos();
		D3DXVECTOR3 maxpos = GetMaxPos();

		if (pScene == CScene::MODE::MODE_TUTORIAL)
		{
			if (GetOldPos().x < -180.0f
				&& GetPos().x > -180.0f)
			{
				SetPos(D3DXVECTOR3(GetOldPos().x, GetPos().y, GetPos().z));
				SetMove(D3DXVECTOR3(0.0f,GetMove().y,GetMove().z));
			}
		}

		//�u���b�N�Ƃ̐ڐG����
		HitBlock();

		//���Ƃ̐ڐG����
		HitField();

		//�G�l�~�[�Ƃ̐ڐG����
		HitEnemy();

		//�Q�[���̏�Ԏ擾
		CGame::GAME_STATE Game_state = CGame::GetState();

		if (pScene == CScene::MODE::MODE_GAME &&Game_state == CGame::GAME_STATE::GAME_STATE_NORMAL && GetPos().x > CCharacter::BOSS_FIELD_X)
		{//�{�X���ԂɈڍs
			Game_state = CGame::GAME_STATE::GAME_STATE_BOSS;

			CSound* pSound = CManager::GetSound();
			//�T�E���h�̒�~
			pSound->StopSound();

			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME_BOSS);

			CGame::SetState(Game_state);

		}

		if (GetLaunding())
		{//���n���Ă�Ȃ�
			//�W�����v�����Z�b�g
			m_nJumpCnt = 0;
		}

		if (pos.y < DEADZONE_Y)
		{//���X�|�[������
			ReSpawn();
		}

		//�}�E�X�̏��擾
		CInputMouse* pMouse = CManager::GetMouse();
		CInputPad* pPad = CManager::GetPad();

		//�ǂ��������Ă邩�擾
		bool bWay = GetWay();

		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CGauge_Slash::GAUGE_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�k���|�C���^����Ȃ����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�G�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_GAUGE_SLASH)
				{
					CGauge_Slash* pGauge = (CGauge_Slash*)pObj;

					//�Q�[�W����
					Gauge(pGauge);
				}
			}
		}

		if (pMouse->GetTrigger(1) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_B))
		{//�E�N���b�N�����͂��ꂽ��
			//�ߐڍU������
			PerformMelee(pos, bWay);
		}
	}
}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	//�e�N���X�̕`����Ă�
	CCharacter::Draw();
}

//=============================================
//lock-on����
//=============================================
void CPlayer::LockOn()
{
	if (m_bLockOn != true)
	{
		m_pLockOn = CLockOn::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bLockOn = true;
}

//=============================================
//lock-on�T�C�Y�ύX
//=============================================
void CPlayer::LockOn_ChangeSize(float fRatioFrame)
{
	m_pLockOn->ChangeSize(fRatioFrame);
}

//=============================================
//�W���a�����Ə��ɍ��킹�ďo��
//=============================================
void CPlayer::LockOn_Flow()
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
			nFlowLife = 90;
		}
		CFlow* pFlow = CFlow::Create(D3DXVECTOR3(m_pLockOn->GetPos().x, m_pLockOn->GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(10.0f, 10.0f, 0.0f), nFlowLife, 1, CFlow::FLOW_TYPE::FLOW_TYPE_ENEMY);
	}
	Delete_LockOn();
}

//=============================================
//�Ə����폜
//=============================================
void CPlayer::Delete_LockOn()
{
	if (m_pLockOn != nullptr)
	{
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nLife)
{
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //rot�ݒ�
	pPlayer->SetLife(nLife); //�̗͑��

	//x�t�@�C���ǂݍ���
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	pPlayer->Init(); //����������
	
	return pPlayer;
}

//=============================================
//�_���[�W���󂯂��Ƃ�
//=============================================
void CPlayer::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	//��Ԃ��擾
	CCharacter::CHARACTER_STATE state = GetState();

	if (m_pLockOn != nullptr)
	{//�Ə��j��
		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}

	if (nLife > 0)
	{//HP���c���Ă���

		nLife -= nDamage;

		//�_���[�W��ԂɕύX
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//���݂̏�Ԃ���
		SetState(state);

		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CGauge_Life::GAUGE_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//�k���|�C���^����Ȃ����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();

				//�G�Ƃ̓����蔻��
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_GAUGE_LIFE)
				{
					CGauge_Life* pGauge = (CGauge_Life*)pObj;

					//�Q�[�W����
					pGauge->SubGauge(100);
				}
			}
		}

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//�I��
		Uninit();
		//���񂾏�Ԃ�
		m_PlayerDeath = true;
	}
}

//=============================================
//�Q�[�W����
//=============================================
void CPlayer::Gauge(CGauge* pGauge)
{
	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	//�}�E�X�̏��擾
	CInputMouse* pMouse = CManager::GetMouse();
	CInputPad* pPad = CManager::GetPad();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ђʎa��
	if (m_ReleaseCnt > SLASH_COOLTIME &&pGauge->GetSize().x > (float)SLASH_COST && m_Attack == PLAYER_ATTACK_PANETRARING_SLASH)
	{//�Q�[�W������U�����@���ђʎa����������
		if (pMouse->GetPress(0) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_X))
		{//���N���b�N��������Ă��
			//�Q�[�W����(��ɉ����ꂽ���Ԃɉ����ď���ʕύX)
			m_PressCnt++;
			if (m_PressCnt >= CHARGE_INTERVAL)
			{//�����ꂽ��T�C�Y����
				m_SlashSize.x += 1.0f;
				m_SlashSize.y += 4.0f;
				m_SlashSize.z += 0.0f;

				//�J�E���g���Z�b�g
				m_PressCnt = 0;

				m_nChargeCnt++;
			}

			//�Q�[�W����
			pGauge->SubGauge((float)SLASH_COST);

			//�L�[���͏��ύX
			m_OldPress = true;
			m_OldRelease = false;

		}
	}
	if ((pMouse->GetRelease(0) ||pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X)) && m_OldPress && m_Attack == PLAYER_ATTACK_PANETRARING_SLASH)
	{//���N���b�N�������ꂽ��
		if (m_nChargeCnt >= MAX_CHARGE)
		{//�}�b�N�X�`���[�W�ʂ�������
			m_nSlashDamage = 5;
		}
		else if (m_nChargeCnt >= MAX_CHARGE * 0.5f && m_nChargeCnt < MAX_CHARGE)
		{//�������ゾ������
			m_nSlashDamage = 3;
		}
		else
		{//����ȉ���������
			m_nSlashDamage = 1;
		}
		CSound* pSound = CManager::GetSound();

		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT);
		//�e����
		ShotBullet(pos,4.0f, m_SlashSize, bWay, m_nSlashDamage, CBullet::BULLET_ALLEGIANCE_PLAYER,CBullet::BULLET_TYPE_PANETRARING_SLASH);

		//�a���̃T�C�Y���Z�b�g
		m_SlashSize = D3DXVECTOR3(10.0f, 10.0f, 0.0f);

		//����������ĂȂ���Ԃ�
		m_OldPress = false;

		//��������Ԃ�
		m_OldRelease = true;

		//�J�E���g���Z�b�g
		m_PressCnt = 0;
		m_nChargeCnt= 0;
		//������Ă���̃J�E���g���Z�b�g
		m_ReleaseCnt = 0;
	}

	//�W���a��
	if (m_ReleaseCnt > SLASH_COOLTIME && pGauge->GetSize().x > SLASH_COST && (pMouse->GetTrigger(0) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_X)) && m_Attack == PLAYER_ATTACK_FLOW)
	{
		//�W����Ԃ͈̔͂̃|�C���^������
		CFlow_Range* pFlow_Range = nullptr;
		if (bWay == true)
		{//�E����
			pFlow_Range = CFlow_Range::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 70.0f, 0.0f));
		}
		else if (bWay == false)
		{//������
			pFlow_Range = CFlow_Range::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 70.0f, 0.0f));
		}
	}

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CFlow_Range::FLOW_RANGE_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FLOW_RANGE)
			{
				CFlow_Range* pFlow_Range = (CFlow_Range*)pObj;

				if (pGauge->GetSize().x > 0.0f && (pMouse->GetPress(0) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_X)) && (pFlow_Range->GetMaxPos().x < 300.0f || pFlow_Range->GetMinPos().x > -300.0f) && m_Attack == PLAYER_ATTACK_FLOW)
				{//���N���b�N��������Ă��
					pFlow_Range->SizeUp(GetWay());

					m_bFlow = true;

					//�Q�[�W����
					pGauge->SubGauge(SLASH_COST);

					//�L�[���͏��ύX
					m_OldPress = true;
					m_OldRelease = false;
				}
			}
		}
	}

	if (m_OldPress && (pMouse->GetRelease(0) || pPad->GetRelease(CInputPad::JOYKEY::JOYKEY_X)) && m_Attack == PLAYER_ATTACK_FLOW)
	{
		m_bFlow = false;
		m_OldPress = false;
		//��������Ԃ�
		m_OldRelease = true;
		//������Ă���̃J�E���g���Z�b�g
		m_ReleaseCnt = 0;
	}

	if (m_OldRelease)
	{//�����ꂽ��Ԃ̎�
		m_ReleaseCnt++;
	}
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-900.0f, 0.5f, 0.0f);

	//pos���
	SetPos(PlayerPos);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputPad* pPad = CManager::GetPad();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	switch (pCameraType)
	{//�T�C�h�r���[�̎��͉��ɂ��������Ȃ��悤�ɐݒ�
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_LEFT))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_RIGHT))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	default:
		if (pKeyboard->GetPress(DIK_W))
		{
			vecDirection.z += 1.0f;
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			vecDirection.z -= 1.0f;
		}
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//�ǂ��������Ă邩���
	SetWay(bWay);

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

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
		//rot����
		SetRot(rot);
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE) || pPad->GetTrigger(CInputPad::JOYKEY::JOYKEY_A))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //��
			m_nJumpCnt++; //�W�����v�����Z
		}
	}

	//�ړ��ʑ��
	SetMove(move);

	//���n���Ă邩���
	SetLanding(bLanding);

}

//=============================================
//�ߐڍU������
//=============================================
void CPlayer::PerformMelee(D3DXVECTOR3 pos, bool bWay)
{
	if (bWay == true)
	{//�E����
		CMelee::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y + 10.0f, pos.z),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30, MELEE_DAMAGE);
	}
	else if (bWay == false)
	{//������
		CMelee::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y + 10.0f, pos.z),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30, MELEE_DAMAGE);
	}
}

