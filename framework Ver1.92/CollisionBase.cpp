#include "CollisionBase.h"
#include "CollisionManeger.h"


CCollisionBase::CCollisionBase() :
	m_Active(true),
	m_Hit(false),
	m_HitedObject(NULL)
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
	int SelectLayer = 0x01;
	int HitLayerNumber = HitLayer;
	D3DXVECTOR3 a;
	std::list<CCollisionBase*>* List;
	while (HitLayerNumber != 0)
	{
		if (HitLayerNumber & 0x01)
		{
			if (CCollisionManeger::Instance()->GetCollisionList(SelectLayer, List))
			{
				auto Itr_s = List->begin();
				auto Itr_e = List->end();

				while (Itr_s != Itr_e)
				{

					HitObject = Collision(a, HitLayer, *Itr_s);

				}

			}
		}

		SelectLayer = SelectLayer << 1;
		HitLayerNumber = HitLayerNumber >> 1;
	}

	return false;
}

CGameObject* CCollisionBase::Collision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CCollisionBase* HitObject)
{

	//Ç»ÇÒÇ©äÓñ{ÇÃÇ†ÇΩÇËîªíËÇ≈Ç‡é¿ëïÇµÇ∆Ç±Ç§Ç©Ç»ÅH

	return NULL;
}