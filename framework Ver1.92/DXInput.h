#pragma once
#include "DirectX3D.h"
#include <windows.h>
#include <tchar.h>
#define DIRECTINPUT_VERSION 0x0800	// DirectX8 �𖾎�
#include <dinput.h>					// DirectInput �֘A�̃w�b�_

//-------- �L�[�{�[�h�֌W
#define MAX_KEY			256			// �L�[��

//-------- �W���C�X�e�B�b�N�֌W
#define JOY_X			0			// �w��
#define JOY_Y			1			// �x��

//-------- �}�E�X�֌W
#define MOUSE_X			0			// �w��
#define MOUSE_Y			1			// �x��
#define MOUSE_Z			2			// �y��

//-------- �Q�[���p�b�h�֌W
#define MAX_JOY			4			// �ő�F���ڑ���
#define JOY_MIN_X		-32768		// �w���ŏ��l
#define JOY_MAX_X		32767		// �w���ő�l
#define JOY_MIN_Y		-32768		// �x���ŏ��l
#define JOY_MAX_Y		32767		// �x���ő�l

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

