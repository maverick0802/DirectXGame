#pragma once
#include "C3DObj.h"
#include "OBB.h"

class CWall :
	public C3DObj
{
	COBB m_OBB[4];


public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Draw();
	void AlphaDraw();
	void UnInitialize();
	COBB* CWall::GetOBB();

public:
	CWall();
	virtual ~CWall();
};

