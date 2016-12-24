#include "Component.h"
#include "Factory.h"




CComponent::CComponent()
{

}

CComponent::~CComponent()
{
}


void CComponent::Initialize(CMesh Mesh){

	//m_Mesh = CFactory<CMesh>::GetInstance().Create();

}

void CComponent::Update()
{

	m_Transform.Translate();

}



void CComponent::UnInitialize(){

	delete this;

}



void CComponent::Draw()
{
	for (int nCnt = 0; nCnt < m_Mesh.GetMaterialNum(); nCnt++)
	{
		(*CDirectX3D::Create()->GetDevice())->SetMaterial(&m_Mesh.GetMeshMaterial()[nCnt]);	// マテリアル情報をセット

		(*CDirectX3D::Create()->GetDevice())->SetTexture(0,m_Mesh.GetTexture()[nCnt].GetTexture());

		m_Mesh.GetMeshdata()->DrawSubset(nCnt);
	}
	

}


