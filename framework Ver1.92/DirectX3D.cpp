#include "DirectX3D.h"

CSmart_ptr<CDirectX3D>	CDirectX3D::m_pCDirectX3D;


CDirectX3D::CDirectX3D(CApplicationBase * pApplication, bool bWindowMode) :
m_bWindowMode(bWindowMode),
m_pApplication(pApplication),
m_Direct3D(NULL){}

CDirectX3D::~CDirectX3D()
{
}


CDirectX3D* CDirectX3D::Create(CApplicationBase* pApplicaton, bool bWindowMode)
{

	static CSmart_ptr<CDirectX3D> pCDirectX3D( new CDirectX3D(pApplicaton, bWindowMode));

	m_pCDirectX3D = pCDirectX3D;

	return m_pCDirectX3D.GetPtr();
};

CDirectX3D* CDirectX3D::Create(void)
{

	if (!(m_pCDirectX3D.GetPtr()))
		return nullptr;

	return m_pCDirectX3D.GetPtr();
};

HRESULT CDirectX3D::Initialize()
{

	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	// Direct3D�I�u�W�F�N�g�̐���
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3D == NULL){
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���K��
	if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ���[�N���[���N���A
	d3dpp.BackBufferWidth = m_pApplication->GetWidth();	// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = m_pApplication->GetHight();	// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̐ݒ�
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����B
	d3dpp.Windowed = m_bWindowMode;			// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (m_bWindowMode){
		// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else{
		// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	int a = 1;

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v
		*m_pApplication->GethWnd(),			// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&m_3DDevice)))	{			// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>�ƃn�[�h�E�F�A�ōs���A<���_����>��CPU�ōs��
		if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
			D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v
			*m_pApplication->GethWnd(),								// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
			&d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
			&m_3DDevice))){					// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

			// �L�̐ݒ肪���s������
			// �f�o�C�X�쐬����]<�`��>�ƃn<���_����>��CPU�ōs��
			if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
				D3DDEVTYPE_REF,						// �f�o�C�X�^�C�v
				*m_pApplication->GethWnd(),								// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
				&d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
				&m_3DDevice))){					// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̃p�����[�^�̐ݒ�
	m_3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	m_3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// �A���t�@�u�����h���s��
	m_3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// �\�[�X�̐ݒ�
	m_3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// �ł��Ƃ̐ݒ�

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	m_3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`��U�l�̌J��Ԃ��ݒ�
	m_3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`��V�l�̌J��Ԃ��ݒ�
	m_3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g�����̕�Ԑݒ�

	m_3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);


	return S_OK;
}

void CDirectX3D::Begin(){
	
	m_3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 255, 0), 1.0f, 0);
	m_3DDevice->BeginScene();

}

void CDirectX3D::End(){

	m_3DDevice->EndScene();
	m_3DDevice->Present(NULL, NULL, NULL, NULL);
}
	

LPDIRECT3DDEVICE9* CDirectX3D::GetDevice()
{


	return &m_3DDevice;

}

