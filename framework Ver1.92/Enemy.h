#pragma once
#include "C3DObj.h"
class CEnemy :
	public C3DObj
{
public:
	CEnemy(void);
	CEnemy(ID::SCENE_ID);
	virtual~CEnemy(void);

	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
};

