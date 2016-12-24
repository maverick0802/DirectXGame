#pragma once
#include "DirectX3D.h"
#include <string>
#include "ResourceBase.h"

class CTexture: public CResourceBase
{
private:
	LPDIRECT3DTEXTURE9 *m_Texturedata;
public:
private:
public:
	CTexture(ID::SCENE_ID);
	CTexture();
	~CTexture();
	virtual void Release();
	void Load(std::string);
	LPDIRECT3DTEXTURE9* GetTexture();
	void SetTexture(LPDIRECT3DTEXTURE9*);
};

