#include "SceneManeger.h"
#include "SceneMediator.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"
#include "ResourceManeger.h"
#include "ObjectManeger.h"
#include "ResourceLoader.h"

/////////////////////////////////////////
//　コンストラクタ
////////////////////////////////////////
CSceneManeger::CSceneManeger(void):
m_NowScene(NULL	)
{
}

/////////////////////////////////////////
//　デストラクタ
////////////////////////////////////////
CSceneManeger::~CSceneManeger(void)
{
	CObjectFactoryManeger::Instance()->AllRelease();	//オブジェクトの全解放
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
//　シーンの切り替え
////////////////////////////////////////
void CSceneManeger::SwapScene()
{
	//次のシーンが登録されてるか確認
	ID::SCENE_ID SceneID = CSceneMediator::Instance()->GetNextScene();

	if (SceneID != ID::SCENE_NULL)
	{
		//---されていたら---
		
		//現在のシーンの解放処理
		if (m_NowScene)
		{
			m_NowScene->Release();
			delete m_NowScene;
			m_NowScene = NULL;
		}

		//次のシーンの生成
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

		//次のシーンを生成したので変更
		CSceneMediator::Instance()->SetNextScene(ID::SCENE_NULL);
		CSceneMediator::Instance()->SetNowScene(SceneID);
		
		//現在シーンの初期化（さっき次のシーンで指定したシーン）
		m_NowScene->Initialize();

	}



}
