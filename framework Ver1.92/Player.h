#pragma once
#include "c3dobj.h"

#include "OBB.h"
class CPlayer :
	public C3DObj
{

	COBB m_OBB;
public:
	CPlayer(void);
	CPlayer(ID::SCENE_ID);
	~CPlayer(void);

	void Initialize();
	void Update();
	void Draw();
	void AlphaDraw();
	COBB GetOBB();

};

