#pragma once
#include "C3DObj.h"

class CItem :
	public C3DObj
{

public:
	CItem(void);
	CItem(ID::SCENE_ID);
	~CItem(void);

	void Initialize();
	void Update();
	void Draw();

};

