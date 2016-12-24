#pragma once
#include "GameObject.h"
#include "ObjectManeger.h"
#include "ObjectFactory.h"
#include <typeinfo>

class CObjectMediator
{
public:
	CObjectMediator(void);
	~CObjectMediator(void);
	static CObjectMediator* Instance();

	template<typename T>
	T* FindObject(int ObjectNumber)
	{
		return CObjectFactory<T>::Instance()->GetObject(ObjectNumber);

	}

	template<typename T>
	void RemoveObject(int ObjectNum)
	{
		CObjectFactory<T>::Instance()->Remove(ObjectNum);
	
	}

};

