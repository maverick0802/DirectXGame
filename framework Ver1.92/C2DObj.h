#pragma once
#include "GameObject.h"
#include "plate.h"
class C2DObj :
	public CGameObject
{
protected:
	CPlate m_Plate;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PrevDraw();
	virtual void Draw();
	virtual void AlphaDraw();
	virtual void UnInitialize();
	virtual void ResistChild(CGameObject*);
	virtual void SendMatrixforChildren(D3DXMATRIX);

	C2DObj();
	C2DObj(ID::SCENE_ID);
	~C2DObj();
};

