#include "Camera.h"
#include "ObjectMediator.h"
#include "DXInput.h"
CCamera::CCamera()
{
}

CCamera::CCamera(ID::SCENE_ID SceneID)
{

	m_SceneID = SceneID;
	//m_ObjID = ID::O
}


CCamera::~CCamera()
{
}


void CCamera::Initialize()
{

	C3DObj::Initialize();

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_CameraMat);
	D3DXMatrixIdentity(&m_matProj);
	m_EyePt		= D3DXVECTOR3(0, 30, -60);
	m_LookatPt	= D3DXVECTOR3(0, 20, 0);
	m_UpVec		= D3DXVECTOR3(0, 1, 0);
	SetPos(m_EyePt);
	//カメラのセット
	Setup();

}

void CCamera::Update()
{
	C3DObj::Update();
	C3DObj* pPlayer = CObjectMediator::Instance()->FindObject<CPlayer>( 0);
	D3DXVECTOR3 pos = GetPos() - GetLookAtPos();


	D3DXMATRIX		world/* = m_CameraMat*/;
	D3DXMATRIX		ZAxisMat;
	D3DXQUATERNION	QuonZ;
	D3DXVECTOR3		ZAxis = GetForward();
	D3DXVECTOR3		LookAt = GetLookAtPos();
	D3DXVECTOR2		Trans;
	D3DXVECTOR3		Trans2 = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3*	CameraZAxis;
	D3DXQUATERNION	TransQuon;
	D3DXMATRIX		TransRotMat;
	D3DXVECTOR3		CameraAxisX;
	D3DXVECTOR3		CameraAxisY;
	D3DXVECTOR3		CameraAxisZ;

	float			AngleZ = 0;		//Z軸の回転角（一応あるけどたぶん使わない）

	//マウスの移動量取得
	long MouseX = CDXInput::GetMouseAxis(MOUSE_X);
	long MouseY = CDXInput::GetMouseAxis(MOUSE_Y);

	D3DXMatrixIdentity(&world);
	//Z軸回転の処理
	D3DXQuaternionRotationAxis(&QuonZ, &ZAxis, D3DXToRadian(AngleZ));
	D3DXMatrixRotationQuaternion(&ZAxisMat, &QuonZ);
	D3DXMatrixMultiply(&world, &ZAxisMat, &world);

	Trans = D3DXVECTOR2(MouseX, MouseY);		//経度上の移動方向（実際はマウスから取得するけど今は仮置き）
	D3DXVec2Normalize(&Trans, &Trans);
	//D3DXVec3TransformCoord(&Trans2, &Trans, &world);

	//マウスの移動量が取得できれば姿勢行列を更新
	if (1/*Trans2.x != 0 || Trans2.y != 0 || Trans2.z != 0*/) 
	{
		D3DXQUATERNION TransQuonX;
		D3DXQUATERNION TransQuonY;
		D3DXMATRIX TransMatX;
		D3DXMATRIX TransMatY;
		D3DXVECTOR3 TransAxisY;
		D3DXMatrixIdentity(&TransMatX);
		D3DXMatrixIdentity(&TransMatY);

		D3DXQuaternionRotationAxis(&TransQuonX, &D3DXVECTOR3(0, 1, 0), D3DXToRadian(3.0f) * Trans.x);	//算出した回転軸での既定の回転量だけ回転するクォータニオンを作成
		D3DXMatrixRotationQuaternion(&TransMatX, &TransQuonX);
		

		if (D3DXVec3Dot((D3DXVECTOR3*)m_CameraMat.m[2], &D3DXVECTOR3(1, 0, 0)) != 0)
		{
			D3DXVec3TransformCoord(&TransAxisY, &D3DXVECTOR3(1, 0, 0) , &m_CameraMat);
			D3DXQuaternionRotationAxis(&TransQuonY, &TransAxisY, D3DXToRadian(3.0f) * Trans.y);	//算出した回転軸での既定の回転量だけ回転するクォータニオンを作成
			D3DXMatrixRotationQuaternion(&TransMatY, &TransQuonY);
		}

		D3DXMatrixMultiply(&TransRotMat, &TransMatX, &TransMatY);
		D3DXVec3TransformCoord(&pos, &pos, &TransRotMat);					//座標位置に回転行列を適応

		CameraAxisZ =  - pos;
		D3DXVec3Normalize(&CameraAxisZ, &CameraAxisZ);

		memcpy(&CameraAxisY, world.m[1], sizeof(D3DXVECTOR3));
		D3DXVec3Cross(&CameraAxisX, &CameraAxisY, &CameraAxisZ);
		D3DXVec3Normalize(&CameraAxisX, &CameraAxisX);

		D3DXVec3Cross(&CameraAxisY, &CameraAxisZ, &CameraAxisX);
		D3DXVec3Normalize(&CameraAxisY, &CameraAxisY);

		D3DXMatrixIdentity(&world);
		memcpy(world.m[0], &CameraAxisX, sizeof(D3DXVECTOR3));
		memcpy(world.m[1], &CameraAxisY, sizeof(D3DXVECTOR3));
		memcpy(world.m[2], &CameraAxisZ, sizeof(D3DXVECTOR3));
		m_CameraMat = world;
	}

	D3DXVECTOR3 PlayerMove = pPlayer->GetPos() - pPlayer->GetPrevPos();
	D3DXVECTOR3 pos2;

	m_LookatPt += PlayerMove;
	pos2 = m_LookatPt + pos;

	memcpy(world.m[3], &pos2, sizeof(D3DXVECTOR3));
	//world._44 = 1.0f;

	D3DXMatrixInverse(&m_matView, NULL, &world);

	SetWorld(world);
	//SetPos(pos);
}

