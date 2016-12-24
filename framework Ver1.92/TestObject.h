#pragma once
#include "C3DObj.h"

class CTestObject :
	public C3DObj
{
	CMesh* Mesh;

public:
	CTestObject();
	~CTestObject();
	void Initialize();
	//void Update();
	//void LateUpdate();
	//void PrevDraw();
	void Draw();
	//void UnInitialize();

};

