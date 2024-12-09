//=============================================
//
//�G�f�B�^�[[edit.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EDIT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _EDIT_H_

#include "main.h"
#include "block.h"
//=============================================
//�G�f�B�^�[�N���X
//=============================================
class CEdit
{
public:
	static const int BLOCK_MAX = 128; //�`�揇
	CEdit();
	~CEdit();

	void Init();

	void Update();

	void SetBlock(); //�u���b�N�̐ݒu
	void SaveBlock(); //�u���b�N�̕ۑ�
private:
	int m_nNumBlock; //�u���b�N�̐ݒu��

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	}EDIT_BLOCK_INFO;

	EDIT_BLOCK_INFO m_Edit_Block_Info;

	CBlock* m_EditBlockInfo;
};
#endif