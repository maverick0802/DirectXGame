#include "House.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"
 
CHouse::CHouse(void)
{

	m_ThicknessWall = 5.0f;
	
}


CHouse::~CHouse(void)
{
}

void CHouse::Initialize()
{

	CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(m_ModelName,&m_Meshdata);
	m_HitBox.x = 47 * 2;
	m_HitBox.y = 53;
	m_HitBox.z = 22 * 2;

}

void CHouse::Update()
{

	C3DObj* Obj = CObjectMediator::Instance()->FindObject<CPlayer>(0);
	D3DXVECTOR3 PlayerPos = Obj->GetPos();


}

