#include "Transform.h"
#include <map>

CTransform::CTransform()
{
}


CTransform::~CTransform()
{
}



void CTransform::SetPosition(D3DXVECTOR3 Position)
{

	m_Position = Position;
}


D3DXVECTOR3 CTransform::GetPosition()
{

	return m_Position;

}

void CTransform::Translate()
{

	D3DXMatrixTranslation(&m_World, 10, 0, 0);

	
	(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_WORLD, &m_World);
	

}


