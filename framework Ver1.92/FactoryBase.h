#pragma once
#include <Windows.h>


class CFactoryBase
{

public:
	virtual HRESULT  Destory() = 0;
	virtual HRESULT AllDestory() = 0;

};

