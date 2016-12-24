#include "ResourceBase.h"



CResourceBase::CResourceBase()
{

	

}

CResourceBase::~CResourceBase()
{
}

ID::SCENE_ID CResourceBase::GetSceneID()
{

	return m_SceneID;

}
ID::RESOURCE_ID CResourceBase::GetResourceID()
{

	return m_ResourceID;

}

int CResourceBase::GetResourceNumber()
{

	return m_ResourceNumber;

}
