#include "GameObject.h"


CGameObject::CGameObject(ID::SCENE_ID ID)
{
	m_SceneID = ID;
	m_ObjectNumber = -1;
	m_Parent = false;
	m_RemoveFlag = false;

}


CGameObject::~CGameObject()
{

		

}

void CGameObject::OnRemove()
{

	m_RemoveFlag = true;

}

bool CGameObject::GetRemove()
{

	return m_RemoveFlag;

}

void CGameObject::SetObjectNumber(int Number)
{

	m_ObjectNumber = Number;

}

void CGameObject::SetAllObjectNumber(int Number)
{

	m_AllObjectNumber = Number;

}

void CGameObject::OnParent()
{

	m_Parent = true;

}

