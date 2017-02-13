/////////////////////////////////////
//
// インクルード
//
/////////////////////////////////////

#pragma once
#include "DirectX3D.h"
#include "SceneMediator.h"
#include<list>

///////////////////////////////////
//
// ID定義
//
///////////////////////////////////
namespace ID{

	typedef enum{

		OBJECT_PLAYER =  1,
		OBJECT_ENEMY  =  2,
		OBJECT_HOUSE  =  4,
		OBJECT_FIELD  =  8,
		OBJECT_SKY    = 16,
		OBJECT_OTHER  = 32

	}OBJECT_ID;

}


class CGameObject
{
protected:
	D3DXMATRIX	m_World;
	D3DXMATRIX	m_LocalWorld;
	D3DXMATRIX	m_PrevLocalWorld;
	int				m_ObjectNumber;
	int				m_AllObjectNumber;
	ID::OBJECT_ID	m_ObjID;
	ID::SCENE_ID	m_SceneID;
	bool			m_Parent;	//親がいるか	
	std::list<CGameObject*>	m_ChildrenList;
	bool			m_RemoveFlag;
	
public:
	CGameObject(ID::SCENE_ID ID);
	virtual ~CGameObject();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void PrevDraw() = 0;
	virtual void Draw() = 0;
	virtual void AlphaDraw() = 0;
	virtual void UnInitialize() = 0;
	virtual void ResistChild(CGameObject* ) = 0;
	virtual void SendMatrixforChildren(D3DXMATRIX ) = 0;
	void OnRemove();
	bool GetRemove();
	void SetPos(D3DXVECTOR3 pos) { m_LocalWorld._41 = pos.x;  m_LocalWorld._42 = pos.y;  m_LocalWorld._43 = pos.z; };
	//D3DXVECTOR3 GetLocalPos() { return D3DXVECTOR3(m_LocalWorld._41, m_LocalWorld._42, m_LocalWorld._43); };		
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(m_LocalWorld._41, m_LocalWorld._42, m_LocalWorld._43); };
	D3DXVECTOR3 GetForward() { return D3DXVECTOR3(m_World._31, m_World._32, m_World._33);};
	D3DXVECTOR3 GetRight() { return D3DXVECTOR3(m_World._11, m_World._12, m_World._13); };
	D3DXVECTOR3 GetUp() { return D3DXVECTOR3(m_World._21, m_World._22, m_World._23); };
	D3DXMATRIX  GetWorld() { return m_World; };
	D3DXMATRIX  GetLocalWorld() { return m_LocalWorld; };
	void		SetWorld(D3DXMATRIX world) { m_LocalWorld = world; };
	void SetObjectNumber(int Number);
	void SetAllObjectNumber(int Number);
	void OnParent();

};

