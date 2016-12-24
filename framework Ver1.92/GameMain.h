#pragma once
#include "GameBase.h"
class CGameMain :
	public CGameBase
{
public:
	CGameMain();
	~CGameMain();

	virtual HRESULT Initialize();
	virtual HRESULT Update();
	virtual HRESULT Draw();
};

