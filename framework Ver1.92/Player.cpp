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
}

void CPlayer::Update()
{
	C3DObj::Update();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 Move = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3	vCrossPoint;
	D3DXVECTOR3 CameraForword;
	D3DXVECTOR3 PlayerForword = GetForward();
	D3DXMATRIX  world = GetWorld();
	D3DXMATRIX  RotMat;
	float CosA;
	float Angle = 0;
	bool bMove = false;

	pos.y += 10.0f;
	
	//フィールドとのあたり判定
	C3DObj* pField = CObjectMediator::Instance()->FindObject<CField>(0);
	if(pField->Intersect(pos, D3DXVECTOR3(0, -1, 0), true, &vCrossPoint))
		pos.y = vCrossPoint.y;
	else
		pos.y = 0.0f;
	//建物との判定
	D3DXVECTOR3 tmp = pos;
	tmp.y += 20.0f;
	vCrossPoint = D3DXVECTOR3(0,0,0);
	C3DObj* pHouse = CObjectMediator::Instance()->FindObject<CHouse>(0);
	if(pHouse->Intersect(tmp, D3DXVECTOR3(tmp.x,tmp.y - 30,tmp.z), false, &vCrossPoint))
		pos.y = vCrossPoint.y;
	else
		pos.y = pos.y;

	//プレイヤーの移動
	CCamera* pCamera = CObjectMediator::Instance()->FindObject<CCamera>(0);
	C3DObj* pGoal = CObjectMediator::Instance()->FindObject<CGoalLogo>(0);

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
		Move = PlayerForword * SPEED_FORWORD;
		pos += Move;
	}

	//if (pField->Intersect(D3DXVECTOR3(pos.x, pos.y + 5, pos.z), D3DXVECTOR3(pos.x, pos.y + 5, pos.z) +  (PlayerForword * 10), false, &vCrossPoint))
	//{
	//	D3DXVECTOR3 vLength = D3DXVECTOR3(pos.x, pos.y + 5, pos.z) - vCrossPoint;
	//	float fLength;

	//	fLength = D3DXVec3Length(&vLength);
	//	if (fLength < 10)
	//		pos = GetPrevPos();

	//}


	//if(pGoal->GetPos().x - 10 < GetPos().x && pGoal->GetPos().x + 10 > GetPos().x &&
	//	pGoal->GetPos().z - 10 < GetPos().z && pGoal->GetPos().z + 10 > GetPos().z)
	//{

	//	C3DObj* tmp = CObjectMediator::Instance()->FindObject<CItem>(ID::SCENE_NULL,0);
	//	if(tmp == NULL)
	//		CSceneMediator::Instance()->SetNextScene(ID::SCENE_END);
	//}
	D3DXMatrixMultiply(&world, &world, &RotMat);

	SetWorld(world);
	SetPos(pos);
	

	printf("X = %f Y = %f Z = %f\n", pos.x, pos.y, pos.z);
	
}

void CPlayer::Draw()
{
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// 鏡面反射を無効
	C3DObj::Draw();
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を無効

}

