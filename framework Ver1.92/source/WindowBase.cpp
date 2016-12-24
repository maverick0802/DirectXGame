#include "WindowBase.h"


CWindowBase::CWindowBase()
{
	HWND m_hWnd = NULL;


}





BOOL CWindowBase::Create(HINSTANCE hInstance,
						 const char* pszClassName,
						 const char* pszWindowName,
						 int nScreenWidth,
						 int nScreenHeight)
{

	m_hWnd = CreateWindowEx(0,
		pszClassName,
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

	if (!m_hWnd)
	{

		printf("ウィンドウハンドルの生成に失敗しました\n");

		return FALSE;

	}
	else
	{

		printf("ウィンドウハンドルの生成に成功しました\n");

		return TRUE;

	}
}