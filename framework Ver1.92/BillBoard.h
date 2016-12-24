#pragma once
#include "plate.h"

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


class CBillBoard
{
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DCOLOR	col;
		D3DXVECTOR2 tex;
	}VERTEX_3D;

	VERTEX_3D m_VertexData[4];
	D3DXVECTOR3 m_Position;
	CTexture* m_Texture;

	void MakeVertex(D3DXVECTOR3 pos, D3DXVECTOR2 size);
public:
	void Initialize(std::string TextureName, D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Update();
	void Draw();
	CBillBoard();
	~CBillBoard();
};

