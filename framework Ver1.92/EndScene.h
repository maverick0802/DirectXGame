#pragma once
#include "SceneBase.h"
class CEndScene :
	public CSceneBase
{
public:
	CEndScene();
	~CEndScene();
	void Initialize();
	void Updata();
	void LateUpdata();
	void PrevDraw();
	void Draw();
	void Release();
};

