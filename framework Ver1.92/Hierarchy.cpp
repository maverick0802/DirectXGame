#include "Hierarchy.h"
#include "ResourceLoader.h"

const char TEXTURE_FILE[256] = "data/TEXTURE/";

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CHierarchy::CHierarchy(void)
{
	m_szDir[0] = 0;
}


//---------------------------------------------------------------------------------------
// �t���[������
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::CreateFrame(LPCSTR pMesh, LPD3DXFRAME* ppNewFrame)
{
	// ��肠����NULL�ŃN���A
	*ppNewFrame = NULL;

	// �t���[���p�������m��
	MYFRAME* pFrame = new MYFRAME;
	if (pFrame == NULL) {
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pFrame, sizeof(MYFRAME));

	// �t���[�����̃R�s�[
	if (pMesh) {
		// �t���[��������
		pFrame->Name = new char[lstrlenA(pMesh) + 1];
		if (pFrame->Name == NULL) {
			delete pFrame;
			return E_OUTOFMEMORY;
		}
		lstrcpyA(pFrame->Name, pMesh);
	}
	else {
		// �t���[�����Ȃ�
		pFrame->Name = NULL;
	}

	// �}�g���b�N�X������
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

	// �m�ۂ����t���[����Ԃ�
	*ppNewFrame = pFrame;
	return S_OK;
}

