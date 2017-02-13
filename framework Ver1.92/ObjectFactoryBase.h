#pragma once
#include "GameObject.h"

class CObjectFactoryBase
{
protected:
	static int m_AllObject;
	int m_ObjectNum;
	ID::SCENE_ID  m_SceneID;
	ID::OBJECT_ID m_ObjectID;

public:
	CObjectFactoryBase(void);
	CObjectFactoryBase(ID::SCENE_ID SceneID);
	~CObjectFactoryBase(void);
	virtual void Initialize() = 0;

	virtual void Updata() = 0;

	virtual void LateUpdata() = 0;

	virtual void PrevDraw() = 0;

	virtual void Draw() = 0;

	virtual void AlphaDraw() = 0;

	virtual void Release() = 0;

};

