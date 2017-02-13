#include "Field.h"
#include "ResourceLoader.h"


CField::CField()
{
}


CField::~CField()
{
}

void CField::Initialize()
{
	C3DObj::Initialize();
	SetModelName("Wall.x");
	if (!m_Meshdata)
		CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(m_ModelName, &m_Meshdata);
	SetPos(D3DXVECTOR3(0, 0, 0));
}
void CField::Update()
{

	C3DObj::Update();
	 
}

void CField::LateUpdate()
{

	C3DObj::LateUpdate();

}

void CField::Draw()
{
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ‹¾–Ê”½ŽË‚ð–³Œø
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ‹¾–Ê”½ŽË‚ð–³Œø

}

void CField::UnInitialize()
{

	

}
