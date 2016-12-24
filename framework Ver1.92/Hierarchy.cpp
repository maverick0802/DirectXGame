#include "Hierarchy.h"
#include "ResourceLoader.h"

const char TEXTURE_FILE[256] = "data/TEXTURE/";

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CHierarchy::CHierarchy(void)
{
	m_szDir[0] = 0;
}


//---------------------------------------------------------------------------------------
// フレーム生成
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::CreateFrame(LPCSTR pMesh, LPD3DXFRAME* ppNewFrame)
{
	// 取りあえずNULLでクリア
	*ppNewFrame = NULL;

	// フレーム用メモリ確保
	MYFRAME* pFrame = new MYFRAME;
	if (pFrame == NULL) {
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pFrame, sizeof(MYFRAME));

	// フレーム名のコピー
	if (pMesh) {
		// フレーム名あり
		pFrame->Name = new char[lstrlenA(pMesh) + 1];
		if (pFrame->Name == NULL) {
			delete pFrame;
			return E_OUTOFMEMORY;
		}
		lstrcpyA(pFrame->Name, pMesh);
	}
	else {
		// フレーム名なし
		pFrame->Name = NULL;
	}

	// マトリックス初期化
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

	// 確保したフレームを返す
	*ppNewFrame = pFrame;
	return S_OK;
}

//---------------------------------------------------------------------------------------
// メッシュコンテナ生成
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
	// 取りあえずNULLをセットしておく
	*ppNewMeshContainer = NULL;

	// 正常なメッシュ以外はエラーで戻す
	if (pMeshData->Type != D3DXMESHTYPE_MESH || pMeshData->pMesh->GetFVF() == 0) {
		return E_FAIL;
	}
	// メッシュオブジェクト取得
	LPD3DXMESH pMesh = pMeshData->pMesh;

	// メッシュコンテナ用メモリの確保
	MYMESHCONTAINER* pMeshContainer = new MYMESHCONTAINER;
	if (pMeshContainer == NULL) {
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));

	// メッシュ名のコピー
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

	// D3Dデバイス取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pMesh->GetDevice(&pDevice);

	// ポリゴン(三角形)数取得
	int iFacesAmount = pMesh->GetNumFaces();

	// 法線有無のチェック
	if (pMesh->GetFVF() & D3DFVF_NORMAL) {
		pMeshContainer->MeshData.pMesh = pMesh;
		pMesh->AddRef();
	}
	else {
		// 法線を持たない場合は追加
		if (FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL, pDevice, &pMeshContainer->MeshData.pMesh))) {
			pDevice->Release();
			DestroyMeshContainer(pMeshContainer);
			return E_FAIL;
		}
		pMesh = pMeshContainer->MeshData.pMesh;
		D3DXComputeNormals(pMesh, NULL);
	}

	// マテリアル用メモリ確保
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

	// マテリアルの設定
	if (NumMaterials > 0) {
		//// カレントディレクトリを変更
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

		//// カレントディレクトリを元に戻す
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

	// 属性テーブルを取得
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

	// D3Dデバイス解放
	pDevice->Release();

	// スキン情報があるか
	if (pSkinInfo) {
		// スキン情報を保存(参照カウンタ加算)
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		// ワールド・マトリックスの場所を確保
		DWORD dwBoneNum = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrix = new D3DXMATRIX[dwBoneNum];
		if (pMeshContainer->pBoneOffsetMatrix == NULL)
			return E_OUTOFMEMORY;

		// ワールド・マトリックスを初期化
		for (DWORD i = 0; i < dwBoneNum; ++i) {
			pMeshContainer->pBoneOffsetMatrix[i] =
				*pSkinInfo->GetBoneOffsetMatrix(i);
		}

		// スキン用に変換
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

	// 確保したメッシュコンテナを返す
	*ppNewMeshContainer = pMeshContainer;
	return S_OK;
}

//---------------------------------------------------------------------------------------
// フレーム破棄
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameToFree;
	SAFE_DELETE_ARRAY(pFrame->Name);
	SAFE_DELETE(pFrame);
	return S_OK;
}

//---------------------------------------------------------------------------------------
// メッシュコンテナ破棄
//---------------------------------------------------------------------------------------
HRESULT CHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerToFree;

	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);

	// 全テクスチャの解放
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
// Xファイルのあるディレクトリを設定
//---------------------------------------------------------------------------------------
void CHierarchy::SetDirectory(LPCTSTR pszDir)
{
	if (pszDir)
		lstrcpy(m_szDir, pszDir);
	else
		m_szDir[0] = 0;
}