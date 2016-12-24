#pragma once
#include <Windows.h>

class CGameBase
{
public:
	virtual HRESULT Initialize() = 0;
	virtual HRESULT Update() = 0;
	virtual HRESULT Draw() = 0;

	
	CGameBase();
	~CGameBase();
};

