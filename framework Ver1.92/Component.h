#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
class CComponent
{

private:
	CTransform  m_Transform;
	CMesh		m_Mesh;

	
public:

private:

public:
	CComponent();
	virtual void Initialize(CMesh);
	virtual void Draw();
	virtual void Update();
	virtual void UnInitialize();
	virtual ~CComponent();
};

