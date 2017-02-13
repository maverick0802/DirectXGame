#include "CollisionManeger.h"


CCollisionBase::CCollisionBase() :
	m_Active(true),
	m_Hit(false),
	m_HitedObject(NULL),
	m_pWorld(NULL),
	m_Center(D3DXVECTOR3(0, 0, 0)),
	m_Box(D3DXVECTOR3(0, 0, 0)),
	m_Color(255,0,0,0.5f)
{
}


CCollisionBase::~CCollisionBase()
{


}


void CCollisionBase::OnActive()
{

	m_Active = true;

}


void CCollisionBase::OffActive()
{

	m_Active = false;

}


void CCollisionBase::SetHitedObject(CGameObject* SetObject)
{

	m_HitedObject = SetObject;

}

bool CCollisionBase::CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject)
{
	//int SelectLayer = 0x01;
	//int HitLayerNumber = HitLayer;
	//D3DXVECTOR3 a;
	//std::list<CCollisionBase*>* List;
	//while (HitLayerNumber != 0)
	//{
	//	if (HitLayerNumber & 0x01)
	//	{
	//		if (CCollisionManeger::Instance()->GetCollisionList(SelectLayer, List))
	//		{
	//			auto Itr_s = List->begin();
	//			auto Itr_e = List->end();

	//			while (Itr_s != Itr_e)
	//			{

	//				HitObject = Collision(a, HitLayer, *Itr_s);

	//			}

	//		}
	//	}

	//	SelectLayer = SelectLayer << 1;
	//	HitLayerNumber = HitLayerNumber >> 1;
	//}

	return false;
}


///////////////////////////
// �����蔻��
///////////////////////////
bool CCollisionBase::Collision( CCollisionBase* Opponent)
{

	//�Ȃ񂩊�{�̂����蔻��ł��������Ƃ������ȁH

	return false;
}


///////////////////////////
// �{�b�N�X�̐ݒ�
///////////////////////////
void CCollisionBase::SetBox(D3DXVECTOR3 & Box)
{
	//Mesh�̏�����
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//�{�b�N�X�̐V�K�ݒ�
	m_Box = Box;
	HRESULT hr = D3DXCreateBox(*CDirectX3D::Create()->GetDevice(), m_Box.x * 2, m_Box.y * 2, m_Box.z * 2, &m_pMesh, NULL);

	//�����Ɏ��s������NULL���
	if (FAILED(hr))
		m_pMesh = NULL;


}


///////////////////////////
// �f�o�b�N�p�`��
///////////////////////////
void CCollisionBase::Draw()
{

	//�f�t�H���g�ł͉����`�悵�Ȃ�
	//�h����ŕ`���ς���

}