void CCamera::LateUpdate()
{
	C3DObj::LateUpdate();
	(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_VIEW, &m_matView);
	
}


void CCamera::Draw()
{


}

void CCamera::UnInitialize()
{

	

}

HRESULT CCamera::Setup(){

	SetupLight();
	SetupCamera();

	return S_OK;
}


HRESULT CCamera::SetupCamera(){

	D3DXMatrixLookAtLH(&m_matView, &GetPos(), &m_LookatPt, &m_UpVec);
	(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(45), (float)CApplicationBase::GetWidth() / CApplicationBase::GetHight(), 1.f, 10000.f);
	(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

HRESULT CCamera::SetupLight(){

	(*CDirectX3D::Create()->GetDevice()) ->SetRenderState(D3DRS_ZENABLE, TRUE);

	//ディレクショナルライトを設定する。
	// Render（Draw）でD3DRS_LIGHTINGを有効にしておかないと、意味がない。
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Diffuse.g = mtrl.Diffuse.b = mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient = mtrl.Diffuse;
	(*CDirectX3D::Create()->GetDevice())->SetMaterial(&mtrl);

	D3DXVECTOR3 vecDir;
	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(D3DLIGHT9));
	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Diffuse.r = 1.f;
	Light.Diffuse.g = 1.f;
	Light.Diffuse.b = 1.f;
	Light.Diffuse.a = 1.f;
	Light.Ambient.r = 0.5f;
	Light.Ambient.g = 0.5f;
	Light.Ambient.b = 0.5f;
	Light.Ambient.a = 0.5f;
	Light.Specular = Light.Ambient;
	vecDir = D3DXVECTOR3(0.f, -1.f, 0.f);
	D3DXVec3Normalize((D3DXVECTOR3*)&Light.Direction, &vecDir);

	Light.Range = 1000.f;
	(*CDirectX3D::Create()->GetDevice())->SetLight(0, &Light);
	(*CDirectX3D::Create()->GetDevice())->LightEnable(0, TRUE);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// 最後に環境光を設定する。
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	(*CDirectX3D::Create()->GetDevice())->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	(*CDirectX3D::Create()->GetDevice())->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	(*CDirectX3D::Create()->GetDevice())->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	return S_OK;
}

///////////////////////////////////////
// 注視点取得
///////////////////////////////////////
D3DXVECTOR3 CCamera::GetLookAtPos()
{

	return m_LookatPt;

}

///////////////////////////////////////
// カメラの上方ベクトル取得
///////////////////////////////////////
D3DXVECTOR3 CCamera::GetUpVec()
{

	return m_UpVec;

}

///////////////////////////////////////
// カメラの姿勢行列取得
///////////////////////////////////////
D3DXMATRIX	CCamera::GetCameraMat()
{

	return m_CameraMat;

}

