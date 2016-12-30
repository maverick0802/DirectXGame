#include "Mesh.h"
//****************************************
//
// Meshクラス
//
//
//
//	スキンメッシュアニメーション対応したはず…
//
//
//
//
//
//****************************************


///////////////////////////////////////
// デフォルトコンストラクタ
///////////////////////////////////////
CMesh::CMesh(ID::SCENE_ID SceneID):
CResourceBase(SceneID),
m_FrameRoot(NULL),
m_pAnimeCtr(NULL),
m_uNumAnimeSet(0),
m_ppAnimeSet(NULL),
m_dwPrev(0)
{

	m_ResourceID = ID::RESOURCE_MESH;

}

///////////////////////////////////////
// コンストラクタ
///////////////////////////////////////
CMesh::CMesh():
CResourceBase(ID::SCENE_NULL),
m_FrameRoot(NULL),
m_pAnimeCtr(NULL),
m_uNumAnimeSet(0),
m_ppAnimeSet(NULL),
m_dwPrev(0)
{

	m_ResourceID = ID::RESOURCE_MESH;

}

///////////////////////////////////////
// デストラクタ
///////////////////////////////////////
CMesh::~CMesh()
{



}


///////////////////////////////////////
// 描画処理（総合）
///////////////////////////////////////
void CMesh::Draw(D3DXMATRIX& world)
{
	if (m_pAnimeCtr)
	{
		DWORD dwNow = ::timeGetTime();
		double deltaTime = (dwNow - m_dwPrev) / 1000.0;
		m_dwPrev = dwNow;
		m_pAnimeCtr->AdvanceTime(deltaTime, NULL);

	}
	//(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_WORLD, &world);
	if (m_FrameRoot)
	{
		UpdateFrameMatrices(m_FrameRoot, &world);

		DrawFrame(m_FrameRoot);
	}

}

///////////////////////////////////////
// 部位ごとにボーンを追って描画
///////////////////////////////////////
void CMesh::DrawFrame(LPD3DXFRAME pFrameBase)
{

	LPD3DXMESHCONTAINER pMeshContainer = pFrameBase->pMeshContainer;
	
	while (pMeshContainer){
		//メッシュコンテナの描画
		RenderMeshContainer(pMeshContainer,pFrameBase);

		//次のメッシュコンテナ
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	
	}

	//兄弟フレームがあれば兄弟フレームを描画
	if (pFrameBase->pFrameSibling)
		DrawFrame(pFrameBase->pFrameSibling);

	//子フレームがあれば子フレームを描画
	if (pFrameBase->pFrameFirstChild)
		DrawFrame(pFrameBase->pFrameFirstChild);

}

///////////////////////////////////////
// レンダリング
///////////////////////////////////////
void CMesh::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{

	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;

	if (pMeshContainer->pSkinInfo){
	
		LPD3DXBONECOMBINATION pBoneCombi = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();
		DWORD dwPrevBoneID = UINT_MAX;
		DWORD dwBlendMatrix;

		for (DWORD nCnt = 0; nCnt < pMeshContainer->dwBone; nCnt++)
		{
			dwBlendMatrix = 0;
			for (DWORD nNum = 0; nNum < pMeshContainer->dwWeight; nNum++)
			{
			
				if (pBoneCombi[nCnt].BoneId[nNum] != UINT_MAX)
					dwBlendMatrix = nNum;	
			}

			(*CDirectX3D::Create()->GetDevice())->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrix);

			for (DWORD nNum = 0; nNum < pMeshContainer->dwWeight; nNum++)
			{
				DWORD Id = pBoneCombi[nCnt].BoneId[nNum];

				if (Id != UINT_MAX)
				{

					(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_WORLDMATRIX(nNum),
						&(pMeshContainer->pBoneOffsetMatrix[Id] * (*pMeshContainer->ppBoneMatrix[Id])));

				}

			}

			(*CDirectX3D::Create()->GetDevice())->SetMaterial(&pMeshContainer->pMaterials[pBoneCombi[nCnt].AttribId].MatD3D);
			(*CDirectX3D::Create()->GetDevice())->SetTexture(0,*pMeshContainer->ppTextures[pBoneCombi[nCnt].AttribId]->GetTexture());
			dwPrevBoneID = pBoneCombi[nCnt].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(nCnt);

		}

		return;
	}

	(*CDirectX3D::Create()->GetDevice())->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrID = 0; iAttrID < pMeshContainer->NumMaterials; iAttrID++){
		DWORD dwAttriID = pMeshContainer->pAttributeTable[iAttrID].AttribId;
		(*CDirectX3D::Create()->GetDevice())->SetMaterial(&pMeshContainer->pMaterials[dwAttriID].MatD3D);
		if (pMeshContainer->ppTextures[dwAttriID])
			(*CDirectX3D::Create()->GetDevice())->SetTexture(0, *pMeshContainer->ppTextures[dwAttriID]->GetTexture());
		else
			(*CDirectX3D::Create()->GetDevice())->SetTexture(0, NULL);

		pMeshContainer->MeshData.pMesh->DrawSubset(dwAttriID);
	}


}

