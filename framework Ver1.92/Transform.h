#pragma once
#include "DirectX3D.h"

class CTransform
{

private:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotetion;
	float		m_Accel;
	float		m_Speed;
	D3DXMATRIX	m_World;

public:
private:
public:
	CTransform();
	~CTransform();
	void Initialize(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, float accel);
	void SetPosition(D3DXVECTOR3);
	void Translate();
	D3DXVECTOR3 GetPosition();
};

