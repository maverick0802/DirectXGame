#pragma once
#include <map>
#include "ObjectManeger.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Sky.h"
#include "Camera.h"
#include "Field.h"
#include "Item.h"
#include "TitleLogo.h"
#include "GoalLogo.h"
#include "Tutorial.h"
#include "Result.h"
#include "TestObject.h"
#include "House.h"

template <typename T>

class CObjectFactory :public CObjectFactoryBase
{
	std::map<int,T*> m_ObjectMap;
	//std::iterator b;
	static bool bFlag;
public:
	CObjectFactory<T>(void):
	CObjectFactoryBase(ID::SCENE_NULL)
	{
	
		
	
	}

	CObjectFactory<T>(ID::SCENE_ID SceneID):
	CObjectFactoryBase(SceneID)
	{
	
		
	
	}

	~CObjectFactory<T>(void)
	{
			

	};

	static CObjectFactory<T>* Instance()
	{

		static CObjectFactory<T> Instance;
		if(!bFlag)
		{
			const char* type = typeid(Instance).raw_name();
			//Scene‚Í‚Ç‚Á‚©‚©‚çŽæ“¾‚Å‚«‚é‚æ‚¤‚É‚·‚é
			CObjectFactoryManeger::Instance()->ResistManeger(ID::SCENE_MAIN, &Instance, type);
			bFlag = true;
		}

		return &Instance;
	}

	T* CreateObject()
	{
		T* tmp;
		tmp = new T;
		tmp->SetObjectNumber(m_ObjectNum);
		m_ObjectMap.insert(std::make_pair(m_ObjectNum, tmp));
		m_ObjectNum++;
		return tmp;
	}

	void Remove(int ObjectNum)
	{
	
		if (m_ObjectMap.find(ObjectNum) != m_ObjectMap.end())
			m_ObjectMap[ObjectNum]->OnRemove();

	
	}

	T* GetObject(int ObjectNumber)
	{
		if (m_ObjectMap.find(ObjectNumber) != m_ObjectMap.end())
			return m_ObjectMap.find(ObjectNumber)->second;
		return NULL;
	}

	void Initialize()
	{
		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->Initialize();
			if (Itr_s->second->GetRemove())
				Itr_s = m_ObjectMap.erase(Itr_s);
			else
			Itr_s++;
		}

	}

	void Updata()
	{
	
		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->Update();
			if (Itr_s->second->GetRemove())
			{
				delete Itr_s->second;
				Itr_s = m_ObjectMap.erase(Itr_s);
			}
			else
				Itr_s++;
		}
	
	}

	void LateUpdata()
	{

		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->LateUpdate();
		
			if (Itr_s->second->GetRemove())
			{
				Itr_s = m_ObjectMap.erase(Itr_s);
			}
			else
				Itr_s++;
			
		}

	}

	void PrevDraw()
	{

		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->PrevDraw();
			if (Itr_s->second->GetRemove())
				Itr_s = m_ObjectMap.erase(Itr_s);
			else
				Itr_s++;
			
		}

	}

	void Draw()
	{
	
		//•s“§–¾“®‰æ
		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->Draw();
			if (Itr_s->second->GetRemove())
				Itr_s = m_ObjectMap.erase(Itr_s);
			else
				Itr_s++;
			
		}
	
	}

	void AlphaDraw()
	{
	
		//•s“§–¾“®‰æ
		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();


		//”¼“§–¾•`‰æ
		LPDIRECT3DDEVICE9  pDevice = *CDirectX3D::Create()->GetDevice();

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		while (Itr_s != Itr_e)
		{
			Itr_s->second->AlphaDraw();
			if (Itr_s->second->GetRemove())
				Itr_s = m_ObjectMap.erase(Itr_s);
			else
				Itr_s++;

		}

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	
	}


	void Release()
	{
		auto Itr_s = m_ObjectMap.begin();
		auto Itr_e = m_ObjectMap.end();

		while (Itr_s != Itr_e)
		{
			Itr_s->second->UnInitialize();
			delete Itr_s->second;
			Itr_s = m_ObjectMap.erase(Itr_s);
			
		}
		bFlag = false;
		m_ObjectNum = 0;
	}
};

template <typename T>
bool CObjectFactory<T>::bFlag;

