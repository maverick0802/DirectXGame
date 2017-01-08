#include "CollisionManeger.h"



CCollisionManeger::CCollisionManeger()
{
}


CCollisionManeger::~CCollisionManeger()
{
}


CCollisionManeger* CCollisionManeger::Instance()
{

	static CCollisionManeger Instance;

	return &Instance;

}
bool CCollisionManeger::GetCollisionList(int Layer, std::list<CCollisionBase*>* List)
{

	if (m_CollisionMap.find((ID::OBJECT_ID) Layer) != m_CollisionMap.end())
	{
		List = &m_CollisionMap[(ID::OBJECT_ID)Layer];
		return true;;
	}

	List = NULL;
	return false;
}

bool CCollisionManeger::Resist(int Layer, CCollisionBase* CollBase)
{

	if (m_CollisionMap.find((ID::OBJECT_ID) Layer) != m_CollisionMap.end())
	{
		std::list<CCollisionBase*> tmp; 
		m_CollisionMap.insert(std::make_pair((ID::OBJECT_ID) Layer, tmp));
		m_CollisionMap[(ID::OBJECT_ID) Layer].push_back(CollBase);

	}
	else
	{

		m_CollisionMap[(ID::OBJECT_ID) Layer].push_back(CollBase);

	}

	return false;
}