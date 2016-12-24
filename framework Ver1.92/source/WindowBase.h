#pragma once
#include <Windows.h>
#include <String>


class CWindowBase
{
public:
	CWindowBase();
	~CWindowBase(){};

protected:
	HWND m_hWnd;
public:
	
	BOOL Create(HINSTANCE hInstance,
							const char* pszClassName,
							const char* pszWindowName,
							int nScreenWidth,
							int nScreenHeight);

	HWND GethWnd(void){ return m_hWnd; }


};

