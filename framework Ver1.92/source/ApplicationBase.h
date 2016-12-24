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
	HINSTANCE	m_hInstance;				//�A�v���P�[�V�����n���h��
	WNDCLASSEX	m_WndClassEx;				//�E�B���h�E�N���X�\����
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

	//�R���X�g���N�^
	CApplicationBase();
	
	//�f�X�g���N�^
	virtual ~CApplicationBase(){};				
	
	//���s�֐�
	int Run(HINSTANCE hInstance);
	
	//�O���[�o���ȃE�B���h�E�v���V�[�W���֐�
	static LRESULT CALLBACK GlobalWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	//�C���X�^���X�n���h�����擾
	HINSTANCE GethInstance(){
	
		return m_hInstance;
	
	}

	//�E�B���h�E�N���X�\���̂��擾
	void GetWndClass(WNDCLASSEX*  wc){
	
		*wc = m_WndClassEx;
	
	}

	//�E�B���h�E�̃X�}�[�g�|�C���^�ւ̃|�C���^���擾

	static HWND* GethWnd()
	{
	
		return &m_hWnd;

	}
	
	//�E�B���h�E�̉�����Ԃ�
	static int GetWidth(){ return	m_nWidth;};
	
	//�E�B���h�E�̏c����Ԃ�
	static int GetHight(){ return	m_nHight;};
	
	bool FPSKeeper();


//-------���z�֐�-------
protected:

	//�E�B���h�E�N���X�o�^
	virtual BOOL RegistWndClass(char * szClassName);

	//���C���E�B���h�E�̍쐬
	virtual BOOL CreatMainWnd(HINSTANCE hInstance,
		const char* pszWindowName,
		int nScreenWidth,
		int nScreenHeight);

	//�A�v���P�[�V�����Ǝ��̏�����
	virtual BOOL Initialize();

	//���b�Z�[�W���[�v
	virtual void Loop();

	//�A�v���P�[�V�����̏I������
	virtual void ReleaseApp();
	




};




