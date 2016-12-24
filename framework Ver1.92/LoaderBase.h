#pragma once
#include"ResourceBase.h"
#include <string>
#include <map>

class LoaderBase
{
protected:
	ID::RESOURCE_ID m_ResourceID;
	std::map<std::string, CResourceBase*> m_map;
public:
	LoaderBase();
	LoaderBase(ID::RESOURCE_ID);
	~LoaderBase();
	virtual CResourceBase* CheckMap(std::string);
	virtual HRESULT ResistMap(std::string, CResourceBase*);
	void Release();

};

