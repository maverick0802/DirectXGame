#include "CollisionManeger.h"


CCollisionBase::CCollisionBase() :
	m_Active(true),
	m_Hit(false),
	m_HitedObject(NULL),
	m_pWorld(NULL),
	m_Center(D3DXVECTOR3(0, 0, 0)),
	m_Box(D3DXVECTOR3(0, 0, 0)),
	m_Color(255,0,0,0.5f)
{
}


CCollisionBase::~CCollisionBase()
{


}


void CCollisionBase::OnActive()
{

	m_Active = true;

}


void CCollisionBase::OffActive()
{

	m_Active = false;

}


void CCollisionBase::SetHitedObject(CGameObject* SetObject)
{

	m_HitedObject = SetObject;

}

bool CCollisionBase::CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject)
{
	//int SelectLayer = 0x01;
	//int HitLayerNumber = HitLayer;
	//D3DXVECTOR3 a;
	//std::list<CCollisionBase*>* List;
	//while (HitLayerNumber != 0)
	//{
	//	if (HitLayerNumber & 0x01)
	//	{
	//		if (CCollisionManeger::Instance()->GetCollisionList(SelectLayer, List))
	//		{
	//			auto Itr_s = List->begin();
	//			auto Itr_e = List->end();

	//			while (Itr_s != Itr_e)
	//			{

	//				HitObject = Collision(a, HitLayer, *Itr_s);

	//			}

	//		}
	//	}

	//	SelectLayer = SelectLayer << 1;
	//	HitLayerNumber = HitLayerNumber >> 1;
	//}

	return false;
}


///////////////////////////
// あたり判定
///////////////////////////
bool CCollisionBase::Collision( CCollisionBase* Opponent)
{

	//なんか基本のあたり判定でも実装しとこうかな？

	return false;
}


///////////////////////////
// ボックスの設定
///////////////////////////
void CCollisionBase::SetBox(D3DXVECTOR3 & Box)
{
	//Meshの初期化
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//ボックスの新規設定
	m_Box = Box;
	HRESULT hr = D3DXCreateBox(*CDirectX3D::Create()->GetDevice(), m_Box.x * 2, m_Box.y * 2, m_Box.z * 2, &m_pMesh, NULL);

	//生成に失敗したらNULL代入
	if (FAILED(hr))
		m_pMesh = NULL;


}


///////////////////////////
// デバック用描画
///////////////////////////
void CCollisionBase::Draw()
{

	//デフォルトでは何も描画しない
	//派生先で描画を変える

}