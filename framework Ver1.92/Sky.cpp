#include "Sky.h"
#include "ResourceLoader.h"

CSky::CSky()
{

	

}

CSky::CSky(ID::SCENE_ID SceneID)
{

			

}


CSky::~CSky()
{

	

}

void CSky::Initialize()
{
	C3DObj::Initialize();

	SetModelName("Dome_K202.x");
	if (!m_Meshdata)
		CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(m_ModelName, &m_Meshdata);
	m_Camera = CObjectMediator::Instance()->FindObject<CCamera>(0);
	SetPos(m_Camera->GetPos());
	//m_Camera->ResistChild(this);

}

void CSky::Update()
{

	C3DObj::Update();
	SetPos(m_Camera->GetPos());

}

void CSky::PrevDraw()
{

	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_LIGHTING, FALSE);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_LIGHTING, TRUE);

	

}

void CSky::Draw()
{
	//‚È‚É‚à‚µ‚È‚¢
}
