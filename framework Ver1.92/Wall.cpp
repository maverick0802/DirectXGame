#include "Wall.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"



CWall::CWall()
{
	m_ObjID = ID::OBJECT_WALL;

}


CWall::~CWall()
{
}

void CWall::Initialize()
{
	C3DObj::Initialize();

	//ÉÇÉfÉãÇÃê›íË
	SetModelName("Wall.x");
	if (!m_Meshdata)
		CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(m_ModelName, &m_Meshdata);
	SetPos(D3DXVECTOR3(0, 0, 0));

	D3DXVECTOR3 Center[4] = { {   0,  70,  370 },
							  {   0,  70, -370 },
							  { 370,  70,    0 }, 
							  {-370,  70,    0 }, };
	D3DXVECTOR3 Box[2]    = { { 400, 100,   30 },
						      {  30, 100,  400 }, };

	//OBBÇÃê›íË
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{

		m_OBB[nCnt].SetWorldMatrix(&m_LocalWorld);
		m_OBB[nCnt].SetBox(Box[nCnt / 2]);
		m_OBB[nCnt].SetCenter(Center[nCnt]);
		m_OBB[nCnt].SetColor(D3DXCOLOR(255, 0, 0, 100));

	}

}
void CWall::Update()
{

	C3DObj::Update();

}

void CWall::LateUpdate()
{

	C3DObj::LateUpdate();

}

void CWall::Draw()
{
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ãæñ îΩéÀÇñ≥å¯
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ãæñ îΩéÀÇñ≥å¯

}

void CWall::AlphaDraw()
{

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{

		m_OBB[nCnt].Draw();

	}

}

void CWall::UnInitialize()
{



}

COBB* CWall::GetOBB()
{

	return m_OBB;

}