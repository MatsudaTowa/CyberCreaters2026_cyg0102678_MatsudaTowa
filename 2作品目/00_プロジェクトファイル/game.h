//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "edit.h"
#include "timer.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

class CGame:public CScene
{
public:

	typedef enum
	{
		GAME_STATE_NORMAL = 0,
		GAME_STATE_BOSS,
		GAME_STATE_MAX,
	}GAME_STATE;

	//�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	}LOAD_ENEMY;

	//�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}LOAD_BLOCK;

	static const std::string ENEMY_FILE;	//�G�l�~�[�̃t�@�C��
	static const std::string BLOCK_FILE;	//�G�l�~�[�̃t�@�C��
	static const int DELAY_CNT = 30; //���U���g�ɔ�Ԃ܂ł̃f�B���C
	static const int ENEMY_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	static const int BLOCK_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static void SetState(GAME_STATE state)
	{
		m_GameState = state;
	}

	static GAME_STATE&GetState();

	static CScore*GetScore();
	static CPlayer*GetPlayer();
private:
	int m_nResultDelay; //���U���g�ւ̃f�B���C
	bool m_bEdit; //�G�f�B�b�g���Ă邩�ǂ���
	static GAME_STATE m_GameState; //�Q�[���X�e�[�g
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	LOAD_BLOCK m_LoadBlock; //�ǂݍ��ނƂ��ɕK�v�ȃu���b�N�̏��
	static CEdit*m_pEdit;
	static CTimer*m_pTimer;
	static CScore*m_pScore;
	static CPlayer*m_pPlayer;

	void LoadEnemy(const std::string* pFileName);
	void LoadBlock(const std::string* pFileName);
};
#endif