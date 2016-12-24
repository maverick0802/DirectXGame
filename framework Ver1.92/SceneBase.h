#pragma once
class CSceneBase
{
public:
	virtual void Initialize();
	virtual void Updata();
	virtual void LateUpdata();
	virtual void PrevDraw();
	virtual void Draw();
	virtual void Release();
	CSceneBase();
	~CSceneBase();
};

