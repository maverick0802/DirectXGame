#pragma once
#include "GameObject.h"

//////////////////////////////////////////////////////////
//�@�N���X��  :�@CCollisionBase
//�@�쐬��    :�@���Y�G�I
//�@�X�V����  :�@20161229 : �N���X��`
// ---------------------------------------------------------
//�@�`�ڍׁ`
// �����蔻��̊��N���X
///////////////////////////////////////////////////////////
class CCollisionBase
{
public:
	CCollisionBase();
	virtual ~CCollisionBase();

	virtual	bool CheckCollision(CGameObject*) = 0;
};

