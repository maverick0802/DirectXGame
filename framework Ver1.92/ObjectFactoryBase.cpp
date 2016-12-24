#include "ObjectFactoryBase.h"


CObjectFactoryBase::CObjectFactoryBase(void):
m_ObjectNum(0),
m_SceneID(ID::SCENE_NULL)
{
}


CObjectFactoryBase::CObjectFactoryBase(ID::SCENE_ID SceneID):
m_ObjectNum(0),
m_SceneID(SceneID)
{

}


CObjectFactoryBase::~CObjectFactoryBase(void)
{
}
