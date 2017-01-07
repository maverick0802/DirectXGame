#pragma once
#include "DirectX3D.h"
#include "SceneMediator.h"
#include<list>
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
	bool			m_Parent;	//êeÇ™Ç¢ÇÈÇ©	
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
	virtual void UnInitialize() = 0;
	virtual void ResistChild(CGameObject* ) = 0;
	virtual void SendMatrixforChildren(D3DXMATRIX ) = 0;
	void OnRemove();
	bool GetRemove();
	void SetObjectNumber(int Number);
	void SetAllObjectNumber(int Number);
	void OnParent();

};

