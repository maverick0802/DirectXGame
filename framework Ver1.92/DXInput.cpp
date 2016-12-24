#include "DXInput.h"


LPDIRECTINPUT8			CDXInput::m_pDI = NULL;
LPDIRECTINPUTDEVICE8	CDXInput::m_pDIKeyDevice = NULL;
BYTE					CDXInput::m_diKeyState[MAX_KEY] = {0};
BYTE					CDXInput::m_diPrevKeyState[MAX_KEY] = {0};
LPDIRECTINPUTDEVICE8	CDXInput::m_pDIMouseDevice = NULL;
DIMOUSESTATE			CDXInput::m_diMouseState = {0};
DIMOUSESTATE			CDXInput::m_diPrevMouseState = {0};
LPDIRECTINPUTDEVICE8	CDXInput::m_pDIJoyDevice[MAX_JOY] = {0};
DIJOYSTATE				CDXInput::m_diJoyState[MAX_JOY] = {0};
DIJOYSTATE				CDXInput::m_diPrevJoyState[MAX_JOY] = {0};
int						CDXInput::m_nJoyNum = 0;
char					g_szTitle[] = "CInput";

CDXInput::CDXInput()
{
}


CDXInput::~CDXInput()
{
}

BOOL CALLBACK	CDXInput::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{

	DIDEVCAPS diDevCaps;
	
	//ジョイスティック用デバイスオブジェクトを作成
	HRESULT	 hr = m_pDI->CreateDevice(lpddi->guidInstance, &m_pDIJoyDevice[m_nJoyNum], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;	//列挙を続ける
	//ジョイステックの性能を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = m_pDIJoyDevice[m_nJoyNum]->GetCapabilities(&diDevCaps);
	if (FAILED(hr))
	{
		m_pDIJoyDevice[m_nJoyNum]->Release();
		m_pDIJoyDevice[m_nJoyNum] = NULL;
		return DIENUM_CONTINUE;
	}
	if (++m_nJoyNum < MAX_JOY)
		return DIENUM_CONTINUE;
	return DIENUM_STOP;		//必要数揃ったので列挙を終了する

}


void CDXInput::Initialize(HWND hWnd)
{
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	//DirectInputオブジェクトの作成
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput オブジェクトの作成に失敗しました"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********キーボード用
	//DirectInputDeviceオブジェクトの作成
	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIKeyDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputDevice オブジェクトの作成に失敗しました"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//データフォーマットの設定
	hr = m_pDIKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput でデータフォーマットの設定に失敗しました"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//協調レベルの設定
	hr = m_pDIKeyDevice->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputで協調レベルの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//デバイスへの入力制御開始
	hr = m_pDIKeyDevice->Acquire();
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput でデバイスへの入力制御開始に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********マウス用
	//DirectInputDeviceオブジェクトの作成
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pDIMouseDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputDevice オブジェクトの作成に失敗しました"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//データフォーマットの設定
	hr = m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput でデータフォーマットの設定に失敗しました"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//協調レベルの設定
	hr = m_pDIMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputで協調レベルの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//Deviceの設定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize		= sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIPROPAXISMODE_REL;			//相対値モードに設定
	m_pDIMouseDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	//デバイスへの入力制御開始
	hr = m_pDIKeyDevice->Acquire();
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput でデバイスへの入力制御開始に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********ジョイパット用
	//DirectInputDeviceオブジェクトの作成
	m_nJoyNum = 0;
	hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice オブジェクトの作成に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	for (int nCnt = 0; nCnt < m_nJoyNum; nCnt++)
	{
		//データフォーマットの設定
		hr = m_pDIJoyDevice[nCnt]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput でデータフォーマットの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		//協調レベルの設定
		hr = m_pDIJoyDevice[nCnt]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInputで協調レベルの設定に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		//デバイスの設定
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize		= sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = JOY_MIN_X;
		diprg.lMax = JOY_MAX_X;
		m_pDIJoyDevice[nCnt]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = JOY_MIN_Y;
		diprg.lMax = JOY_MAX_Y;
		m_pDIJoyDevice[nCnt]->SetProperty(DIPROP_RANGE, &diprg.diph);

		//デバイスへの入力制御開始
		hr = m_pDIJoyDevice[nCnt]->Acquire();
		if (FAILED(hr))
		{
			MessageBox(hWnd, ("DirectInput でデバイスへの入力制御開始に失敗しました！"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

	}


}
void CDXInput::UnInitialize()
{

	for (int nCnt = 0; nCnt < m_nJoyNum; nCnt++)
	{
		if (m_pDIJoyDevice[nCnt])
			m_pDIJoyDevice[nCnt]->Unacquire();
		m_pDIJoyDevice[nCnt]->Release();
		m_pDIJoyDevice[nCnt] = NULL;
	}

	if (m_pDIKeyDevice)
		m_pDIKeyDevice->Unacquire();
	m_pDIKeyDevice->Release();
	m_pDIKeyDevice = NULL;
	if (m_pDIMouseDevice)
		m_pDIMouseDevice->Unacquire();
	m_pDIMouseDevice->Release();
	m_pDIMouseDevice = NULL;
	m_pDI->Release();
	m_pDI = NULL;



}
void CDXInput::Update()
{
	HRESULT hr;

	if (m_pDIKeyDevice)
	{
		//前フレームのキーボードの入力結果を保存
		CopyMemory(m_diPrevKeyState, m_diKeyState, MAX_KEY);
		m_pDIKeyDevice->Acquire();		//要求を出す
		//現在のキーボードの状態を取得
		hr = m_pDIKeyDevice->GetDeviceState(MAX_KEY, &m_diKeyState);
		if (hr == DIERR_INPUTLOST)
			m_pDIKeyDevice->Acquire();			//再度、要求を出す
	}
	if (m_pDIMouseDevice)
	{
		//前フレームのマウスの入力結果を保存
		m_diPrevMouseState = m_diMouseState;
		m_pDIMouseDevice->Acquire();	//要求を出す
		//現在のマウスの状態を取得
		hr = m_pDIMouseDevice->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState);
		if (hr == DIERR_INPUTLOST)
			m_pDIMouseDevice->Acquire();		//再度、要求を出す
	}
	for (int nCnt = 0; nCnt < m_nJoyNum; nCnt++)
	{

		m_diPrevJoyState[nCnt] = m_diJoyState[nCnt];
		m_pDIJoyDevice[nCnt]->Acquire();	//要求を出す
		m_pDIJoyDevice[nCnt]->Poll();		//デバイス上のポーキング対象オブジェクトからデータを取得
		//現在のジョイスティックの状態を取得
		hr = m_pDIJoyDevice[nCnt]->GetDeviceState(sizeof(m_diPrevJoyState[0]), &m_diJoyState[nCnt]);
		if (hr == DIERR_INPUTLOST)
			m_pDIJoyDevice[nCnt]->Acquire();	//再度、要求を出す
	}

}

//キーの押下状態を取得
bool CDXInput::GetKeyPress(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diKeyState[nKey] & 0x80) != 0;
}

//キーのトリガー状態を取得
bool CDXInput::GetKeyTrigger(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) == 0 && 
		(m_diKeyState[nKey] & 0x80) != 0;
}

//キーのリリース状態を取得
bool CDXInput::GetKeyRelease(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) != 0 &&
		(m_diKeyState[nKey] & 0x80) == 0;
}

