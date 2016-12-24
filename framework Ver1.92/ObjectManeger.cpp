#include "ObjectManeger.h"


CObjectFactoryManeger::CObjectFactoryManeger()
{



}

CObjectFactoryManeger::~CObjectFactoryManeger()
{



}

CObjectFactoryManeger* CObjectFactoryManeger::Instance()
{


	static CObjectFactoryManeger Instance;


	return &Instance;
}

void CObjectFactoryManeger::ResistManeger(ID::SCENE_ID SceneID, CObjectFactoryBase* Resist, const char* TypeName)
{
	//const char* TypeName = typeid(Resist).name();
	if (m_ObjectFactoryMap.find(SceneID) == m_ObjectFactoryMap.end())
	{
		std::map<char*, CObjectFactoryBase*> tmp;
		tmp.insert(std::make_pair((char*)TypeName, Resist));
		m_ObjectFactoryMap.insert(std::make_pair(SceneID, tmp));


	}
	else if (m_ObjectFactoryMap.find(SceneID)->second.find((char*)TypeName) == m_ObjectFactoryMap.find(SceneID)->second.end())
	{

		m_ObjectFactoryMap.find(SceneID)->second.insert(std::make_pair((char*)TypeName, Resist));

	}

}

CObjectFactoryBase* CObjectFactoryManeger::FindFactory(ID::SCENE_ID SceneID, char* TypeName)
{

	if (m_ObjectFactoryMap.find(SceneID) != m_ObjectFactoryMap.end())
		if (m_ObjectFactoryMap.find(SceneID)->second.find(TypeName) != m_ObjectFactoryMap.end()->second.end())
			m_ObjectFactoryMap.find(SceneID)->second.find(TypeName)->second;
	return NULL;
}

////////////////////////////////
// 初期化
////////////////////////////////
void CObjectFactoryManeger::Initialize()
{
	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();


	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->Initialize();

			Itr_Obj_s++;
		}

		Itr_s++;
	}

}

////////////////////////////////
// 更新
////////////////////////////////
void CObjectFactoryManeger::Updata()
{
	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();


	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->Updata();

			Itr_Obj_s++;
		}

		Itr_s++;

	}

}

////////////////////////////////
// 遅延更新（のろまさん用）
////////////////////////////////
void CObjectFactoryManeger::LateUpdata()
{

	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();


	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->LateUpdata();

			Itr_Obj_s++;
		}

		Itr_s++;

	}

}

////////////////////////////////
// 描画前描画（せっかちさん用）
////////////////////////////////
void CObjectFactoryManeger::PrevDraw()
{
	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();


	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->PrevDraw();

			Itr_Obj_s++;
		}

		Itr_s++;

	}

}

////////////////////////////////
// 描画（せっかちさん用）
////////////////////////////////
void CObjectFactoryManeger::Draw()
{
	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();


	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->Draw();

			Itr_Obj_s++;
		}

		Itr_s ++ ;

	}

}

////////////////////////////////
// 全開放
////////////////////////////////
void CObjectFactoryManeger::AllRelease()
{

	auto Itr_s = m_ObjectFactoryMap.begin();
	auto Itr_e = m_ObjectFactoryMap.end();

	while (Itr_s != Itr_e)
	{
		auto Itr_Obj_s = Itr_s->second.begin();
		auto Itr_Obj_e = Itr_s->second.end();

		while (Itr_Obj_s != Itr_Obj_e)
		{

			Itr_Obj_s->second->Release();

			Itr_Obj_s = Itr_s->second.erase(Itr_Obj_s);
		}

		Itr_s = m_ObjectFactoryMap.erase(Itr_s);
	}

}