#include "C3DObj.h"


C3DObj::C3DObj(ID::SCENE_ID SceneID):
CGameObject(SceneID),
m_Radius(0.5f),
m_Center(0,0,0),
m_Meshdata(NULL),
m_Box(0,0,0)
{

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&m_LocalWorld);
	D3DXMatrixIdentity(&m_PrevLocalWorld);

}

C3DObj::C3DObj():
CGameObject(ID::SCENE_NULL),
m_Radius(0.5f),
m_Center(0, 0, 0),
m_Meshdata(NULL),
m_Box(0, 0, 0)
{

	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&m_LocalWorld);
	D3DXMatrixIdentity(&m_PrevLocalWorld);

}

C3DObj::~C3DObj()
{
}

void C3DObj::Initialize()
{



}

void C3DObj::Update()
{
	//D3DXMatrixIdentity(&m_World);
	if(m_Meshdata)
		m_Meshdata->Updata(); 
	m_PrevLocalWorld = m_LocalWorld;
}

void C3DObj::LateUpdate()
{
	if (!m_Parent)
	{
		D3DXMATRIX tmp;
		D3DXMatrixIdentity(&tmp);
		SendMatrixforChildren(tmp);
	}
}

void C3DObj::PrevDraw()
{

}

void C3DObj::Draw()
{


	if(m_Meshdata)
		m_Meshdata->Draw(m_World);

}

void C3DObj::UnInitialize()
{

	

}


void C3DObj::Translate(D3DXVECTOR3 trans)
{
	D3DXMATRIX Trans;
	D3DXMatrixTranslation(&Trans, trans.x, trans.y, trans.z);
	D3DXMatrixMultiply(&m_LocalWorld, &m_LocalWorld, &Trans);

}

void C3DObj::ResistChild(CGameObject* Child)
{

	m_ChildrenList.push_back(Child);
	Child->OnParent();

}

void C3DObj::SendMatrixforChildren(D3DXMATRIX ParentWorld)
{

	m_World = m_LocalWorld * ParentWorld;

	auto Itr_S = m_ChildrenList.begin();
	auto Itr_E = m_ChildrenList.end();

	while (Itr_S != Itr_E)
	{

		(*Itr_S)->SendMatrixforChildren(m_World);
		Itr_S++;
	}

}

//void C3DObj::SetPos(D3DXVECTOR3 pos)
//{
//
//	m_LocalWorld._41 = pos.x;
//	m_LocalWorld._42 = pos.y;
//	m_LocalWorld._43 = pos.z;
//
//}
//
/////////////////////////////////////////
//// 親空間におけるローカル座標の取得
/////////////////////////////////////////
//D3DXVECTOR3 C3DObj::GetPos()
//{
//
//	return D3DXVECTOR3(m_LocalWorld._41, m_LocalWorld._42, m_LocalWorld._43);
//
//}
//
/////////////////////////////////////////
//// ワールド座標の取得
/////////////////////////////////////////
//D3DXVECTOR3 C3DObj::GetWorldPos()
//{
//
//	return D3DXVECTOR3(m_World._41, m_World._42, m_World._43);
//
//}
//
/////////////////////////////////////////
//// ワールド行列の取得
/////////////////////////////////////////
//D3DXMATRIX  C3DObj::GetWorld()
//{
//	return m_LocalWorld;
//}
//
/////////////////////////////////////////
//// ワールド行列の設定
/////////////////////////////////////////
//void  C3DObj::SetWorld(D3DXMATRIX World)
//{
//	m_LocalWorld = World; 
//}
//
/////////////////////////////////////////
//// 前方ベクトルの取得
/////////////////////////////////////////
//D3DXVECTOR3 C3DObj::GetForward()
//{
//
//	return D3DXVECTOR3(m_LocalWorld._31, m_LocalWorld._32, m_LocalWorld._33);
//
//}
//
/////////////////////////////////////////
//// 右ベクトルの取得
/////////////////////////////////////////
//D3DXVECTOR3 C3DObj::GetRight()
//{
//
//	return D3DXVECTOR3(m_LocalWorld._11, m_LocalWorld._12, m_LocalWorld._13);
//
//}
//
/////////////////////////////////////////
//// 上方ベクトルの取得
/////////////////////////////////////////
//D3DXVECTOR3 C3DObj::GetUp()
//{
//
//	return D3DXVECTOR3(m_LocalWorld._21, m_LocalWorld._22, m_LocalWorld._23);
//
//}

