#include "SceneBase.h"
#include "ObjectFactory.h"
#include "DXInput.h"


CSceneBase::CSceneBase()
{
}


CSceneBase::~CSceneBase()
{
}

void CSceneBase::Initialize()
{

	CObjectFactoryManeger::Instance()->Initialize();

}


void CSceneBase::Updata()
{
	CDXInput::Update();
	CObjectFactoryManeger::Instance()->Updata();

}

void CSceneBase::LateUpdata()
{

	CObjectFactoryManeger::Instance()->LateUpdata();

}

void CSceneBase::PrevDraw()
{

	CObjectFactoryManeger::Instance()->PrevDraw();

}

void CSceneBase::Draw()
{

	CObjectFactoryManeger::Instance()->Draw();

}

void CSceneBase::Release()
{

	CDXInput::UnInitialize();

}