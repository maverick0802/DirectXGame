#pragma once
#include <map>
#include <typeinfo>
#include "GameObject.h"
#include "ObjectFactoryBase.h"

class CObjectFactoryManeger
{
	std::map<ID::SCENE_ID, std::map<char*,CObjectFactoryBase*>> m_ObjectFactoryMap;

public:
	CObjectFactoryManeger::CObjectFactoryManeger();

	CObjectFactoryManeger::~CObjectFactoryManeger();

	static CObjectFactoryManeger* Instance();

	void ResistManeger(ID::SCENE_ID SceneID, CObjectFactoryBase* Resist, const char*);

	CObjectFactoryBase* FindFactory(ID::SCENE_ID SceneID, char* TypeName);

	void Initialize();

	void Updata();

	void LateUpdata();

	void PrevDraw();

	void Draw();

	void AllRelease();
};

