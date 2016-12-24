#include "ApplicationBase.h"
#include "DXAppBase.h"
#include "d3dx9.h"
#include "dinput.h"
#include <string.h>
#include "..//Player.h"
#include "..//ObjectFactory.h"
#include "..//ObjectMediator.h"
#include "..//DXInput.h"
#include "..//ResourceManeger.h"
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



//=============================================
//�}�N����`
//=============================================
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)

////*******************************************
////�\���̐錾
////*******************************************
//typedef struct {
//	D3DXVECTOR3 pos;						//���_���W
//	float		rhw;						//�e�N�X�`��
//	D3DCOLOR	col;						//���_�J���[
//	D3DXVECTOR2	tex;
//
//}VERTEX_2D;
//
//typedef enum
//{
//	GAME_TITLE,
//	GAME_MAIN,
//	GAME_OVER
//
//
//}GAMESTATUS;



////////////////////////////////////////
//�@����������
////////////////////////////////////////
BOOL CDXAppBase::Initialize(void)
{
	CApplicationBase::Initialize();

	//DirectX�̐���������
	m_DirectX3D = CDirectX3D::Create(this, true);
	m_DirectX3D -> Initialize();

	//���̓f�o�C�X�̏�����
	CDXInput::Initialize(m_hWnd);

	//�Q�[���Ǝ��̏�����
	//m_MainGame.SetPtr();

	//�J����������
	//Camera.Initialize();

	//SceneManeger������
	m_SceneManeger.SwapScene();

	return TRUE;


}

////////////////////////////////////////
//�@���C�����[�v
////////////////////////////////////////
void CDXAppBase::Loop(void)
{

	MSG Msg;

	while (1)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{//-----���b�Z�[�W����������-----

			if (Msg.message == WM_QUIT)
				break;
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);

		}
		else
		{//-----�Q�[�����̏���-----

			if (FPSKeeper())//60FPS�ŏ��������
			{
				////�V�[���̍X�V
				m_SceneManeger.Updata();


				////�X�V��̍X�V
				m_SceneManeger.LateUpdata();

				////����Scene���ݒ肳��Ă�����ύX
				m_SceneManeger.SwapScene();
			}

			m_DirectX3D->Begin();		//�`��J�n

			//�`����s	
			m_SceneManeger.PrevDraw();
			m_SceneManeger.Draw();
			m_DirectX3D->End();			//�`��I��


		}

	}

}


void CDXAppBase::ReleaseApp()
{
	CObjectFactoryManeger::Instance()->AllRelease();
	CResourceManeger::Instance()->Release();


}




