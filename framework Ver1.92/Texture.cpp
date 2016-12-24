#include "Texture.h"


CTexture::CTexture(ID::SCENE_ID SceneID):
CResourceBase(SceneID),
m_Texturedata(NULL)
{
	m_ResourceID = ID::RESOURCE_TEXTURE;

}

CTexture::CTexture():
CResourceBase(ID::SCENE_NULL),
m_Texturedata(NULL)
{

	m_ResourceID = ID::RESOURCE_TEXTURE;

}


CTexture::~CTexture()
{

	int a;
	a = 100;
}



void CTexture::Load(std::string MaterialName)
{

	
}

LPDIRECT3DTEXTURE9* CTexture::GetTexture()
{

	return m_Texturedata;

}

void CTexture::SetTexture(LPDIRECT3DTEXTURE9* Texturedata)
{

	m_Texturedata = Texturedata;

}

void CTexture::Release()
{
	if(m_Texturedata)
	{	
		delete m_Texturedata;
		m_Texturedata = NULL;
	}
}
