#pragma once
#include "GameObject.h"
#include <string>

////////////////////////////////////////////////////////////////////
//�@CResourceBase
//�@Author : ���Y�@�G�I�@
//
//	Detail�F
//	���\�[�X�n�̊��N���X
//	
//�@History�F
//�@6/25 �N���X�쐬 �@
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
	ID::SCENE_ID	m_SceneID;			//���̃��\�[�X���ǂݍ��܂ꂽScene��ID
	ID::RESOURCE_ID m_ResourceID;		//���\�[�X�̎��
	int				m_ResourceNumber;	//���\�[�X�̌ŗL�ԍ��i�B�ꖳ��j
	int				m_Reference;		//�Q�ƃJ�E���^�[

public:
	CResourceBase();
	CResourceBase(ID::SCENE_ID){};
	virtual ~CResourceBase();
	ID::SCENE_ID GetSceneID();
	ID::RESOURCE_ID GetResourceID();
	int GetResourceNumber();
	virtual void Release() = 0;

};

