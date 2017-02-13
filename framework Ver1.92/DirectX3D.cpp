#include "DirectX3D.h"

CSmart_ptr<CDirectX3D>	CDirectX3D::m_pCDirectX3D;


CDirectX3D::CDirectX3D(CApplicationBase * pApplication, bool bWindowMode) :
m_bWindowMode(bWindowMode),
m_pApplication(pApplication),
m_Direct3D(NULL){


}

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

	D3DDISPLAYMODE			d3ddm;


	// Direct3D�I�u�W�F�N�g�̐���
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3D == NULL){
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_D3dpp, sizeof(m_D3dpp));						// ���[�N���[���N���A
	m_D3dpp.BackBufferWidth = m_pApplication->GetWidth();	// �Q�[����ʃT�C�Y(��)
	m_D3dpp.BackBufferHeight = m_pApplication->GetHight();	// �Q�[����ʃT�C�Y(��)
	m_D3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	m_D3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����B
	m_D3dpp.Windowed = m_bWindowMode;			// �E�B���h�E���[�h
	m_D3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	m_D3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (m_bWindowMode){
		// �E�B���h�E���[�h
		m_D3dpp.BackBufferFormat = D3DFMT_UNKNOWN;				// �J���[���[�h�̐ݒ�
		m_D3dpp.FullScreen_RefreshRateInHz = 0;
		m_D3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else{
		// �t���X�N���[�����[�h
		m_D3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				// �J���[���[�h�̐ݒ�
		m_D3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_D3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}


	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,			// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,												// �f�o�C�X�^�C�v
		*m_pApplication->GethWnd(),									// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// �f�o�C�X�쐬����̑g�ݍ��킹
		&m_D3dpp,														// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&m_3DDevice)))	{											// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>�ƃn�[�h�E�F�A�ōs���A<���_����>��CPU�ōs��
		if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,		// �f�B�X�v���C�A�_�v�^
			D3DDEVTYPE_HAL,											// �f�o�C�X�^�C�v
			*m_pApplication->GethWnd(),								// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,					// �f�o�C�X�쐬����̑g�ݍ��킹
			&m_D3dpp,													// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
			&m_3DDevice))){											// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^

			// �L�̐ݒ肪���s������
			// �f�o�C�X�쐬����]<�`��>�ƃn<���_����>��CPU�ōs��
			if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,	// �f�B�X�v���C�A�_�v�^
				D3DDEVTYPE_REF,										// �f�o�C�X�^�C�v
				*m_pApplication->GethWnd(),							// �t�H�[�J�X����E�B���h�E�ւ̃n���h��
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,				// �f�o�C�X�쐬����̑g�ݍ��킹
				&m_D3dpp,												// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
				&m_3DDevice))){										// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
				// ���������s
				return E_FAIL;
			}
		}
	}


	m_3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˂�L��

															// �Ō�Ɋ�����ݒ肷��B
	m_3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	m_3DDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);

	m_3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	m_3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

	m_3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);



	return S_OK;
}


//////////////////////////////////
//
//�@�֐���: Begin
//�@����  : �Ȃ�
//�@�߂�l: �Ȃ�
//�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//�@�T�v
//�@�����_�����O�J�n
//
//////////////////////////////////

bool CDirectX3D::Begin(){
	
	//�r���[�|�[�g���N���A
	m_3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(128, 128, 255), 1.0f, 0);

	return SUCCEEDED( m_3DDevice->BeginScene());		//�V�[���J�n

}


//////////////////////////////////
//
//�@�֐���: End
//�@����  : �Ȃ�
//�@�߂�l: �Ȃ�
//�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//�@�T�v
//�@�����_�����O�I��
//
//
//////////////////////////////////

void CDirectX3D::End(){

	m_3DDevice->EndScene();		//�V�[���I��

}

//////////////////////////////////
//
//�@�֐���: SwapBuffer
//�@����  : �Ȃ�
//�@�߂�l: �Ȃ�
//�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//�@�T�v�@
//	�o�b�N�o�b�t�@����ւ�
//
//////////////////////////////////

void CDirectX3D::SwapBuffer() {

	//�o�b�t�@�ɕ`�悵�����e��\��
	if (FAILED(m_3DDevice->Present(NULL, NULL, NULL, NULL))) {
		m_3DDevice->Reset(&m_D3dpp);
	}

}
	

//////////////////////////////////
//
//�@�֐���: GetDevice
//�@����  : �Ȃ�
//�@�߂�l: �Ȃ�
//�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//�@�T�v
//�@�f�o�C�X�̎擾
//
//////////////////////////////////

LPDIRECT3DDEVICE9* CDirectX3D::GetDevice()
{


	return &m_3DDevice;

}

