#pragma once
#include "d3dx9.h"
#include "Texture.h"

// �}�N��
#ifndef SAFE_DELETE_ARRAY
#define	SAFE_DELETE_ARRAY(p) {if(p){delete[]p;p=NULL;}}
#endif
#ifndef SAFE_DELETE
#define	SAFE_DELETE(p) {if(p){delete p;p=NULL;}}
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if(p){p->Release();p=NULL;}}
#endif

struct MYFRAME : public D3DXFRAME
{	// �ŏI�I�ȃ}�g���b�N�X���i�[���邽�߂̕ϐ���ǉ�.
	D3DXMATRIX	CombinedTransformationMatrix;
};

// ���b�V���R���e�i�N���X
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{	// �e�N�X�`����ۑ����邽�߂̕ϐ���ǉ�
	CTexture**	ppTextures;

	// �����e�[�u��
	LPD3DXATTRIBUTERANGE	pAttributeTable;
	DWORD					NumAttributeGroups;
	// �ȉ��̓X�L�����b�V���p
	DWORD			dwWeight;	// �d�݂̐�
	DWORD			dwBone;		// �{�[���̐�
	LPD3DXBUFFER	pBoneBuffer;// �{�[���E�e�[�u��
	LPD3DXMATRIX*	ppBoneMatrix;// �{�[���̃��[���h�s��̐擪
	LPD3DXMATRIX	pBoneOffsetMatrix;// �t���[���Ƃ��Ẵ{�[���̃��[���h�s��
};

class CHierarchy :
	public ID3DXAllocateHierarchy
{
public:
	CHierarchy(void);
	STDMETHOD(CreateFrame)(LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(
		LPCSTR Name,
		CONST D3DXMESHDATA* pMeshData,
		CONST D3DXMATERIAL* pMaterials,
		CONST D3DXEFFECTINSTANCE* pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD* pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER* ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(LPD3DXMESHCONTAINER pMeshContainerBase);
	void SetDirectory(LPCTSTR pszDir);

private:
	TCHAR m_szDir[_MAX_PATH];	// X�t�@�C���̂���f�B���N�g��


};