///////////////////////////////////////
// フレーム取得
///////////////////////////////////////
LPD3DXFRAME* CMesh::GetFrame()
{

	return &m_FrameRoot;

}

///////////////////////////////////////
// アニメーションコントローラー取得
///////////////////////////////////////
LPD3DXANIMATIONCONTROLLER* CMesh::GetAnimeCtr()
{
	
	return &m_pAnimeCtr;

}

///////////////////////////////////////
//　アニメーション数取得
///////////////////////////////////////
UINT CMesh::GetAnimeNum()
{

	return	m_uNumAnimeSet;

}

///////////////////////////////////////
// アニメーションの取得
///////////////////////////////////////
LPD3DXANIMATIONSET* CMesh::GetAnimeSet()
{

	return m_ppAnimeSet;

}

///////////////////////////////////////
// 階層構造取得
///////////////////////////////////////
CHierarchy* CMesh::GetHierarchy()
{

	return &m_Hierarchy;

}

///////////////////////////////////////
// アニメーションの設定
///////////////////////////////////////
void CMesh::SetAnimeSet(LPD3DXANIMATIONSET* pAnimeSet)
{

	m_ppAnimeSet = pAnimeSet;

}

///////////////////////////////////////
// アニメーション数の設定
///////////////////////////////////////
void CMesh::SetAnimeSetNum(UINT AnimeSetNum)
{

	m_uNumAnimeSet = AnimeSetNum;

}

///////////////////////////////////////
// タイマー設定
///////////////////////////////////////
void CMesh::SetTime(DWORD dwTime)
{

	m_dwPrev = dwTime;

}

///////////////////////////////////////
// アニメーションの開始時間の設定
///////////////////////////////////////
void CMesh::SetStartTime(double dTime)
{

	if (m_pAnimeCtr == NULL) return;
	for (int nCnt = 0; nCnt < m_pAnimeCtr->GetMaxNumTracks(); nCnt++)
		m_pAnimeCtr->SetTrackPosition(nCnt, 0);
	m_pAnimeCtr->ResetTime();
	m_pAnimeCtr->AdvanceTime(dTime, NULL);

}

///////////////////////////////////////
// 後処理
///////////////////////////////////////
void CMesh::Release()
{
	if (m_ppAnimeSet)
	{

		for (int nCnt = 0; nCnt < m_uNumAnimeSet; nCnt++)
		{

			SAFE_RELEASE(m_ppAnimeSet[nCnt])

		}
		SAFE_DELETE_ARRAY(m_ppAnimeSet);
	}
	SAFE_RELEASE(m_pAnimeCtr);

	if (m_FrameRoot)
	{

		D3DXFrameDestroy(m_FrameRoot, &m_Hierarchy);
		m_FrameRoot = NULL;
	}
}

///////////////////////////////////////
// 更新
///////////////////////////////////////
void CMesh::Updata()
{
}

///////////////////////////////////////
// フレームごとの行列を生成
///////////////////////////////////////
void CMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{

	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	if (pParentMatrix)
	{

		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * (*pParentMatrix);

	}
	else
	{
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}

	if (pFrame->pFrameSibling)
	{

		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);

	}

	if (pFrame->pFrameFirstChild)
	{

		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);

	}

}

///////////////////////////////////////
// アニメーションの切り替え
///////////////////////////////////////
void CMesh::SwitchAnimenSet(DWORD dwSetNumber)
{

	if (m_uNumAnimeSet > dwSetNumber || m_pAnimeCtr != NULL)
	{
	
		m_pAnimeCtr->SetTrackAnimationSet(0, m_ppAnimeSet[dwSetNumber]);
	
	}

}

