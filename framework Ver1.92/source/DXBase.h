#pragma once
#include <Windows.h>

class CDXBase
{
protected:
	HWND m_hWnd;
	HINSTANCE m_Instance;

public:
	CDXBase(HWND hWnd, HINSTANCE hInstance)
	{
	
		m_hWnd	   = hWnd;
		m_Instance = hInstance;

	}

	virtual ~CDXBase(){};

	virtual HRESULT Initialize() = 0;

	virtual HRESULT Release(){};

	virtual HRESULT Step() = 0;

};

