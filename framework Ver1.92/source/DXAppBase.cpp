#include "ApplicationBase.h"
#include "DXAppBase.h"
#include "d3dx9.h"
#include "dinput.h"
#include <string.h>
#include "..//Player.h"
#include "..//ObjectFactory.h"
#include "..//ObjectMediator.h"
#include "..//DXInput.h"
#include "..//ResourceManeger.h"
//=============================================
//ライブラリのリンク
//=============================================

#if 1
#pragma comment (lib,"d3d9.lib")			//自プログラムにライブラリを結合させる
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"winmm.lib")
#endif



//=============================================
//マクロ定義
//=============================================
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)

////*******************************************
////構造体宣言
////*******************************************
//typedef struct {
//	D3DXVECTOR3 pos;						//頂点座標
//	float		rhw;						//テクスチャ
//	D3DCOLOR	col;						//頂点カラー
//	D3DXVECTOR2	tex;
//
//}VERTEX_2D;
//
//typedef enum
//{
//	GAME_TITLE,
//	GAME_MAIN,
//	GAME_OVER
//
//
//}GAMESTATUS;



////////////////////////////////////////
//　初期化処理
////////////////////////////////////////
BOOL CDXAppBase::Initialize(void)
{
	CApplicationBase::Initialize();

	//DirectXの生成初期化
	m_DirectX3D = CDirectX3D::Create(this, true);
	m_DirectX3D -> Initialize();

	//入力デバイスの初期化
	CDXInput::Initialize(m_hWnd);

	//ゲーム独自の初期化
	//m_MainGame.SetPtr();

	//カメラ初期化
	//Camera.Initialize();

	//SceneManeger初期化
	m_SceneManeger.SwapScene();

	return TRUE;


}

////////////////////////////////////////
//　メインループ
////////////////////////////////////////
void CDXAppBase::Loop(void)
{

	MSG Msg;

	while (1)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{//-----メッセージが走ったら-----

			if (Msg.message == WM_QUIT)
				break;
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);

		}
		else
		{//-----ゲーム側の処理-----

			if (FPSKeeper())//60FPSで処理が回る
			{
				////シーンの更新
				m_SceneManeger.Updata();


				////更新後の更新
				m_SceneManeger.LateUpdata();

				////次のSceneが設定されていたら変更
				m_SceneManeger.SwapScene();
			}

			m_DirectX3D->Begin();		//描画開始

			//描画実行	
			m_SceneManeger.PrevDraw();
			m_SceneManeger.Draw();
			m_DirectX3D->End();			//描画終了


		}

	}

}


void CDXAppBase::ReleaseApp()
{
	CObjectFactoryManeger::Instance()->AllRelease();
	CResourceManeger::Instance()->Release();


}




