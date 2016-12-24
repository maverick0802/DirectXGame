#pragma once
#include "ResourceLoader.h"
#include <string>
#

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CPlate
{
	typedef struct
	{
		D3DXVECTOR3 pos;
		float		rhw;
		D3DCOLOR	col;
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	VERTEX_2D m_VertexData[4];
	CTexture m_Texture;
	D3DXCOLOR m_RGBA;
	void MakeVertex(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
public:
	CPlate();
	~CPlate();
	void Initialize(std::string, D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Initialize( D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
	void Update();
	void Draw();
	bool FadeOut(float Second, float TargetAlpha);
	bool FadeIn( float Second,float TargetAlpha);
};

