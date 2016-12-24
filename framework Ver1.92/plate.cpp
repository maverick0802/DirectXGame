#include "plate.h"


CPlate::CPlate()
{
}


CPlate::~CPlate()
{
}

void CPlate::Initialize(std::string TextureName, D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	//m_Texture = *CResourceLoader::Instance()->FindLoader<CTextureLoader>()->Load(ID::SCENE_NULL, TextureName);
	MakeVertex(pos, size, D3DXCOLOR(255,255,255,255));
}

void CPlate::Initialize(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{

	m_Texture.SetTexture(NULL);
	MakeVertex(pos, size, col);


}

void CPlate::Update()
{



}

void CPlate::Draw()
{
	(*CDirectX3D::Create()->GetDevice())->SetFVF(FVF_VERTEX_2D);
	if(m_Texture.GetTexture())
	(*CDirectX3D::Create()->GetDevice())->SetTexture(0, *m_Texture.GetTexture());
	else
	(*CDirectX3D::Create()->GetDevice())->SetTexture(0, NULL);

	(*CDirectX3D::Create()->GetDevice())->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,
														2,
														&m_VertexData[0],
														sizeof(VERTEX_2D)
														);
}
void CPlate::MakeVertex(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
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

	m_VertexData[0].rhw = 
	m_VertexData[1].rhw = 
	m_VertexData[2].rhw = 
	m_VertexData[3].rhw = 1.0f;

	m_VertexData[0].col = 
	m_VertexData[1].col = 
	m_VertexData[2].col =
	m_VertexData[3].col = D3DCOLOR_RGBA((int)col.r,(int)col.g,(int)col.b,(int)col.a);

	m_VertexData[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_VertexData[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_VertexData[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_VertexData[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_RGBA = col;
}

bool CPlate::FadeOut( float Second,float TargetAlpha)
{
	static bool bFlag = false;
	static float fStartTime = 0;
	static float fAlphaRenge = 0;
	if(!bFlag)
	{
		fStartTime = ::timeGetTime();
		fAlphaRenge = m_RGBA.a - TargetAlpha;
		bFlag = true;
	}
	float deltaTime = (::timeGetTime() - fStartTime) / 1000;

	if(deltaTime  < Second )
	{
		m_RGBA.a = fAlphaRenge * (1 - (deltaTime / Second));

		m_VertexData[0].col	=
		m_VertexData[1].col	=
		m_VertexData[2].col =
		m_VertexData[3].col = D3DCOLOR_RGBA((int)m_RGBA.r,(int)m_RGBA.g,(int)m_RGBA.b,(int)m_RGBA.a);
									
	}
	else if(bFlag) 
	{
		m_VertexData[0].col	=
		m_VertexData[1].col	=
		m_VertexData[2].col =
		m_VertexData[3].col = D3DCOLOR_RGBA((int)m_RGBA.r,(int)m_RGBA.g,(int)m_RGBA.b,(int)TargetAlpha);
		bFlag = false;
		return true;
	}
	
	return false;
}

bool CPlate::FadeIn( float Second, float TargetAlpha)
{

	static bool bFlag = false;
	static float fStartTime = 0;
	static float fAlphaRenge = 0;
	if(!bFlag)
	{
		fStartTime = ::timeGetTime();
		fAlphaRenge =  TargetAlpha - m_RGBA.a;
		bFlag = true;
	}
	float deltaTime = (::timeGetTime() - fStartTime) / 1000;

	if(deltaTime  < Second )
	{
		m_RGBA.a = fAlphaRenge * ((deltaTime / Second));

		m_VertexData[0].col	=
		m_VertexData[1].col	=
		m_VertexData[2].col =
		m_VertexData[3].col = D3DCOLOR_RGBA((int)m_RGBA.r,(int)m_RGBA.g,(int)m_RGBA.b,(int)m_RGBA.a);
									
	}
	else if(bFlag) 
	{
		m_VertexData[0].col	=
		m_VertexData[1].col	=
		m_VertexData[2].col =
		m_VertexData[3].col = D3DCOLOR_RGBA((int)m_RGBA.r,(int)m_RGBA.g,(int)m_RGBA.b,(int)TargetAlpha);
		bFlag = false;
		return true;
	}
	
	return false;
}
