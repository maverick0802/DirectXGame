#include "ApplicationBase.h"
#include "DXAppBase.h"
#include "DXWndBase.h"
#include <crtdbg.h>

#ifdef _DEBUG
#define	DEBUG_NEW	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const double FPS_RATE = 1000 / 60;

CApplicationBase* CApplicationBase::pApp = NULL;
HWND		CApplicationBase::m_hWnd;
int			CApplicationBase::m_nWidth;
int			CApplicationBase::m_nHight;



CApplicationBase::CApplicationBase()
{

	pApp =  this;
	m_dwLastTime = m_dwLastFPSTime = ::timeGetTime();
	m_dwFPS = 0;
}


int CApplicationBase::Run(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	//ウィンドウクラス登録
	if (!RegistWndClass("DIRECTX_CLASS"))
		return E_FAIL;

	//メインウィンドウの作成

	if (!CreatMainWnd(m_hInstance, "DIRECTX_TEST",800,600))
		return E_FAIL;

	//アプリケーション独自の初期化
	if(!Initialize())
		return E_FAIL;

	//メッセージループ
	Loop();

	//アプリケーションの終了処理
	ReleaseApp();

	return 0;
}



LRESULT CALLBACK CApplicationBase::GlobalWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	if (pApp)
	{
		switch (Msg)
		{
		case WM_DESTROY:
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			CREATESTRUCT* pCreateStruct;
			pCreateStruct = (CREATESTRUCT*)lParam;
			SetWindowLongPtr(hWnd, 0, (LONG_PTR)pCreateStruct->lpCreateParams);
			printf("サブクラスの登録成功\n");
			break;

		default:
		
			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}

		return 0;




	}


	return S_OK;

}

//ウィンドウクラス登録
BOOL CApplicationBase::RegistWndClass(char * pszClassName)
{
	m_szClassName = pszClassName;
	
	WNDCLASSEX Buf	=
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		CApplicationBase::GlobalWindowProc,
		0,
		0,
		m_hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		m_szClassName.c_str(),
		NULL,
	};

	m_WndClassEx = Buf;

	//ウィンドウクラスの登録
	if (RegisterClassEx(&m_WndClassEx) == 0)
		return false;
	return TRUE;

}

//メインウィンドウの作成
BOOL CApplicationBase::CreatMainWnd(HINSTANCE hInstance,
						 const char* pszWindowName,
						 int nScreenWidth,
						 int nScreenHeight)
{
	
		
		m_hWnd = CreateWindowEx(0,
			"DIRECTX_CLASS",
			pszWindowName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			(nScreenWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2),
			(nScreenHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
			NULL,
			NULL,
			hInstance,
			NULL
			);

		m_nWidth = nScreenWidth;
		m_nHight = nScreenHeight;

		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

	

	return TRUE;

}

BOOL CApplicationBase::Initialize()
{	

	return TRUE;

}


void CApplicationBase::Loop()
{
	MSG Msg;
	while (1)
	if (GetMessage(&Msg, NULL, 0, 0))
	{

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

	}

}

void CApplicationBase::SetDebug()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(353);
}

void CApplicationBase::ReleaseApp()
{


	

}

bool CApplicationBase::FPSKeeper()
{
	DWORD dwNowTime = ::timeGetTime();
	static DWORD dwFPSCounter = 0;
	if (dwNowTime - m_dwLastFPSTime> 500)
	{

		m_dwFPS = (dwFPSCounter * 1000) / (dwNowTime - m_dwLastFPSTime);
		//m_dwLastFPSTime = ::timeGetTime();
		m_dwLastFPSTime = dwNowTime;
		dwFPSCounter = 0;
		printf("FPS::%d", m_dwFPS);
	}

	if (dwNowTime - m_dwLastTime > FPS_RATE)
	{
		m_dwDeltaTime = dwNowTime - m_dwLastTime;
		m_dwLastTime = dwNowTime;
		dwFPSCounter++;
		return true;
	}
	//dwFPSCounter++;
	return false;
}





