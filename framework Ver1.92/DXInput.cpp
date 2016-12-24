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
	
	//�W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	HRESULT	 hr = m_pDI->CreateDevice(lpddi->guidInstance, &m_pDIJoyDevice[m_nJoyNum], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;	//�񋓂𑱂���
	//�W���C�X�e�b�N�̐��\�𒲂ׂ�
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
	return DIENUM_STOP;		//�K�v���������̂ŗ񋓂��I������

}


void CDXInput::Initialize(HWND hWnd)
{
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	//DirectInput�I�u�W�F�N�g�̍쐬
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput �I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********�L�[�{�[�h�p
	//DirectInputDevice�I�u�W�F�N�g�̍쐬
	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIKeyDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//�������x���̐ݒ�
	hr = m_pDIKeyDevice->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//�f�o�C�X�ւ̓��͐���J�n
	hr = m_pDIKeyDevice->Acquire();
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********�}�E�X�p
	//DirectInputDevice�I�u�W�F�N�g�̍쐬
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pDIMouseDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//�������x���̐ݒ�
	hr = m_pDIMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//Device�̐ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize		= sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIPROPAXISMODE_REL;			//���Βl���[�h�ɐݒ�
	m_pDIMouseDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	//�f�o�C�X�ւ̓��͐���J�n
	hr = m_pDIKeyDevice->Acquire();
	if (FAILED(hr))
	{
		MessageBox(hWnd, ("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//*********�W���C�p�b�g�p
	//DirectInputDevice�I�u�W�F�N�g�̍쐬
	m_nJoyNum = 0;
	hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	for (int nCnt = 0; nCnt < m_nJoyNum; nCnt++)
	{
		//�f�[�^�t�H�[�}�b�g�̐ݒ�
		hr = m_pDIJoyDevice[nCnt]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		//�������x���̐ݒ�
		hr = m_pDIJoyDevice[nCnt]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		//�f�o�C�X�̐ݒ�
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

		//�f�o�C�X�ւ̓��͐���J�n
		hr = m_pDIJoyDevice[nCnt]->Acquire();
		if (FAILED(hr))
		{
			MessageBox(hWnd, ("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
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
		//�O�t���[���̃L�[�{�[�h�̓��͌��ʂ�ۑ�
		CopyMemory(m_diPrevKeyState, m_diKeyState, MAX_KEY);
		m_pDIKeyDevice->Acquire();		//�v�����o��
		//���݂̃L�[�{�[�h�̏�Ԃ��擾
		hr = m_pDIKeyDevice->GetDeviceState(MAX_KEY, &m_diKeyState);
		if (hr == DIERR_INPUTLOST)
			m_pDIKeyDevice->Acquire();			//�ēx�A�v�����o��
	}
	if (m_pDIMouseDevice)
	{
		//�O�t���[���̃}�E�X�̓��͌��ʂ�ۑ�
		m_diPrevMouseState = m_diMouseState;
		m_pDIMouseDevice->Acquire();	//�v�����o��
		//���݂̃}�E�X�̏�Ԃ��擾
		hr = m_pDIMouseDevice->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState);
		if (hr == DIERR_INPUTLOST)
			m_pDIMouseDevice->Acquire();		//�ēx�A�v�����o��
	}
	for (int nCnt = 0; nCnt < m_nJoyNum; nCnt++)
	{

		m_diPrevJoyState[nCnt] = m_diJoyState[nCnt];
		m_pDIJoyDevice[nCnt]->Acquire();	//�v�����o��
		m_pDIJoyDevice[nCnt]->Poll();		//�f�o�C�X��̃|�[�L���O�ΏۃI�u�W�F�N�g����f�[�^���擾
		//���݂̃W���C�X�e�B�b�N�̏�Ԃ��擾
		hr = m_pDIJoyDevice[nCnt]->GetDeviceState(sizeof(m_diPrevJoyState[0]), &m_diJoyState[nCnt]);
		if (hr == DIERR_INPUTLOST)
			m_pDIJoyDevice[nCnt]->Acquire();	//�ēx�A�v�����o��
	}

}

//�L�[�̉�����Ԃ��擾
bool CDXInput::GetKeyPress(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diKeyState[nKey] & 0x80) != 0;
}

//�L�[�̃g���K�[��Ԃ��擾
bool CDXInput::GetKeyTrigger(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) == 0 && 
		(m_diKeyState[nKey] & 0x80) != 0;
}

//�L�[�̃����[�X��Ԃ��擾
bool CDXInput::GetKeyRelease(int nKey)
{
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) != 0 &&
		(m_diKeyState[nKey] & 0x80) == 0;
}

//�W���C�X�e�B�b�N���擾
int	 CDXInput::GetNumJoyStick()
{
	return m_nJoyNum;
}

//�W���C�X�e�B�b�N�̃{�^���̉�����Ԏ擾
bool CDXInput::GetJoyPress(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;

}

//�W���C�X�e�B�b�N�̃{�^���̃g���K��Ԃ̎擾
bool CDXInput::GetJoyTrigger(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;

}

//�W���C�X�e�B�b�N�̃{�^���̃����[�X��Ԃ̎擾
bool CDXInput::GetJoyRelease(int nJoy, int nButton)
{
	if (nJoy < 0 || nJoy >= m_nJoyNum) return false;
	if (nButton < 0 || nButton >= 32)return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0;
}

//�W���C�X�e�b�N�̎���Ԃ̎擾
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

//�}�E�X�̃{�^���̉�����Ԃ̎擾
bool CDXInput::GetMousePress(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}

//�}�E�X�̃{�^���̃g���K��Ԃ̎擾
bool CDXInput::GetMouseTrigger(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) == 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}

//�}�E�X�̃{�^���̃����[�X��Ԃ̎擾
bool CDXInput::GetMouseRelease(int nButton)
{
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) != 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) == 0;
}

//�}�E�X�̕ω��ʎ擾
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
