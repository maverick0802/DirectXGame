#pragma once

////////////////////////////////////////////////
//
//ClassName: CDirectX3D
//auther:���Y�@�G�I
// �`Detail�`
//DirectX9��3D�ɕK�v�ȏ�������A�f�o�C�X�̊Ǘ�������
//
//**********************************************
//
//
//
//
//
//
//
//
/////////////////////////////////////////////////


#include "d3dx9.h"
#include "dinput.h"
#include "source\ApplicationBase.h"
#include "DirectX3D.h"
#include "source\Smart_ptr.h"
#include <Windows.h>
#include <string.h>
//=============================================
//���C�u�����̃����N
//=============================================

#if 1
#pragma comment (lib,"d3d9.lib")			//���v���O�����Ƀ��C�u����������������
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"winmm.lib")
#endif

typedef struct {
	D3DXVECTOR3 pos;						//���_���W
	float		rhw;						//�e�N�X�`��
	D3DCOLOR	col;						//���_�J���[
	D3DXVECTOR2	tex;

}VERTEX_2D;


class CDirectX3D
{
public:
	~CDirectX3D();
	HRESULT Initialize();

	static CDirectX3D* Create(CApplicationBase* pApplicaton, bool bWindowMode);

	static CDirectX3D* Create(void);

	bool Begin();
	void End();
	void SwapBuffer();

	LPDIRECT3DDEVICE9* GetDevice();
	
private:
	LPDIRECT3DDEVICE9	m_3DDevice;
	LPDIRECT3D9			m_Direct3D;
	CApplicationBase*	m_pApplication;
	bool				m_bWindowMode;
	static CSmart_ptr<CDirectX3D>	m_pCDirectX3D;
	D3DPRESENT_PARAMETERS	m_D3dpp;


	CDirectX3D(CApplicationBase * pApplication, bool bWindowMode);
	//CDirectX3D(){};


	
};

