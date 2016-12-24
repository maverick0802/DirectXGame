#pragma once

#include "Singleton.h"
#include "FactoryBase.h"
#include <vector>

class CFactoryManeger:public CSingleton<CFactoryManeger>
{

//*******ïœêî*******
private:
	std::vector<CFactoryBase*> FactoryList;
public:


private:
	void AddFactory(CFactoryBase*);
public:
	CFactoryManeger();
	~CFactoryManeger();
};

