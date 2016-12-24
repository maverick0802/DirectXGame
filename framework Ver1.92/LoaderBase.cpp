#include "LoaderBase.h"
#include "ResourceManeger.h"
LoaderBase::LoaderBase()
{


}

LoaderBase::LoaderBase(ID::RESOURCE_ID ResourceID)
{

	m_ResourceID = ResourceID;
	CResourceManeger::Instance()->Resist(m_ResourceID, this);

}



LoaderBase::~LoaderBase()
{
}

CResourceBase* LoaderBase::CheckMap(std::string FileName)
{
	if (m_map.find(FileName) != m_map.end())
	{
		return m_map[FileName];
	}
	return NULL;
}

HRESULT LoaderBase::ResistMap(std::string FileName, CResourceBase* Recive)
{

	if (m_map.find(FileName) == m_map.end())
	{
		m_map.insert(std::make_pair(FileName, Recive));
		return S_OK;
	}
	return E_FAIL;

}

void LoaderBase::Release()
{

	auto Itr_S = m_map.begin();
	auto Itr_E = m_map.end();

	while (Itr_S != Itr_E)
	{
		Itr_S->second->Release();
		delete Itr_S->second;
		Itr_S = m_map.erase(Itr_S);

	}


}
