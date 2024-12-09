//=============================================
//
//�`���[�g���A��[tutorial.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "player_test.h"
#include "bullet.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "tutorial_UI.h"
#include "item.h"
#include "manager.h"
#include "sound.h"

const std::string CTutorial::ENEMY_FILE = "data\\FILE\\tutorial_enemy.txt";

const std::string CTutorial::BLOCK_FILE = "data\\FILE\\block.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CTutorial::CTutorial()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTutorial::~CTutorial()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorial::Init()
{
	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�Q�[�W�̃t���[��UI����
	CGauge_Fream::Create(D3DXVECTOR3(250.0f, 150.0f, 0.0f), D3DXVECTOR2(280.0f, 120.0f));

	//�u���b�N����
	LoadBlock(&CTutorial::BLOCK_FILE);
	//�G�l�~�[����
	LoadEnemy(&CTutorial::ENEMY_FILE);

	//�v���C���[����
	m_pPlayer = new CPlayer;
	m_pPlayer->Init(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	CTutorial_UI::Create(D3DXVECTOR3(-900.0f, 40.0f, 100.0f), D3DXVECTOR3(60.0f, 40.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE);
	CTutorial_UI::Create(D3DXVECTOR3(-700.0f, 40.0f, 100.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE);
	CTutorial_UI::Create(D3DXVECTOR3(-500.0f, 40.0f, 100.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH);

	CTutorial_UI::Create(D3DXVECTOR3(-300.0f, 40.0f, 100.0f), D3DXVECTOR3(60.0f, 40.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_GAUGE);

	CItem::Create(CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH, D3DXVECTOR3(-600.0f, 10.0f, 0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	CItem::Create(CItem::ITEMTYPE::ITEMTYPE_FLOW, D3DXVECTOR3(-550.0f, 10.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TUTORIAL);

	m_pSkipUI = CSkip_UI::Create(D3DXVECTOR3(200.0f,600.0f,0.0f),D3DXVECTOR2(150.0f,70.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorial::Uninit()
{
	CSound* pSound = CManager::GetSound();
	//�T�E���h�̒�~
	pSound->StopSound();
	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTutorial::Update()
{
	CObject::UpdateAll();
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	CInputPad* pPad = CManager::GetPad();

	//CFade*pFade= CFade::GetFade();
	if (pKeyboard->GetPress(DIK_RETURN) || pPad->GetPress(CInputPad::JOYKEY::JOYKEY_START))
	{
		m_pSkipUI->m_bPress = true; //�����Ă��Ԃ�
		m_pSkipUI->ColorChange();
		if (m_pSkipUI->m_col.r >= 1.0f && m_pSkipUI->m_col.g >= 1.0f && m_pSkipUI->m_col.b >= 1.0f)
		{
			//�X�L�b�vUI�̃����o�ϐ�������
			m_pSkipUI->m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			m_pSkipUI->m_bPress = false;
			CManager::SetMode(CScene::MODE::MODE_GAME);
		}
	}
	else
	{
		m_pSkipUI->m_bPress = false; //�����ĂȂ���Ԃ�
		m_pSkipUI->ColorChange();

	}
}

//=============================================
//�`��
//=============================================
void CTutorial::Draw()
{
}

void CTutorial::LoadEnemy(const std::string* pFileName)
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
void CTutorial::LoadBlock(const std::string* pFileName)
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
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
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
