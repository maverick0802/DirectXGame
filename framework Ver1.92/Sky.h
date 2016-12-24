#pragma once
#include "C3DObj.h"
#include "ObjectMediator.h"

class CSky :
	public C3DObj
{
	C3DObj* m_Camera;

public:
	CSky();
	CSky(ID::SCENE_ID);
	~CSky();

	void Initialize();
	void Update();
	void PrevDraw();
	void Draw();
};

