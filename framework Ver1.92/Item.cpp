#include "Item.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"

 D3DXVECTOR3 Point[4];/* = {{D3DXVECTOR3(-618,10,-300)},
							  {D3DXVECTOR3(-84,32,-205)},
							  {D3DXVECTOR3(-666,53,-43)},
							  {D3DXVECTOR3(127,32,42)},};*/
 bool bFlag[4] = {false};

CItem::CItem(void)
{
	m_Radius = 10;
	m_SceneID = ID::SCENE_NULL;
}
CItem::CItem(ID::SCENE_ID SceneID)
{
	m_Radius = 10;
	m_SceneID = SceneID;
}


CItem::~CItem(void)
{
}

void CItem::Initialize()
{
	Point[0] = D3DXVECTOR3(-618,10,-300);
	Point[1] = D3DXVECTOR3(-84,32,-205);
	Point[2] = D3DXVECTOR3(-666,53,-43);
	Point[3] = D3DXVECTOR3(127,32,42);
	C3DObj::Initialize();
	//CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(ID::SCENE_NULL, "Sphere.x", m_Meshdata);
	
	int PointNum = rand() % 5;
	while(bFlag[PointNum] == true)
	{
	
		PointNum = rand();

	}
	bFlag[PointNum] = true;

	SetPos(Point[PointNum]);
}

void CItem::Update()
{

	C3DObj::Update();
	C3DObj* pPlayer = CObjectMediator::Instance()->Instance()->FindObject<CPlayer>( 0);
	if (pPlayer->CollisionSphere(this))
		CObjectMediator::Instance()->Instance()->RemoveObject<CItem>(m_ObjectNumber);


}

void CItem::Draw()
{

	C3DObj::Draw();

}
