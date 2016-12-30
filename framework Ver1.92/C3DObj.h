#pragma once
#include "GameObject.h"
#include "DirectX3D.h"
#include "Mesh.h"
#include <list>

class C3DObj :
	public CGameObject
{
protected:
	CMesh*		m_Meshdata;
	D3DXVECTOR3 m_Move;
	float		m_Radius;
	D3DXVECTOR3 m_Center;
	std::string m_ModelName;
public:
	C3DObj(ID::SCENE_ID);
	C3DObj();
	virtual ~C3DObj();
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PrevDraw();
	virtual void Draw();
	virtual void UnInitialize();
	void Translate(D3DXVECTOR3 trans);
	void ResistChild(CGameObject*);
	void SendMatrixforChildren(D3DXMATRIX);
	bool Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay = false, D3DXVECTOR3* pCross = NULL, D3DXVECTOR3* pNormal = NULL);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetWorldPos();
	D3DXMATRIX  GetWorld();
	D3DXVECTOR3 GetForward();
	D3DXVECTOR3 GetRight();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetMove();
	D3DXVECTOR3 GetPrevPos();
	float		GetRadius();
	D3DXVECTOR3	GetCenter();
	bool		CollisionSphere(C3DObj*);
	void		AddMove(D3DXVECTOR3);
	void		SetWorld(D3DXMATRIX);
	void		SetModelName(std::string);
};

