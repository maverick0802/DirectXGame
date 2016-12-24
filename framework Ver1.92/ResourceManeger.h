#pragma once
#include "Texture.h"
#include "Mesh.h"
#include <map>
#include <string>
#include <memory>
#include "LoaderBase.h"

typedef std::map<ID::RESOURCE_ID, LoaderBase*>				LODER_MAP;

class CResourceManeger
{

	LODER_MAP m_LoaderMap;
public:
	static CResourceManeger* Instance();
	void Release();
	void Resist(ID::RESOURCE_ID ,LoaderBase* );
	CResourceManeger();
	~CResourceManeger();
};

