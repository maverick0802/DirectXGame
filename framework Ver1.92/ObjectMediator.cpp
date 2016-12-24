#include "ObjectMediator.h"


CObjectMediator::CObjectMediator(void)
{
}


CObjectMediator::~CObjectMediator(void)
{
}

CObjectMediator* CObjectMediator::Instance()
{

	static CObjectMediator Instance;

	return &Instance;

}