#include "FactoryManeger.h"


CFactoryManeger::CFactoryManeger()
{
}


CFactoryManeger::~CFactoryManeger()
{
}

void CFactoryManeger::AddFactory(CFactoryBase* ResistFactory)
{
	
	FactoryList.push_back(ResistFactory);

}