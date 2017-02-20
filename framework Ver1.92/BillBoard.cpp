#include "BillBoard.h"
#include "ResourceLoader.h"
#include "ObjectMediator.h"

CBillBoard::CBillBoard()
{
}


CBillBoard::~CBillBoard()
{
}

void CBillBoard::Initialize(std::string TextureName, D3DXVECTOR3 pos, D3DXVECTOR2 size)
{

	CResourceLoader::Instance()->FindLoader<CTextureLoader>()->Load(TextureName, &m_Texture);
	MakeVertex(pos, size);
	m_Position = pos;
}


void CBillBoard::Update()
{
	//面の法線ベクトルを求める
	D3DXVECTOR3 vPos1 = m_VertexData[1].pos - m_VertexData[0].pos;
	D3DXVECTOR3 vPos2 = m_VertexData[2].pos - m_VertexData[0].pos;
	D3DXVECTOR3 vNormal = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 CameraForward = D3DXVECTOR3(0,0,0);
	D3DXVec3Cross(&vNormal,&vPos1,&vPos2);
	D3DXVec3Normalize(&vNormal,&vNormal);
	vNormal *= -1;
	CCamera* pCamera = CObjectMediator::Instance()->FindObject<CCamera>(0);
	CameraForward = pCamera->GetForward();
	CameraForward.y = 0;
	float cos = D3DXVec3Dot(&(vNormal),&CameraForward) / (D3DXVec3Length(&CameraForward) * D3DXVec3Length(&vNormal));
	if(cos > 1 || cos < -1)
		cos = (int)cos;
	float Angle = acos(cos);
	D3DXVECTOR3 vRightVec = m_VertexData[0].pos - m_VertexData[1].pos;
	if(D3DXVec3Dot(&vRightVec, &CameraForward) < 0)
		Angle *= -1;
	D3DXMATRIX RotMat;
	D3DXMatrixRotationYawPitchRoll(&RotMat,Angle * 0.2f,0,0);

	D3DXVec3TransformCoord( &m_VertexData[0].pos, &(m_VertexData[0].pos - m_Position), &RotMat);
	D3DXVec3TransformCoord( &m_VertexData[1].pos, &(m_VertexData[1].pos - m_Position), &RotMat);
	D3DXVec3TransformCoord( &m_VertexData[2].pos, &(m_VertexData[2].pos - m_Position), &RotMat);
	D3DXVec3TransformCoord( &m_VertexData[3].pos, &(m_VertexData[3].pos - m_Position), &RotMat);
	m_VertexData[0].pos += m_Position;
	m_VertexData[1].pos += m_Position;
	m_VertexData[2].pos += m_Position;
	m_VertexData[3].pos += m_Position;
	
}


void CBillBoard::Draw()
{


	(*CDirectX3D::Create()->GetDevice())->SetFVF(FVF_VERTEX_3D);
	(*CDirectX3D::Create()->GetDevice())->SetTexture(0, *m_Texture->GetTexture());
	(*CDirectX3D ::Create()->GetDevice())->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,
														2,
														&m_VertexData[0],
														sizeof(VERTEX_3D)
														);


}

void CBillBoard::MakeVertex(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{

	m_VertexData[0].pos.x = pos.x - size.x / 2;
	m_VertexData[0].pos.y = pos.y - size.y / 2;
	m_VertexData[0].pos.z = pos.z;
	m_VertexData[1].pos.x = pos.x + size.x / 2;
	m_VertexData[1].pos.y = pos.y - size.y / 2;
	m_VertexData[1].pos.z = pos.z;
	m_VertexData[2].pos.x = pos.x - size.x / 2;
	m_VertexData[2].pos.y = pos.y + size.y / 2;
	m_VertexData[2].pos.z = pos.z;
	m_VertexData[3].pos.x = pos.x + size.x / 2;
	m_VertexData[3].pos.y = pos.y + size.y / 2;
	m_VertexData[3].pos.z = pos.z;

	m_VertexData[0].col = 
	m_VertexData[1].col = 
	m_VertexData[2].col =
	m_VertexData[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_VertexData[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_VertexData[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_VertexData[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_VertexData[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}

