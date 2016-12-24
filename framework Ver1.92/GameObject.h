#pragma once
#include "DirectX3D.h"
#include "SceneMediator.h"
#include<list>
namespace ID{

	typedef enum{

		OBJECT_PLAYER = 100,
		OBJECT_ENEMY

	}OBJECT_ID;

}


class CGameObject
{
protected:
	int				m_ObjectNumber;
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
	void OnParent();

};

