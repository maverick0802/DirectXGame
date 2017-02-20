#include "MeshLoader.h"
#include "ResourceLoader.h"
#include "ResourceManeger.h"
const std::string MESH_FOLDER = "data/MODEL/";

CMeshLoader::CMeshLoader() :
LoaderBase(ID::RESOURCE_MESH)
{



}


CMeshLoader::~CMeshLoader()
{


}

CMeshLoader* CMeshLoader:: Instance()
{

	static CMeshLoader Instance;


	return &Instance;
}


void CMeshLoader::Load( std::string FileName, CMesh** Recive)
{
	CMesh* ReciveMesh = new CMesh;

	if (*Recive = dynamic_cast<CMesh*>(CheckMap(FileName)))
	{
		return;
	}

	std::string AllFilePass = MESH_FOLDER + FileName;

	ReciveMesh->GetHierarchy()->SetDirectory(MESH_FOLDER.c_str());

	
	DWORD				dwAnimeSetNum = 0;
	LPD3DXANIMATIONSET*	ppAnimeSet = NULL;
	//階層構造メッシュの読み込み 
	HRESULT hr = D3DXLoadMeshHierarchyFromX(
		AllFilePass.c_str(),
		D3DXMESH_MANAGED,
		*CDirectX3D::Create()->GetDevice(),
		ReciveMesh->GetHierarchy(),
		NULL,
		ReciveMesh->GetFrame(),
		ReciveMesh->GetAnimeCtr()
		);
	if (FAILED(hr)) 
		return ;

	//ボーンとフレームの関連付け
	hr = AllocAllBoneMatrix(*ReciveMesh->GetFrame(),*ReciveMesh->GetFrame());
	if (FAILED(hr)) 
		return ;

	 //アニメーションセット取得
	 dwAnimeSetNum = 0;
	 if (*ReciveMesh->GetAnimeCtr() != NULL)
	 {
		 dwAnimeSetNum = (*ReciveMesh->GetAnimeCtr())->GetNumAnimationSets();
		 if (dwAnimeSetNum > 0)
		 {

			 ppAnimeSet = new LPD3DXANIMATIONSET[dwAnimeSetNum];
			 for (DWORD nCnt = 0; nCnt < dwAnimeSetNum; nCnt++)
				 (*ReciveMesh->GetAnimeCtr())->GetAnimationSet(nCnt, &ppAnimeSet[nCnt]);
		 }

	 }

	 ReciveMesh->SetTime(::timeGetTime());
	 ReciveMesh->SetAnimeSet(ppAnimeSet);
	 ReciveMesh->SetAnimeSetNum(dwAnimeSetNum);
	 ResistMap(FileName, ReciveMesh);
	 *Recive = ReciveMesh;
	
}

HRESULT CMeshLoader::AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameRoot)
{

	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER *)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;

	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];

	for (DWORD nCnt = 0; nCnt < dwBoneNum; nCnt++)
	{
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(nCnt));
		if (!pFrame)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[nCnt] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CMeshLoader::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
{

	MYFRAME* pFrame = (MYFRAME *)pFrameBase;

	HRESULT hr = S_OK;

	//ルートフレームの確保
	if (pFrame->pMeshContainer)
	{

		hr = AllocBoneMatrix(pFrame->pMeshContainer, pFrameRoot);
			if (FAILED(hr))
				return hr;
	}
	//兄弟フレームの確保
	if (pFrame->pFrameSibling)
	{

		hr = AllocAllBoneMatrix(pFrame->pFrameSibling, pFrameRoot);
		if (FAILED(hr))
			return hr;
	}

	//子フレームの確保
	if (pFrame->pFrameFirstChild)
	{

		hr = AllocAllBoneMatrix(pFrame->pFrameFirstChild, pFrameRoot);
	}


	return hr;
}

