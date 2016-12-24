#pragma once
#include "Texture.h"
#include "LoaderBase.h"
#include <memory>
#include <map>


class CTextureLoader :public LoaderBase
{
	std::map<std::string, CTexture> m_map;

public:

	static CTextureLoader* Instance();
	void Load(std::string,CTexture**);
	CTextureLoader();
	~CTextureLoader();
};

