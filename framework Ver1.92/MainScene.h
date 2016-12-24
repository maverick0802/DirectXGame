#pragma once
#include "SceneBase.h"
class CMainScene :
	public CSceneBase
{
public:
	CMainScene();
	~CMainScene();
	void Initialize();
	void Updata();
	void LateUpdata();
	void PrevDraw();
	void Draw();
	void Release();

};

