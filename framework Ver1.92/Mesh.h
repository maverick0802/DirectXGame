#pragma once
#include "DirectX3D.h"
#include <string>
#include <vector>
#include "Hierarchy.h"
#include "Texture.h"
#include "ResourceBase.h"
#include <memory>

class CMesh : public CResourceBase
{
private:
	LPD3DXFRAME									m_FrameRoot;		//参照
	LPD3DXANIMATIONCONTROLLER					m_pAnimeCtr;		//コピー
	UINT										m_uNumAnimeSet;		//？
	LPD3DXANIMATIONSET*							m_ppAnimeSet;		//？
	CHierarchy									m_Hierarchy;		//
	DWORD										m_dwPrev;


public:
private:
public:
	HRESULT UnInitialize();
	virtual void Release();
	virtual void Draw(D3DXMATRIX&);
	virtual void Updata();
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME);
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void SwitchAnimenSet(DWORD SetNumber);
	void CopyAnimeCtrl(LPD3DXANIMATIONCONTROLLER& pAnimeCtrl);
	bool Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectFrame(LPD3DXFRAME pFrameBase, D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectMeshContainer(LPD3DXMESHCONTAINER pMeshContainer, D3DXMATRIX world, D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	void SetAnimeSet(LPD3DXANIMATIONSET*);
	void SetAnimeSetNum(UINT);
	void SetTime(DWORD);
	void SetAnimeCtrl(LPD3DXANIMATIONCONTROLLER);
	void SetStartTime(double);
	LPD3DXFRAME* GetFrame();
	LPD3DXANIMATIONCONTROLLER* GetAnimeCtr();
	UINT GetAnimeNum();
	LPD3DXANIMATIONSET* GetAnimeSet();
	CHierarchy* GetHierarchy();
	CMesh(ID::SCENE_ID);
	CMesh();
	virtual ~CMesh();
};

 