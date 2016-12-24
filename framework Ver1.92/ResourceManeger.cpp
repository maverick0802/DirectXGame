#include "ResourceManeger.h"
#include <List>

const std::string FILEPASS_MESH = "data/MODEL/";
const std::string FILEPASS_TEXTURE = "data/TEXTURE/";

CResourceManeger::CResourceManeger()
{
}


CResourceManeger::~CResourceManeger()
{

}


CResourceManeger* CResourceManeger::Instance()
{

	static CResourceManeger Instance;

	return &Instance;
}




void CResourceManeger::Resist(ID::RESOURCE_ID ResourceID, LoaderBase* Loader)
{

	if (m_LoaderMap.find(ResourceID) == m_LoaderMap.end())
	{
		m_LoaderMap.insert(std::make_pair(ResourceID, Loader));
		return;
	}

}



void CResourceManeger::Release()
{
	auto Itr_S = m_LoaderMap.begin();
	auto Itr_E = m_LoaderMap.end();

	while(Itr_S != Itr_E)
	{

		Itr_S->second->Release();
		Itr_S = m_LoaderMap.erase(Itr_S);
	}

}


