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
	CObjectFactory<CPlayer>::Instance()->CreateObject();
	CObjectFactory<CField>::Instance()->CreateObject();
	CObjectFactory<CSky>::Instance()->CreateObject();
	CObjectFactory<CItem>::Instance()->CreateObject();
	CObjectFactory<CGoalLogo>::Instance()->CreateObject();

	C3DObj* House= CObjectFactory<CHouse>::Instance()->CreateObject();
	House->SetModelName("House.x");
	House->SetPos(D3DXVECTOR3(0, 0, 0));
	//House = CObjectFactory<CHouse>::Instance()->CreateObject();
	//House->SetModelName("House.x");
	//House->SetPos(D3DXVECTOR3(-100, 1, -100));
	//House = CObjectFactory<CHouse>::Instance()->CreateObject();
	//House->SetModelName("House3.x");
	//House->SetPos(D3DXVECTOR3(200, 1, 200));
	//CObjectFactory<CPlayer>::Instance()->CreateObject();
	House = CObjectFactory<CHouse>::Instance()->CreateObject();
	House->SetModelName("House.x");
	House->SetPos(D3DXVECTOR3(-100, 1, -100));
	House = CObjectFactory<CHouse>::Instance()->CreateObject();
	House->SetModelName("House3.x");
	House->SetPos(D3DXVECTOR3(200, 1, 200));
	CObjectFactory<CPlayer>::Instance()->CreateObject();

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