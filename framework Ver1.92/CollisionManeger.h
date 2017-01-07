#pragma once
#include <map>
#include <List>
#include "CollisionBase.h"


class CCollisionManeger
{
	
	std::map<ID::OBJECT_ID, std::list<CCollisionBase*>> m_CollisionMap;
public:
	static CCollisionManeger* Instance();
	bool GetCollisionList(int Layer, std::list<CCollisionBase*>* List);
	bool Resist(int Layer, CCollisionBase* CollBase);
	~CCollisionManeger();
private:
	CCollisionManeger();

};

