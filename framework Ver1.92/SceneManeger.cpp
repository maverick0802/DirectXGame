#include "SceneManeger.h"
#include "SceneMediator.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"
#include "ResourceManeger.h"
#include "ObjectManeger.h"
#include "ResourceLoader.h"

/////////////////////////////////////////
//�@�R���X�g���N�^
////////////////////////////////////////
CSceneManeger::CSceneManeger(void):
m_NowScene(NULL	)
{
}

/////////////////////////////////////////
//�@�f�X�g���N�^
////////////////////////////////////////
CSceneManeger::~CSceneManeger(void)
{
	CObjectFactoryManeger::Instance()->AllRelease();	//�I�u�W�F�N�g�̑S���
	CResourceManeger::Instance()->Release();

	delete m_NowScene;

}


void CSceneManeger::Initialize()
{

	m_NowScene->Initialize();

}

void CSceneManeger::Updata()
{

	m_NowScene->Updata();

}

void CSceneManeger::LateUpdata()
{

	m_NowScene->LateUpdata();

}

void CSceneManeger::PrevDraw()
{

	m_NowScene->PrevDraw();

}



void CSceneManeger::Draw()
{

	m_NowScene->Draw();

}


/////////////////////////////////////////
//�@�V�[���̐؂�ւ�
////////////////////////////////////////
void CSceneManeger::SwapScene()
{
	//���̃V�[�����o�^����Ă邩�m�F
	ID::SCENE_ID SceneID = CSceneMediator::Instance()->GetNextScene();

	if (SceneID != ID::SCENE_NULL)
	{
		//---����Ă�����---
		
		//���݂̃V�[���̉������
		if (m_NowScene)
		{
			m_NowScene->Release();
			delete m_NowScene;
			m_NowScene = NULL;
		}

		//���̃V�[���̐���
		switch (SceneID)
		{
		case ID::SCENE_TITLE:
			
			m_NowScene = new CTitleScene();
			break;

		case ID::SCENE_MAIN:
			m_NowScene = new CMainScene();

			break;

		case ID::SCENE_END:
			m_NowScene = new CEndScene();
			break;
		}

		//���̃V�[���𐶐������̂ŕύX
		CSceneMediator::Instance()->SetNextScene(ID::SCENE_NULL);
		CSceneMediator::Instance()->SetNowScene(SceneID);
		
		//���݃V�[���̏������i���������̃V�[���Ŏw�肵���V�[���j
		m_NowScene->Initialize();

	}



}