//ジョイスティック数取得
int	 CDXInput::GetNumJoyStick()
{
	return m_nJoyNum;
}

//ジョイスティックのボタンの押下状態取得
bool CDXInput::GetJoyPress(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;

}

//ジョイスティックのボタンのトリガ状態の取得
bool CDXInput::GetJoyTrigger(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;

}

//ジョイスティックのボタンのリリース状態の取得
bool CDXInput::GetJoyRelease(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0;
}

//ジョイステックの軸状態の取得
float CDXInput::GetJoyAxis(int nJoy, int nAxis)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return 0.0f;
	switch (nAxis)
	{
	case JOY_X:
		if (m_diJoyState[nJoy].lX < 0)
		{
			return m_diJoyState[nJoy].lX / (float)-JOY_MIN_X;
		}
		return m_diJoyState[nJoy].lX / (float)JOY_MAX_X;
	case JOY_Y:
		if (m_diJoyState[nJoy].lX < 0)
		{
			return m_diJoyState[nJoy].lY / (float)-JOY_MIN_Y;
		}
		return m_diJoyState[nJoy].lY / (float)JOY_MAX_Y;
	default:
		break;
	}
	return 0.0f;
}

//マウスのボタンの押下状態の取得
bool CDXInput::GetMousePress(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}

//マウスのボタンのトリガ状態の取得
bool CDXInput::GetMouseTrigger(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) == 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}

//マウスのボタンのリリース状態の取得
bool CDXInput::GetMouseRelease(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) != 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) == 0;
}

//マウスの変化量取得
long CDXInput::GetMouseAxis(int nAxis)
{
	switch (nAxis)
	{
	case MOUSE_X:
		return m_diMouseState.lX;
	case MOUSE_Y:
		return m_diMouseState.lY;
	case MOUSE_Z:
		return m_diMouseState.lZ;
	}
	return 0L;
}
