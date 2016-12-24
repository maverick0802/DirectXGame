#include "Enemy.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"

CEnemy::CEnemy()
{
	m_ObjID = ID::OBJECT_ENEMY;
}

CEnemy::CEnemy(ID::SCENE_ID SceneID)
{



}


CEnemy::~CEnemy()
{
}

void CEnemy::Initialize()
{
	C3DObj::Initialize();

	//CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load( "Sphere.x", m_Meshdata);
	m_Meshdata->SwitchAnimenSet(2);

	SetPos(D3DXVECTOR3(0, 0, 0));
}

void CEnemy::Update()
{
	C3DObj::Update();
	D3DXQUATERNION	Quon;
	D3DXMATRIX		rotmat;
	D3DXMATRIX		world = GetWorld();

	//D3DXQuaternionRotationYawPitchRoll(&Quon, D3DXToRadian(1), D3DXToRadian(0), D3DXToRadian(0));
	D3DXQuaternionRotationAxis(&Quon, &D3DXVECTOR3(10, 0, 0), D3DXToRadian(1));
	D3DXMatrixRotationQuaternion(&rotmat, &Quon);
	D3DXMatrixMultiply(&world, &world, &rotmat);
	SetWorld(world);

}

void CEnemy::Draw()
{

	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// ‹¾–Ê”½ŽË‚ð–³Œø
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ‹¾–Ê”½ŽË‚ð–³Œø


}
