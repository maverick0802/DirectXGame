#include "SceneMediator.h"


CSceneMediator::CSceneMediator():
m_NowScene(ID::SCENE_NULL),
m_NextScene(ID::SCENE_TITLE)
{
}


CSceneMediator::~CSceneMediator()
{
}

CSceneMediator* CSceneMediator::Instance()
{

	static CSceneMediator Instance;

	return &Instance;

}

void CSceneMediator::SetNextScene(ID::SCENE_ID SceneID)
{

	m_NextScene = SceneID;

}

void CSceneMediator::SetNowScene(ID::SCENE_ID SceneID)
{

	m_NowScene = SceneID;

}

ID::SCENE_ID CSceneMediator::GetNowScene()
{

	return m_NowScene;

}

ID::SCENE_ID CSceneMediator::GetNextScene()
{

	return m_NextScene;

}

