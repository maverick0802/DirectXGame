#pragma once
#include "c3dobj.h"
#include "OBB.h"
class CHouse :
	public C3DObj
{

	D3DXVECTOR3 m_HitBox;
	COBB		m_OBB;

	float		m_ThicknessWall;
public:
	CHouse(void);
	CHouse(ID::SCENE_ID){}
	~CHouse(void);
	void Initialize();
	void Update();
	void Draw();
	

};

