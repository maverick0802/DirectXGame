#include "TestObject.h"
#include "ResourceLoader.h"


CTestObject::CTestObject()
{
}


CTestObject::~CTestObject()
{
}

void CTestObject::Initialize()
{
	CResourceLoader::Instance()->FindLoader<CMeshLoader>()->Load("Player_Ver7.x", &Mesh);
}

void CTestObject::Draw()
{

	Mesh->Draw(m_World);

}
