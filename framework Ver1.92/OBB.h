#pragma once

//******************************
//
//�@�C���N���[�h
//
//******************************
#include "CollisionBase.h"
#include <list>


//*******************************
//
// �N���X��`
//
//*******************************
class COBB :
	public CCollisionBase
{
	///////////////////////////
	// �����o�ϐ�
	//////////////////////////
private:
	COBB*		m_Next;		//����OBB

	//////////////////////////
	//�@�����o�֐�
	//////////////////////////
public:
	COBB();
	virtual ~COBB();
	bool Collision(CCollisionBase* Opponent);							//�����蔻��
	COBB*	GetNext() { return m_Next; };								//����OBB���擾
	void	SetNext(COBB* Next) { m_Next = Next; };						//����OBB���擾
	void	Draw();														//�`��i�f�o�b�N�`��j

};