//---------------------------------------------------------------------------------------
// ���b�V���R���e�i����
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::CreateMeshContainer(
	LPCSTR					Name,
	CONST D3DXMESHDATA*		pMeshData,
	CONST D3DXMATERIAL*		pMaterials,
	CONST D3DXEFFECTINSTANCE*	pEffectInstances,
	DWORD						NumMaterials,
	CONST DWORD*				pAdjacency,
	LPD3DXSKININFO				pSkinInfo,
	LPD3DXMESHCONTAINER*		ppNewMeshContainer)
{
	// ��肠����NULL���Z�b�g���Ă���
	*ppNewMeshContainer = NULL;

	// ����ȃ��b�V���ȊO�̓G���[�Ŗ߂�
	if (pMeshData->Type != D3DXMESHTYPE_MESH || pMeshData->pMesh->GetFVF() == 0) {
		return E_FAIL;
	}
	// ���b�V���I�u�W�F�N�g�擾
	LPD3DXMESH pMesh = pMeshData->pMesh;

	// ���b�V���R���e�i�p�������̊m��
	MYMESHCONTAINER* pMeshContainer = new MYMESHCONTAINER;
	if (pMeshContainer == NULL) {
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));

	// ���b�V�����̃R�s�[
	if (Name) {
		pMeshContainer->Name = new char[lstrlenA(Name) + 1];
		if (pMeshContainer->Name == NULL) {
			delete pMeshContainer;
			return E_OUTOFMEMORY;
		}
		lstrcpyA(pMeshContainer->Name, Name);
	}
	else
		pMeshContainer->Name = NULL;

	// D3D�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pMesh->GetDevice(&pDevice);

	// �|���S��(�O�p�`)���擾
	int iFacesAmount = pMesh->GetNumFaces();

	// �@���L���̃`�F�b�N
	if (pMesh->GetFVF() & D3DFVF_NORMAL) {
		pMeshContainer->MeshData.pMesh = pMesh;
		pMesh->AddRef();
	}
	else {
		// �@���������Ȃ��ꍇ�͒ǉ�
		if (FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh))) {
			pDevice->Release();
			DestroyMeshContainer(pMeshContainer);
			return E_FAIL;
		}
		pMesh = pMeshContainer->MeshData.pMesh;
		D3DXComputeNormals(pMesh, NULL);
	}

	// �}�e���A���p�������m��
	pMeshContainer->NumMaterials = max(1, NumMaterials); 
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new CTexture*[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount * 3];
	if (pMeshContainer->pAdjacency == NULL
		|| pMeshContainer->ppTextures == NULL
		|| pMeshContainer->pMaterials == NULL) {
		DestroyMeshContainer(pMeshContainer);
		pDevice->Release();
		return E_OUTOFMEMORY;
	}
	//ZeroMemory(pMeshContainer->ppTextures, sizeof(CTexture) * pMeshContainer->NumMaterials);
	CopyMemory(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount * 3);

	// �}�e���A���̐ݒ�
	if (NumMaterials > 0) {
		//// �J�����g�f�B���N�g����ύX
		//TCHAR szCurrentDir[_MAX_PATH];
		//if (m_szDir[0]) {
		//	GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		//	SetCurrentDirectory(TEXTURE_FILE);
		//}
		CopyMemory(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);
		for (DWORD i = 0; i < NumMaterials; ++i) {
			pMeshContainer->pMaterials[i].MatD3D.Ambient = pMeshContainer->pMaterials[i].MatD3D.Diffuse;
			if (pMeshContainer->pMaterials[i].pTextureFilename)
				CResourceLoader::Instance()->FindLoader<CTextureLoader>()->Load(pMeshContainer->pMaterials[i].pTextureFilename, &pMeshContainer->ppTextures[i]);
			else
				pMeshContainer->ppTextures[i] = NULL;
		}

		//// �J�����g�f�B���N�g�������ɖ߂�
		//if (m_szDir[0])
		//	SetCurrentDirectory(szCurrentDir);
	}
	else {
		ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Ambient = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	// �����e�[�u�����擾
	HRESULT hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
		pMeshContainer->MeshData.pMesh->GetFVF(), pDevice, &pMesh);
	if (FAILED(hr)) {
		pDevice->Release();
		return hr;
	}
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	pMeshContainer->MeshData.pMesh = pMesh;
	hr = pMesh->GetAttributeTable(NULL, &pMeshContainer->NumAttributeGroups);
	if (FAILED(hr)) {
		pDevice->Release();
		return hr;
	}
	pMeshContainer->pAttributeTable = new D3DXATTRIBUTERANGE[pMeshContainer->NumAttributeGroups];
	if (pMeshContainer->pAttributeTable == NULL) {
		pMeshContainer->NumAttributeGroups = 0;
		pDevice->Release();
		return E_OUTOFMEMORY;
	}
	hr = pMesh->GetAttributeTable(pMeshContainer->pAttributeTable, NULL);
	if (FAILED(hr)) {
		pDevice->Release();
		return hr;
	}

	// D3D�f�o�C�X���
	pDevice->Release();

	// �X�L����񂪂��邩
	if (pSkinInfo) {
		// �X�L������ۑ�(�Q�ƃJ�E���^���Z)
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		// ���[���h�E�}�g���b�N�X�̏ꏊ���m��
		DWORD dwBoneNum = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrix = new D3DXMATRIX[dwBoneNum];
		if (pMeshContainer->pBoneOffsetMatrix == NULL)
			return E_OUTOFMEMORY;

		// ���[���h�E�}�g���b�N�X��������
		for (DWORD i = 0; i < dwBoneNum; ++i) {
			pMeshContainer->pBoneOffsetMatrix[i] =
				*pSkinInfo->GetBoneOffsetMatrix(i);
		}

		// �X�L���p�ɕϊ�
		hr = pSkinInfo->ConvertToBlendedMesh(
			pMesh, NULL, pMeshContainer->pAdjacency,
			NULL, NULL, NULL,
			&pMeshContainer->dwWeight,
			&pMeshContainer->dwBone,
			&pMeshContainer->pBoneBuffer,
			&pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			return hr;
	}

	// �m�ۂ������b�V���R���e�i��Ԃ�
	*ppNewMeshContainer = pMeshContainer;
	return S_OK;
}

//---------------------------------------------------------------------------------------
// �t���[���j��
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameToFree;
	SAFE_DELETE_ARRAY(pFrame->Name);
	SAFE_DELETE(pFrame);
	return S_OK;
}

//---------------------------------------------------------------------------------------
// ���b�V���R���e�i�j��
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerToFree;

	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);

	// �S�e�N�X�`���̉��
	//if (pMeshContainer->ppTextures->GetTexture()) {
	//	for (DWORD i = 0; i < pMeshContainer->NumMaterials; ++i) {
	//		pMeshContainer->ppTextures[i].Release();
	//	}
	//}
	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

	SAFE_DELETE_ARRAY(pMeshContainer->pAttributeTable);
	pMeshContainer->NumAttributeGroups = 0;

	SAFE_RELEASE(pMeshContainer->pBoneBuffer);
	SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrix);
	SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrix);

	SAFE_DELETE(pMeshContainer);
	return S_OK;
}



//---------------------------------------------------------------------------------------
// X�t�@�C���̂���f�B���N�g����ݒ�
//---------------------------------------------------------------------------------------
void CHierarchy::SetDirectory(LPCTSTR pszDir)
{
	if (pszDir)
		lstrcpy(m_szDir, pszDir);
	else
		m_szDir[0] = 0;
}