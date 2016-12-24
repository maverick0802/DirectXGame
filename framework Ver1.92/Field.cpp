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
	SetModelName("Field3.x");
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

	C3DObj::Draw();

}

void CField::UnInitialize()
{

	

}
