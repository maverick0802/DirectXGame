#pragma once
#include "CollisionBase.h"
class COBB :
	public CCollisionBase
{
public:
	COBB();
	~COBB();
	CGameObject* Collision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CCollisionBase* HitObject);
};