///////////////////////////////////////
// 移動量の取得
///////////////////////////////////////
D3DXVECTOR3 C3DObj::GetMove()
{

	return m_Move;

}

///////////////////////////////////////
// 半径の取得
///////////////////////////////////////
float C3DObj::GetRadius()
{

	return m_Radius;

}

///////////////////////////////////////
// 中心の取得
///////////////////////////////////////
D3DXVECTOR3 C3DObj::GetCenter()
{

	return m_Center;

}

bool C3DObj::CollisionSphere(C3DObj* Obj)
{
	D3DXVECTOR3 vPos1,vPos2;

	D3DXVec3TransformCoord(&vPos1, &GetCenter(), &GetWorld());
	D3DXVec3TransformCoord(&vPos2, &Obj->GetCenter(), &Obj->GetWorld());

	float fRadius = GetRadius() + Obj->GetRadius();

	return D3DXVec3LengthSq(&(vPos1 - vPos2)) < fRadius * fRadius;

}

bool C3DObj::CollisionOBB(C3DObj* Obj)
{

	D3DXVECTOR3 Localvec[6];
	D3DXVECTOR3 BoxLength[6];
	Localvec[0] = GetRight();
	Localvec[1] = GetUp();
	Localvec[2] = GetForward();
	Localvec[3] = Obj->GetRight();
	Localvec[4] = Obj->GetUp();
	Localvec[5] = Obj->GetForward();

	D3DXVECTOR3 myBox = GetBox();
	D3DXVECTOR3 youBox = Obj->GetBox();
	BoxLength[0] = Localvec[0] * myBox.x;
	BoxLength[1] = Localvec[1] * myBox.y;
	BoxLength[2] = Localvec[2] * myBox.z;
	BoxLength[3] = Localvec[3] * youBox.x;
	BoxLength[4] = Localvec[4] * youBox.y;
	BoxLength[5] = Localvec[5] * youBox.z;
	
	D3DXVECTOR3 CenterVec = GetCenter() - Obj->GetCenter();


	float fLength;
	D3DXVECTOR3 vSep;

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		vSep = Localvec[nCnt];
		fLength = 0.0f;
		for (int nNum = 0; nNum < 6; nNum++)
		{

			fLength += fabsf(D3DXVec3Dot(&vSep, &BoxLength[nNum]));

		}
		if (fabsf(D3DXVec3Dot(&vSep, &CenterVec)))
		{

			return false;

		}

	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		for (int nNum1 = 3; nNum1 < 6; nNum1++)
		{
			D3DXVec3Cross(&vSep, &Localvec[nCnt], &Localvec[nNum1]);
			D3DXVec3Normalize(&vSep, &vSep);
			fLength = 0.0f;
			for (int nNum2 = 0; nNum2 < 6; nNum2++)
			{

				fLength += fabsf(D3DXVec3Dot(&vSep, &BoxLength[nNum2]));

			}

			if (fabsf(D3DXVec3Dot(&vSep, &CenterVec)))
			{

				return false;

			}
		}
	}

	
	return true;
}


///////////////////////////////////////
// 
///////////////////////////////////////
void C3DObj::AddMove(D3DXVECTOR3 move)
{

	m_Move += move;

}



D3DXVECTOR3 C3DObj::GetPrevPos()
{

	return D3DXVECTOR3(m_PrevLocalWorld._41, m_PrevLocalWorld._42, m_PrevLocalWorld._43);

}

bool C3DObj::Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{

	if (m_Meshdata)
	{
		return m_Meshdata->Intersect(L0, L1, bRay, pCross, pNormal);
	}
	return false;
}

void C3DObj::SetModelName(std::string ModelName)
{
	m_ModelName = ModelName;
}