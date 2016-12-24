#pragma once
#include "FactoryBase.h"
#include "FactoryManeger.h"
#include "Singleton.h"
#include <vector>

template <class T>
class CFactory : public CFactoryBase,public CSingleton<CFactory<T>>
{
	friend CSingleton < CFactory<T> >;
//************メンバ関数*******************
private :

//なし

public:

//************メンバ変数*******************
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

