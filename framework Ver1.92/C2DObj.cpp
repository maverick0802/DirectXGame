#include "C2DObj.h"


C2DObj::C2DObj():
CGameObject(ID::SCENE_NULL)
{


}

C2DObj::C2DObj(ID::SCENE_ID SceneID):
CGameObject(SceneID)
{



}


C2DObj::~C2DObj()
{
}

void C2DObj::Initialize()
{


}

void C2DObj::Update()
{

	

}

void C2DObj::LateUpdate()
{



}

void C2DObj::PrevDraw()
{



}

void C2DObj::Draw()
{

	m_Plate.Draw();

}

void C2DObj::UnInitialize()
{


}

void C2DObj::ResistChild(CGameObject* Child)
{


}

void C2DObj::SendMatrixforChildren(D3DXMATRIX ParentWorld)
{



}