///////////////////////////////////////
// アニメーションコントローラーのコピー
///////////////////////////////////////
void CMesh::CopyAnimeCtrl(LPD3DXANIMATIONCONTROLLER& pAnimeCtrl)
{
	if (m_pAnimeCtr)
		m_pAnimeCtr->CloneAnimationController(m_pAnimeCtr->GetMaxNumAnimationOutputs(),
											  m_pAnimeCtr->GetMaxNumAnimationSets(),
											  m_pAnimeCtr->GetMaxNumTracks(),
											  m_pAnimeCtr->GetMaxNumEvents(),
											  &pAnimeCtrl);
	else
		return;

}

///////////////////////////////////////
// アニメーションコントローラーの設定
///////////////////////////////////////
void CMesh::SetAnimeCtrl(LPD3DXANIMATIONCONTROLLER Recive)
{

	m_pAnimeCtr = Recive;

}

//////////////////////////////////////
// 線分と三角形のあたり判定
//////////////////////////////////////
bool CMesh::Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{

	D3DXVECTOR3 W;
	if (bRay)
	{
		W = L1;
	}
	else
	{
		W = L1 - L0;
	}

	return IntersectFrame(m_FrameRoot, L0, W, bRay, pCross, pNormal);
}

//////////////////////////////////////
// Frame全てのあたり判定
//////////////////////////////////////
bool CMesh::IntersectFrame(LPD3DXFRAME pFrameBase, D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	bool bResult = false;
	if (pFrame->pMeshContainer){
		bResult = IntersectMeshContainer(pFrame->pMeshContainer, pFrame->CombinedTransformationMatrix, L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameSibling)
	{
		bResult = IntersectFrame(pFrame->pFrameSibling, L0, W, bRay, pCross, pNormal);
		if (bResult)
			return bResult;
	}
	if (pFrame->pFrameFirstChild)
	{
		bResult = IntersectFrame(pFrame->pFrameFirstChild, L0, W, bRay, pCross, pNormal);
	}
	return bResult;
}

//////////////////////////////////////
// MeshContainerのあたり判定
//////////////////////////////////////
bool CMesh::IntersectMeshContainer(LPD3DXMESHCONTAINER pMeshContainer, D3DXMATRIX world, D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay, D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{

	bool bResult = false;
	LPD3DXMESH	pMesh= pMeshContainer->MeshData.pMesh;
	LPBYTE		pVtx;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pVtx);
	WORD*		pIdx;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pIdx);
	DWORD	dwStride = pMesh->GetNumBytesPerVertex();
	DWORD	dwIdx = pMesh->GetNumFaces();

	for (DWORD nCnt = 0; nCnt < dwIdx; nCnt++)
	{
		//線と三角形のあたり判定
		D3DXVECTOR3 Point0 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 Point1 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);
		D3DXVECTOR3 Point2 = *(LPD3DXVECTOR3)(pVtx + dwStride * *pIdx++);

		D3DXVec3TransformCoord(&Point0, &Point0, &world);
		D3DXVec3TransformCoord(&Point1, &Point1, &world);
		D3DXVec3TransformCoord(&Point2, &Point2, &world);

		D3DXVECTOR3 Point01 = Point1 - Point0;
		D3DXVECTOR3 Point12 = Point2 - Point1;
		D3DXVECTOR3 Point20 = Point0 - Point2;

		D3DXVECTOR3	N;

		D3DXVec3Cross(&N, &Point01, &W);
		if (D3DXVec3Dot(&N, &(L0 - Point0)) < 0.0f){
			continue;
		}
		D3DXVec3Cross(&N, &Point12, &W);
		if (D3DXVec3Dot(&N, &(L0 - Point1)) < 0.0f){
			continue;
		}
		D3DXVec3Cross(&N, &Point20, &W);
		if (D3DXVec3Dot(&N, &(L0 - Point2)) < 0.0f){
			continue;
		}

		//線分でもあたっているか？
		D3DXVec3Cross(&N, &Point01, &Point12);
		D3DXVec3Normalize(&N, &N);

		float base = D3DXVec3Dot( &N, &W);
		if (base == 0)
		{
			continue;
		}

		float t = D3DXVec3Dot(&N, &(Point0 - L0)) / base;
		if (t < 0.0f)
		{
			continue;			//交点が始点より後方
		}
		if (!bRay && t > 1.0f)
		{
			continue;			//交点が終点より前方
		}
		if (pCross)
			*pCross = L0 + t * W;
		if (pNormal)
			*pNormal = N;


		bResult = true;
		break;
	}
	pMesh->UnlockIndexBuffer();
	pMesh->UnlockVertexBuffer();
	return bResult;

}
