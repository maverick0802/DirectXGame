#pragma once
#include "C3DObj.h"
class CField :
	public C3DObj
{
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Draw();
	void UnInitialize();

	CField();
	~CField();
};

