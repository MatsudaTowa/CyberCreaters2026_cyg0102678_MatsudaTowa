//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player_test.h"
#include "bullet.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//�G�l�~�[�̃t�@�C��
const std::string CGame::ENEMY_FILE = "data\\FILE\\enemy.txt";
const std::string CGame::BLOCK_FILE = "data\\FILE\\block.txt";

//�G�f�B�b�g�ݒ�
CEdit* CGame::m_pEdit = nullptr;

//�^�C���ݒ�
CTimer* CGame::m_pTimer = nullptr;

//�X�R�A�ݒ�
CScore* CGame::m_pScore = nullptr;

//�v���C���[
CPlayer*CGame::m_pPlayer = nullptr;

CGame::GAME_STATE CGame::m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�G�f�B�b�g���ĂȂ���ԂɕύX

	//�ǂݍ��ރG�l�~�[�̏�񏉊���
	m_LoadEnemy.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.type = CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL;

	//�ǂݍ��ރu���b�N�̏�񏉊���
	m_LoadBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LoadBlock.type = CBlock::BLOCKTYPE::BLOCKTYPE_DEFAULT;
}

//=============================================
//�f�X�g���N�^
//=============================================
CGame::~CGame()
{
}

//=============================================
//������
//=============================================
HRESULT CGame::Init()
{

	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}

	//�^�C�}�[������
	if (m_pTimer == nullptr)
	{
		m_pTimer = new CTimer;

		m_pTimer->Init();
	}

	//�X�R�A������
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;

		m_pScore->Init();
	}

	m_GameState = CGame::GAME_STATE::GAME_STATE_NORMAL;

	////�u���b�N����
	//CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//�u���b�N����
	LoadBlock(&CGame::BLOCK_FILE);

	//�Q�[�W�̃t���[��UI����
	CGauge_Fream::Create(D3DXVECTOR3(250.0f,150.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//�v���C���[����
	//CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	//�G�l�~�[����
	LoadEnemy(&CGame::ENEMY_FILE);

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	m_GameState = GAME_STATE_NORMAL;
	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	CSound* pSound = CManager::GetSound();
	//�T�E���h�̒�~
	pSound->StopSound();

	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}

	if (m_bEdit)
	{
		m_pEdit->Update();
	}
	
	//if (m_bEdit == false)
	//{
	CObject::UpdateAll();

	if (m_pTimer != nullptr)
	{
		m_pTimer->Update();
	}
	//}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}
	if (CPlayer::m_PlayerDeath|| CBossEnemy::m_BossDeath || CEnemy::m_nNumEnemy <= 0)
	{//�v���C���[�����ʂ��G�l�~�[��S���E������
		//�J�E���g���Z
		m_nResultDelay++;
		if (m_nResultDelay >= DELAY_CNT)
		{
			//�f�B���C�J�E���g���Z�b�g
			m_nResultDelay = 0;

			m_pScore->SaveScore(m_pScore->m_nScore);

			//���U���g�J��
			CManager::SetMode(CScene::MODE::MODE_RESULT);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
	}
#endif // DEBUG


}

//=============================================
//�`��
//=============================================
void CGame::Draw()
{
}

//=============================================
//�X�R�A�擾
//=============================================
CScore* CGame::GetScore()
{
	return m_pScore;
}

//=============================================
//�v���C���[�擾
//=============================================
CPlayer* CGame::GetPlayer()
{
	return m_pPlayer;
}

CGame::GAME_STATE& CGame::GetState()
{
	return m_GameState;
}

//=============================================
//�G�̓ǂݍ���
//=============================================
void CGame::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[ENEMY_TXT_MAX];
	char aEqual[ENEMY_TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumEnemy; //�G�l�~�[�̐�

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}
	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//�G�l�~�[����
					CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CGame::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumBlock; //�u���b�N�̐�

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}
	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//�G�l�~�[����
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot,1,false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
