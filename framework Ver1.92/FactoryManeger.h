#pragma once

#include "Singleton.h"
#include "FactoryBase.h"
#include <vector>

class CFactoryManeger:public CSingleton<CFactoryManeger>
{

//*******�ϐ�*******
private:
	std::vector<CFactoryBase*> FactoryList;
public:


private:
	void AddFactory(CFactoryBase*);
public:
	CFactoryManeger();
	~CFactoryManeger();
};

