#pragma once
#include "c3dobj.h"
class CHouse :
	public C3DObj
{

	D3DXVECTOR3 m_HitBox;
	float		m_ThicknessWall;
public:
	CHouse(void);
	CHouse(ID::SCENE_ID){}
	~CHouse(void);
	void Initialize();
	void Update();

};

