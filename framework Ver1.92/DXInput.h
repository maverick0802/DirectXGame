#pragma once
#include "DirectX3D.h"
#include <windows.h>
#include <tchar.h>
#define DIRECTINPUT_VERSION 0x0800	// DirectX8 を明示
#include <dinput.h>					// DirectInput 関連のヘッダ

//-------- キーボード関係
#define MAX_KEY			256			// キー数

//-------- ジョイスティック関係
#define JOY_X			0			// Ｘ軸
#define JOY_Y			1			// Ｙ軸

//-------- マウス関係
#define MOUSE_X			0			// Ｘ軸
#define MOUSE_Y			1			// Ｙ軸
#define MOUSE_Z			2			// Ｚ軸

//-------- ゲームパッド関係
#define MAX_JOY			4			// 最大認識接続数
#define JOY_MIN_X		-32768		// Ｘ軸最小値
#define JOY_MAX_X		32767		// Ｘ軸最大値
#define JOY_MIN_Y		-32768		// Ｙ軸最小値
#define JOY_MAX_Y		32767		// Ｙ軸最大値

class CDXInput
{
	static LPDIRECTINPUT8			m_pDI;
	static LPDIRECTINPUTDEVICE8		m_pDIKeyDevice;
	static BYTE						m_diKeyState[MAX_KEY];
	static BYTE						m_diPrevKeyState[MAX_KEY];
	static LPDIRECTINPUTDEVICE8		m_pDIMouseDevice;
	static DIMOUSESTATE				m_diMouseState;
	static DIMOUSESTATE				m_diPrevMouseState;
	static LPDIRECTINPUTDEVICE8		m_pDIJoyDevice[MAX_JOY];
	static DIJOYSTATE				m_diJoyState[MAX_JOY];
	static DIJOYSTATE				m_diPrevJoyState[MAX_JOY];
	static int						m_nJoyNum;

	static BOOL CALLBACK	EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
public:
	CDXInput();
	~CDXInput();
	static void Initialize(HWND hWnd);
	static void UnInitialize();
	static void Update();

	static bool GetKeyPress(int nKey);
	static bool GetKeyTrigger(int nKey);
	static bool GetKeyRelease(int nKey);
	static int	GetNumJoyStick();
	static bool GetJoyPress(int nJoy, int nButton);
	static bool GetJoyTrigger(int nJoy, int nButton);
	static bool GetJoyRelease(int nJoy, int nButton);
	static float GetJoyAxis(int nJoy, int nAxis);
	static bool GetMousePress(int nButton);
	static bool GetMouseTrigger(int nButton);
	static bool GetMouseRelease(int nButton);
	static long GetMouseAxis(int nAxis);
};

