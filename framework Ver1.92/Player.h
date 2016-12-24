#pragma once
#include "c3dobj.h"
class CPlayer :
	public C3DObj
{
public:
	CPlayer(void);
	CPlayer(ID::SCENE_ID);
	~CPlayer(void);

	void Initialize();
	void Update();
	void Draw();
};

