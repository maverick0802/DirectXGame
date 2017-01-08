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


#include "GameObject.h"


////////////////////////////////////////////////
//
// �N���X��: CollisionBase
// �쐬�ҁ@: ���Y�@�G�I
// �ڍ�
//�@�����蔻��̊��N���X�B�����蔻���OnOff���̑����낢��
// ---------------------------------------------
// �X�V����:
// 20170101 �쐬
////////////////////////////////////////////////


class CCollisionBase
{
private:
	bool m_Active;						//�����蔻����Ƃ邩�Ƃ�Ȃ���
	bool m_Hit;							//����܂łɉ����������Ă��邩(����Ȃ�����)
	CGameObject*  m_HitedObject;		//���������I�u�W�F�N�g�̎Q��
	CGameObject*  m_ReferenceObject;	//���������Ă�I�u�W�F�N�g�̎Q��
public:
	CCollisionBase();
	virtual ~CCollisionBase();
	virtual CGameObject* Collision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CCollisionBase* HitObject);
	bool CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject);
	void OnActive();
	void OffActive();
	void SetHitedObject(CGameObject* SetObject);
};
