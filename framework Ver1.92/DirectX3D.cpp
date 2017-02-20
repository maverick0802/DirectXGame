#include "DirectX3D.h"

CSmart_ptr<CDirectX3D>	CDirectX3D::m_pCDirectX3D;


CDirectX3D::CDirectX3D(CApplicationBase * pApplication, bool bWindowMode) :
m_bWindowMode(bWindowMode),
m_pApplication(pApplication),
m_Direct3D(NULL){


}

CDirectX3D::~CDirectX3D()
{
}



CDirectX3D* CDirectX3D::Create(CApplicationBase* pApplicaton, bool bWindowMode)
{

	static CSmart_ptr<CDirectX3D> pCDirectX3D( new CDirectX3D(pApplicaton, bWindowMode));

	m_pCDirectX3D = pCDirectX3D;

	return m_pCDirectX3D.GetPtr();
};

CDirectX3D* CDirectX3D::Create(void)
{

	if (!(m_pCDirectX3D.GetPtr()))
		return nullptr;

	return m_pCDirectX3D.GetPtr();
};


HRESULT CDirectX3D::Initialize()
{

	D3DDISPLAYMODE			d3ddm;


	// Direct3Dオブジェクトの生成
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3D == NULL){
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&m_D3dpp, sizeof(m_D3dpp));						// ワークをゼロクリア
	m_D3dpp.BackBufferWidth = m_pApplication->GetWidth();	// ゲーム画面サイズ(幅)
	m_D3dpp.BackBufferHeight = m_pApplication->GetHight();	// ゲーム画面サイズ(高)
	m_D3dpp.BackBufferCount = 1;						// バックバッファの数
	m_D3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする。
	m_D3dpp.Windowed = m_bWindowMode;			// ウィンドウモード
	m_D3dpp.EnableAutoDepthStencil = TRUE;						// デプスバファ(Ｚバッファ)とステンシルバッファを作成
	m_D3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// デプスバッファとして16bitを使う

	if (m_bWindowMode){
		// ウィンドウモード
		m_D3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// カラーモードの設定
		m_D3dpp.FullScreen_RefreshRateInHz = 0;
		m_D3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else{
		// フルスクリーンモード
		m_D3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				// カラーモードの設定
		m_D3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_D3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}


	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,			// ディスプレイアダプタ
		D3DDEVTYPE_HAL,												// デバイスタイプ
		*m_pApplication->GethWnd(),									// フォーカスするウィンドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// デバイス作成制御の組み合わせ
		&m_D3dpp,														// デバイスのプレゼンテーションパラメータ
		&m_3DDevice)))	{											// デバイスインターフェースへのポインタ

		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>とハードウェアで行い、<頂点処理>はCPUで行う
		if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,		// ディスプレイアダプタ
			D3DDEVTYPE_HAL,											// デバイスタイプ
			*m_pApplication->GethWnd(),								// フォーカスするウィンドウへのハンドル
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,					// デバイス作成制御の組み合わせ
			&m_D3dpp,													// デバイスのプレゼンテーションパラメータ
			&m_3DDevice))){											// デバイスインターフェースへのポインタ

			// 記の設定が失敗したら
			// デバイス作成制御]<描画>とハ<頂点処理>はCPUで行う
			if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,	// ディスプレイアダプタ
				D3DDEVTYPE_REF,										// デバイスタイプ
				*m_pApplication->GethWnd(),							// フォーカスするウィンドウへのハンドル
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,				// デバイス作成制御の組み合わせ
				&m_D3dpp,												// デバイスのプレゼンテーションパラメータ
				&m_3DDevice))){										// デバイスインターフェースへのポインタ
				// 初期化失敗
				return E_FAIL;
			}
		}
	}


	m_3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を有効

															// 最後に環境光を設定する。
	m_3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	m_3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	m_3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);



	return S_OK;
}


//////////////////////////////////
//
//　関数名: Begin
//　引数  : なし
//　戻り値: なし
//　～～～～～～～～～～～～～～～～
//　概要
//　レンダリング開始
//
//////////////////////////////////

bool CDirectX3D::Begin(){
	
	//ビューポートをクリア
	m_3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	return SUCCEEDED( m_3DDevice->BeginScene());		//シーン開始

}


//////////////////////////////////
//
//　関数名: End
//　引数  : なし
//　戻り値: なし
//　～～～～～～～～～～～～～～～～
//　概要
//　レンダリング終了
//
//
//////////////////////////////////

void CDirectX3D::End(){

	m_3DDevice->EndScene();		//シーン終了

}

//////////////////////////////////
//
//　関数名: SwapBuffer
//　引数  : なし
//　戻り値: なし
//　～～～～～～～～～～～～～～～～
//　概要　
//	バックバッファ入れ替え
//
//////////////////////////////////

void CDirectX3D::SwapBuffer() {

	//バッファに描画した内容を表示
	if (FAILED(m_3DDevice->Present(NULL, NULL, NULL, NULL))) {
		m_3DDevice->Reset(&m_D3dpp);
	}

}
	

//////////////////////////////////
//
//　関数名: GetDevice
//　引数  : なし
//　戻り値: なし
//　～～～～～～～～～～～～～～～～
//　概要
//　デバイスの取得
//
//////////////////////////////////

LPDIRECT3DDEVICE9* CDirectX3D::GetDevice()
{


	return &m_3DDevice;

}

