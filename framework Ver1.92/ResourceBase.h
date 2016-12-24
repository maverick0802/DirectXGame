#pragma once
#include "GameObject.h"
#include <string>

////////////////////////////////////////////////////////////////////
//　CResourceBase
//　Author : 杉浦　宏紀　
//
//	Detail：
//	リソース系の基底クラス
//	
//　History：
//　6/25 クラス作成 　
//
////////////////////////////////////////////////////////////////////



namespace ID{

	typedef enum
	{
		RESOURCE_NONE = -1,
		RESOURCE_MESH = 200,
		RESOURCE_TEXTURE

	}RESOURCE_ID;
	

}


class CResourceBase
{
	
protected:
	ID::SCENE_ID	m_SceneID;			//このリソースが読み込まれたSceneのID
	ID::RESOURCE_ID m_ResourceID;		//リソースの種類
	int				m_ResourceNumber;	//リソースの固有番号（唯一無二）
	int				m_Reference;		//参照カウンター

public:
	CResourceBase();
	CResourceBase(ID::SCENE_ID){};
	virtual ~CResourceBase();
	ID::SCENE_ID GetSceneID();
	ID::RESOURCE_ID GetResourceID();
	int GetResourceNumber();
	virtual void Release() = 0;

};

