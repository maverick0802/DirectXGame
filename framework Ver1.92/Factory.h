#pragma once
#include "FactoryBase.h"
#include "FactoryManeger.h"
#include "Singleton.h"
#include <vector>

template <class T>
class CFactory : public CFactoryBase,public CSingleton<CFactory<T>>
{
	friend CSingleton < CFactory<T> >;
//************ƒƒ“ƒoŠÖ”*******************
private :

//‚È‚µ

public:

//************ƒƒ“ƒo•Ï”*******************
private:
	~CFactory(){}
	CFactory(){}


public:
	T* Create()
	{
		return new T;
	}

	HRESULT Destory(){ return S_OK; }
	HRESULT AllDestory(){ return S_OK; }


};

