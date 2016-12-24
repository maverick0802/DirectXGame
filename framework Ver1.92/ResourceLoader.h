#pragma once
#include "ResourceBase.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
#include "LoaderBase.h"
#include <memory>

class CResourceLoader
{


	ID::RESOURCE_ID ExtractResourceID(std::string FileName);

public:
	static CResourceLoader* Instance();

	template<typename T>
	T* FindLoader()
	{
	
	
		return T::Instance();
	
	}
	CResourceLoader();
	~CResourceLoader();
};

