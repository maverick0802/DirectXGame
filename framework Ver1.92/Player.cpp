#include "Player.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"
#include <map>
#include "DXInput.h"

const float SPEED_FORWORD(2.0f);
const float TURNING_RAD(5.0f);

CPlayer::CPlayer(void):
C3DObj(ID::SCENE_NULL)
{
	//D3DXMatrixIdentity(&m_World);
	m_ObjID = ID::OBJECT_PLAYER;
	m_Center = D3DXVECTOR3(0, 10, 0);
	m_Box = D3DXVECTOR3(10, 20, 10);
}

CPlayer::CPlayer(ID::SCENE_ID SceneID):
C3DObj(SceneID)
{

	m_Center = D3DXVECTOR3(0, 10, 0);
	m_ObjID = ID::OBJECT_PLAYER;

}


CPlayer::~CPlayer(void)
{


}


void CPlayer::Initialize()
{
	C3DObj::Initialize();
	SetModelName("Player_Ver8.x");
	if(!m_Meshdata)
		CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load(m_ModelName,&m_Meshdata);
		m_Meshdata->SwitchAnimenSet(1);
		SetPos(D3DXVECTOR3(0, 0, 0));
	m_OBB.SetWorldMatrix(&m_LocalWorld);
	m_OBB.SetBox(D3DXVECTOR3(5,10,5));
	m_OBB.SetCenter(D3DXVECTOR3(0, 10, 0));
}	



//////////////////////////////////
//
//　関数名: Update
//　引数  : なし
//　戻り値: なし
//　～～～～～～～～～～～～～～～～
//　概要
//　プレイヤーの移動、オブジェクトとのあたり判定
//　
//
//
//////////////////////////////////

void CPlayer::Update()
{
	
	C3DObj::Update();

	//変数宣言
	D3DXVECTOR3 pos = GetPos();					//座標位置
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);		//回転量
	D3DXVECTOR3 Move = D3DXVECTOR3(0, 0, 0);	//移動量
	D3DXVECTOR3	vCrossPoint;					//
	D3DXVECTOR3 CameraForword;					//カメラの前方方向
	D3DXVECTOR3 PlayerForword = GetForward();	//プレイヤーの前方方向
	D3DXMATRIX  world = GetWorld();				//
	D3DXMATRIX  RotMat;							//回転行列
	float CosA;									//コサインの格納変数
	float Angle = 0;							//角度
	bool bMove = false;							//移動したかどうか
	m_PrevLocalWorld = m_LocalWorld;			//過去座標確保

	
	//フィールドとのあたり判定
	C3DObj* pField = CObjectMediator::Instance()->FindObject<CField>(0);
	if(pField->Intersect(pos, D3DXVECTOR3(0, -1, 0), true, &vCrossPoint))
		pos.y = vCrossPoint.y;
	else
		pos.y = 0.0f;

	//プレイヤーの移動
	CCamera* pCamera = CObjectMediator::Instance()->FindObject<CCamera>(0);

	CameraForword = pCamera->GetForward();
	CameraForword = D3DXVECTOR3(CameraForword.x, 0, CameraForword.z);
	D3DXVec3Normalize(&CameraForword, &CameraForword);
	D3DXMatrixIdentity(&RotMat);

	//Wが押されたら
	if (CDXInput::GetKeyPress(DIK_W))
	{
		//カメラの前方方向と角度をとってカメラ方向にプレイヤーを回転
		CosA = D3DXVec3Dot(&PlayerForword, &CameraForword) /
			D3DXVec3Length(&CameraForword) * D3DXVec3Length(&PlayerForword);
		if (CosA > 1 || CosA < -1)
			CosA = (int)CosA;
		Angle = acosf(CosA);

		if (D3DXVec3Dot(&GetRight(), &CameraForword) < 0)
			Angle *= -1;
		D3DXMatrixRotationYawPitchRoll(&RotMat, Angle  * 0.2f, 0, 0);
		bMove = true;

	}

	//Wが押されたら
	if (CDXInput::GetKeyPress(DIK_S))
	{
		//カメラの前方方向と角度をとってカメラ方向にプレイヤーを回転
		CosA =	D3DXVec3Dot(&PlayerForword, &(CameraForword * -1)) /
					D3DXVec3Length(&(CameraForword * -1)) * D3DXVec3Length(&PlayerForword);
		if (CosA > 1 || CosA < -1)
			CosA = (int)CosA;
		Angle = acosf(CosA);

		if (D3DXVec3Dot(&GetRight(), &(CameraForword * -1)) < 0)
			Angle *= -1;
		D3DXMatrixRotationYawPitchRoll(&RotMat, Angle  * 0.2f, 0, 0);
		bMove = true;

	}

	//右方向に旋回
	if (CDXInput::GetKeyPress(DIK_D))
	{
		D3DXVECTOR3 CameraRight = pCamera->GetRight();
		CosA =	D3DXVec3Dot(&PlayerForword, &CameraRight) /
			D3DXVec3Length(&PlayerForword) * D3DXVec3Length(&CameraRight);
		if (CosA > 1 || CosA < -1)
			CosA = (int)CosA;
		Angle = acosf(CosA);

		if (D3DXVec3Dot(&GetRight(), &CameraRight) < 0)
			Angle *= -1;
		D3DXMatrixRotationYawPitchRoll(&RotMat, Angle  * 0.2f, 0, 0);
		D3DXVec3TransformCoord(&PlayerForword, &PlayerForword, &RotMat);
		bMove = true;
		//Move = pCamera->GetForward() * -SPEED_FORWORD;
	}
	
	//左方向に旋回
	if (CDXInput::GetKeyPress(DIK_A))
	{
		D3DXVECTOR3 CameraLeft = pCamera->GetRight() * -1;
		CosA = D3DXVec3Dot(&PlayerForword, &CameraLeft) /
			D3DXVec3Length(&PlayerForword) * D3DXVec3Length(&CameraLeft);
		if (CosA > 1 || CosA < -1)
			CosA = (int)CosA;
		Angle = acosf(CosA);

		if (D3DXVec3Dot(&GetRight(), &CameraLeft) < 0)
			Angle *= -1;
		D3DXMatrixRotationYawPitchRoll(&RotMat, Angle  * 0.2f, 0, 0);
		bMove = true;
		//Move = pCamera->GetForward() * -SPEED_FORWORD;
	}
	

	if (bMove)
	{
		D3DXVec3TransformCoord(&PlayerForword, &PlayerForword, &RotMat);
		Move = PlayerForword * SPEED_FORWORD;
		pos += Move;
	}


	D3DXMatrixMultiply(&world,&world,&RotMat);
	world._41 = pos.x;
	world._42 = pos.y;
	world._43 = pos.z;



	SetWorld(world);

	//大外の壁との判定
	//OBB
	C3DObj* pWall = CObjectMediator::Instance()->FindObject<CWall>(0);
	COBB* WallOBB = ((CWall*)pWall)->GetOBB();

	m_OBB.SetColor(D3DXCOLOR(255, 0, 0, 100));

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_OBB.Collision(&WallOBB[nCnt]))
		{

			SetPos(D3DXVECTOR3(m_PrevLocalWorld._41, m_PrevLocalWorld._42, m_PrevLocalWorld._43));

		}
	}

	

	printf("X = %f Y = %f Z = %f\n", pos.x, pos.y, pos.z);
	
}

void CPlayer::Draw()
{
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// 鏡面反射を無効
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を無効
}

void CPlayer::AlphaDraw()
{


	m_OBB.Draw();

}

COBB CPlayer::GetOBB()
{

	return m_OBB;

}

