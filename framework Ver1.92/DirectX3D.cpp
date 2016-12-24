#include "DirectX3D.h"

CSmart_ptr<CDirectX3D>	CDirectX3D::m_pCDirectX3D;


CDirectX3D::CDirectX3D(CApplicationBase * pApplication, bool bWindowMode) :
m_bWindowMode(bWindowMode),
m_pApplication(pApplication),
m_Direct3D(NULL){}

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

	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	// Direct3Dオブジェクトの生成
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3D == NULL){
		return E_FAIL;
	}

	// 現在のディスプレイモードを習得
	if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ワークをゼロクリア
	d3dpp.BackBufferWidth = m_pApplication->GetWidth();	// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = m_pApplication->GetHight();	// ゲーム画面サイズ(高)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの設定
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする。
	d3dpp.Windowed = m_bWindowMode;			// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// デプスバッファとして16bitを使う

	if (m_bWindowMode){
		// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else{
		// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	int a = 1;

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行う
	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
		D3DDEVTYPE_HAL,						// デバイスタイプ
		*m_pApplication->GethWnd(),			// フォーカスするウィンドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
		&d3dpp,								// デバイスのプレゼンテーションパラメータ
		&m_3DDevice)))	{			// デバイスインターフェースへのポインタ

		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>とハードウェアで行い、<頂点処理>はCPUで行う
		if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
			D3DDEVTYPE_HAL,						// デバイスタイプ
			*m_pApplication->GethWnd(),								// フォーカスするウィンドウへのハンドル
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
			&d3dpp,								// デバイスのプレゼンテーションパラメータ
			&m_3DDevice))){					// デバイスインターフェースへのポインタ

			// 記の設定が失敗したら
			// デバイス作成制御]<描画>とハ<頂点処理>はCPUで行う
			if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// ディスプレイアダプタ
				D3DDEVTYPE_REF,						// デバイスタイプ
				*m_pApplication->GethWnd(),								// フォーカスするウィンドウへのハンドル
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
				&d3dpp,								// デバイスのプレゼンテーションパラメータ
				&m_3DDevice))){					// デバイスインターフェースへのポインタ
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートのパラメータの設定
	m_3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	m_3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// アルファブレンドを行う
	m_3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ソースの設定
	m_3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ですとの設定

	// サンプラーステートパラメータの設定
	m_3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャU値の繰り返し設定
	m_3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャV値の繰り返し設定
	m_3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補間設定
	m_3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ拡小時の補間設定

	m_3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);


	return S_OK;
}

void CDirectX3D::Begin(){
	
	m_3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 255, 0), 1.0f, 0);
	m_3DDevice->BeginScene();

}

void CDirectX3D::End(){

	m_3DDevice->EndScene();
	m_3DDevice->Present(NULL, NULL, NULL, NULL);
}
	

LPDIRECT3DDEVICE9* CDirectX3D::GetDevice()
{


	return &m_3DDevice;

}

