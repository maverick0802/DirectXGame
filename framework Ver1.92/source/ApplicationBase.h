#pragma once
#include <Windows.h>
#include "Smart_ptr.h"
#include <vector>
#include <crtdbg.h>


#ifdef _DEBUG
#define	DEBUG_NEW	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

class CApplicationBase
{
protected:
	HINSTANCE	m_hInstance;				//アプリケーションハンドル
	WNDCLASSEX	m_WndClassEx;				//ウィンドウクラス構造体
	static HWND	m_hWnd;
	static int	m_nWidth;
	static int	m_nHight;
	std::string m_szClassName;
	DWORD		m_dwLastTime;
	DWORD		m_dwDeltaTime;
	DWORD		m_dwLastFPSTime;
	DWORD		m_dwDeltaFPSTime;
	DWORD		m_dwFPS;
protected:

	static CApplicationBase *pApp;

public:
	static void SetDebug();

	//コンストラクタ
	CApplicationBase();
	
	//デストラクタ
	virtual ~CApplicationBase(){};				
	
	//実行関数
	int Run(HINSTANCE hInstance);
	
	//グローバルなウィンドウプロシージャ関数
	static LRESULT CALLBACK GlobalWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	//インスタンスハンドルを取得
	HINSTANCE GethInstance(){
	
		return m_hInstance;
	
	}

	//ウィンドウクラス構造体を取得
	void GetWndClass(WNDCLASSEX*  wc){
	
		*wc = m_WndClassEx;
	
	}

	//ウィンドウのスマートポインタへのポインタを取得

	static HWND* GethWnd()
	{
	
		return &m_hWnd;

	}
	
	//ウィンドウの横幅を返す
	static int GetWidth(){ return	m_nWidth;};
	
	//ウィンドウの縦幅を返す
	static int GetHight(){ return	m_nHight;};
	
	bool FPSKeeper();


//-------仮想関数-------
protected:

	//ウィンドウクラス登録
	virtual BOOL RegistWndClass(char * szClassName);

	//メインウィンドウの作成
	virtual BOOL CreatMainWnd(HINSTANCE hInstance,
		const char* pszWindowName,
		int nScreenWidth,
		int nScreenHeight);

	//アプリケーション独自の初期化
	virtual BOOL Initialize();

	//メッセージループ
	virtual void Loop();

	//アプリケーションの終了処理
	virtual void ReleaseApp();
	




};




