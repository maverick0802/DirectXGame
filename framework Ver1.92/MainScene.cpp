#include "MainScene.h"
#include "ObjectFactory.h"


CMainScene::CMainScene()
{
}


CMainScene::~CMainScene()
{
}

void CMainScene::Initialize()
{

	//CObjectFactory<CCamera>::Instance()->CreateObject();
	//CObjectFactory<CSky>::Instance()->CreateObject();
	//CObjectFactory<CField>::Instance()->CreateObject();
	//CObjectFactory<CPlayer>::Instance()->CreateObject();
	////CObjectFactory<CEnemy>::Instance()->CreateObject();
	//CObjectFactory<CItem>::Instance()->CreateObject();
	//CObjectFactory<CItem>::Instance()->CreateObject();
	//CObjectFactory<CGoalLogo>::Instance()->CreateObject();
	//CObjectFactory<CTutorial>::Instance()->CreateObject();

	CSceneBase::Initialize();
}

void CMainScene::Updata()
{

	CSceneBase::Updata();

}

void CMainScene::LateUpdata()
{

	CSceneBase::LateUpdata();

}

void CMainScene::PrevDraw()
{

	CSceneBase::PrevDraw();

}

void CMainScene::Draw()
{

	CSceneBase::Draw();

}

void CMainScene::Release()
{

	//CSceneBase::Release();

}
