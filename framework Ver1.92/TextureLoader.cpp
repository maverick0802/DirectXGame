#include "TextureLoader.h"
#include "ResourceManeger.h"

const std::string TEXTURE_FOLDER = "data/TEXTURE/";

CTextureLoader::CTextureLoader():
LoaderBase(ID::RESOURCE_TEXTURE)
{
}


CTextureLoader::~CTextureLoader()
{
	//Release();
}


CTextureLoader* CTextureLoader::Instance()
{

	static CTextureLoader Instance;

	return &Instance;
}


void CTextureLoader::Load( std::string FileName, CTexture** Recive)
{	
	CTexture* ReciveData = NULL;
	if ( *Recive = dynamic_cast<CTexture*>( CheckMap(FileName)))
	{
		return ;
	}

	ReciveData = new CTexture();
	HRESULT hr;
	LPDIRECT3DTEXTURE9* a = new LPDIRECT3DTEXTURE9;
	std::string AllFilePass = TEXTURE_FOLDER + FileName;
	hr = D3DXCreateTextureFromFile(
		*CDirectX3D::Create()->GetDevice(),
		AllFilePass.c_str(),
		a);

	if (FAILED(hr))
	ReciveData->SetTexture(NULL);
	else
	{
		ReciveData->SetTexture(a);
		ResistMap(FileName, ReciveData);
	}

	*Recive = ReciveData;
	return ;
}

