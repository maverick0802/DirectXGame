#include "TitleScene.h"
#include "ObjectFactory.h"


CTitleScene::CTitleScene()
{
}


CTitleScene::~CTitleScene()
{
}

void CTitleScene::Initialize()
{
	//CObjectFactory<CCamera>::Instance()->CreateObject();
	CObjectFactory<CCamera>::Instance()->CreateObject();
	CObjectFactory<CSky>::Instance()->CreateObject();
	CObjectFactory<CField>::Instance()->CreateObject();
	CObjectFactory<CWall>::Instance()->CreateObject();
	CObjectFactory<CPlayer>::Instance()->CreateObject();
	CObjectFactory<CItem>::Instance()->CreateObject();
	CObjectFactory<CGoalLogo>::Instance()->CreateObject();

	C3DObj* House= CObjectFactory<CHouse>::Instance()->CreateObject();
	House->SetModelName("Stone.x");
	House->SetPos(D3DXVECTOR3(0, 0, 0));

	CSceneBase::Initialize();

}

void CTitleScene::Updata()
{

	CSceneBase::Updata();

}

void CTitleScene::LateUpdata()
{

	CSceneBase::LateUpdata();


}

void CTitleScene::PrevDraw()
{

	CSceneBase::PrevDraw();

}

void CTitleScene::Draw()
{
	
	CSceneBase::Draw();

}

void CTitleScene::Release()
{



}