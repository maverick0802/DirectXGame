#pragma once

#include "DirectX3D.h"
#include "C3DObj.h"
class CCamera:
	public C3DObj
{
public:
	
	void Initialize();
	void Update();
	void LateUpdate();
	void Draw();
	void UnInitialize();

	HRESULT Setup();
	D3DXVECTOR3 GetLookAtPos();
	D3DXVECTOR3 GetUpVec();
	D3DXMATRIX	GetCameraMat();

	CCamera();
	CCamera(ID::SCENE_ID);
	~CCamera();
private:
	HRESULT SetupCamera();
	HRESULT SetupLight();
	D3DXMATRIX		m_CameraMat;
	D3DXMATRIX		m_matView;	//�r���[�s��
	D3DXMATRIX		m_matProj;	//�v���W�F�N�V�����s��
	D3DXVECTOR3		m_EyePt;	// �J�������W
	D3DXVECTOR3		m_LookatPt;	// �����_���W
	D3DXVECTOR3		m_UpVec;	// ������x�N�g��
};

