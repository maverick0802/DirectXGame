#pragma once
#include "ManegerBase.h"
#include "Singleton.h"
#include <map>
#include <string>

template <class T>
class CManeger :
	public CManegerBase,public CSingleton<CManeger<T>>
{
	friend CSingleton < CManeger<T> >;

//*******•Ï”*******
private:
	std::map<int, std::map<std::string, std::map<int, T*>>>	 m_List;
public:

//*******ŠÖ”*******
private:
	CManeger(){};
	~CManeger(){};

public:
	T& Resist(int Layer, std::string Tag, T* Resister)
	{
	

		if (m_List.find(Layer) == m_List.end())
		{
			std::map<std::string, std::map<int, T*>> temp;
			m_List.insert(std::make_pair(Layer, temp));
			m_List[Layer][Tag].insert(std::make_pair(0, Resister));

		}
		else if (m_List[Layer].find(Tag) == m_List[Layer].end())
		{
			std::map<int, T*> temp;
			m_List[Layer].insert(std::make_pair(Tag, temp));
			m_List[Layer][Tag].insert(std::make_pair(0, Resister));

		}
		else if (m_List[Layer][Tag].find(0) == m_List[Layer][Tag].end())
		{

			m_List[Layer][Tag].insert(std::make_pair(0, Resister));

		}

		return *m_List[Layer][Tag][m_List[Layer][Tag].size() - 1];
	
	}


	HRESULT Destory(std::string, int, int)
	{

		
		return S_OK;
	}

	HRESULT AllDestory()
	{

		auto LayerIterator_Start = m_List.begin();
		auto LayerIterator_End = m_List.end();

		for (; LayerIterator_Start != LayerIterator_End; LayerIterator_Start++)
		{
			auto TagIterator_Start = LayerIterator_Start->second.begin();
			auto TagIterator_End = LayerIterator_Start->second.end();


			for (; TagIterator_Start != TagIterator_End; TagIterator_Start++)
			{

				auto ElementIterator_Start = TagIterator_Start->second.begin();
				auto ElementIterator_End = TagIterator_Start->second.end();

				for (; ElementIterator_Start != ElementIterator_End; ElementIterator_Start++)
				{



					ElementIterator_Start->second->UnInitialize();

				}


			}

		}

		return S_OK;
	}

};

