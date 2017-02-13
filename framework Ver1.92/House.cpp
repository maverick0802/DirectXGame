#include "House.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"
 
CHouse::CHouse(void)
{

	m_ThicknessWall = 5.0f;
	m_Box = D3DXVECTOR3(10, 10, 10);
	
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
	m_OBB.SetBox(D3DXVECTOR3(10,10,10));
	m_OBB.SetWorldMatrix(&m_LocalWorld);
	m_OBB.SetColor(D3DXCOLOR(255,0,0,255));

}

void CHouse::Update()
{
	m_OBB.SetColor(D3DXCOLOR(255, 0, 0, 255));
	C3DObj* Obj = CObjectMediator::Instance()->FindObject<CPlayer>(0);
	D3DXVECTOR3 PlayerPos = Obj->GetPos();
}
void CHouse::Draw()
{

	C3DObj::Draw();
	//m_OBB.Draw();

}

