#pragma once
#include "SceneBase.h"
class CTitleScene :
	public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();
	void Initialize();
	void Updata();
	void LateUpdata();
	void PrevDraw();
	void Draw();
	void Release();

};

