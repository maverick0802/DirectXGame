#pragma once

//******************************
//
//�@�C���N���[�h
//
//******************************
#include "CollisionBase.h"
#include <list>


//******************************
//
//�@�萔��`
//
//******************************

//******************************
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
	const D3DXCOLOR DEFAULTCOLOR = D3DXCOLOR(255,   0, 0, 100);
	const D3DXCOLOR HITCOLOR	 = D3DXCOLOR(  0, 255, 0, 100);

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

