#pragma once
#include "ApplicationBase.h"
#include "DXBase.h"
#include "Smart_ptr.h"
#include "../DirectX3D.h"
#include "../GameBase.h"
#include "../SceneManeger.h"
//#include "../Camera.h"
#ifdef _DEBUG
#define	new	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif



class CDXAppBase : public CApplicationBase
{
	CSmart_ptr<CDXBase> m_DXObj;
	CDirectX3D * m_DirectX3D;
	CSmart_ptr<CGameBase> m_MainGame;
	CSceneManeger m_SceneManeger;
	//CCamera Camera;

public:
	CDXAppBase(){};
	~CDXAppBase(){};

	BOOL Initialize(void);
	void Loop();
	void ReleaseApp();

	//void SetObject(CSmart_ptr<CDXBase> DxObj)
	//{
	//
	//	m_DXObj = DxObj.GetPtr();
	//
	//}

};

