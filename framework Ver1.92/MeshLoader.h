#pragma once
#include "Mesh.h"
#include "LoaderBase.h"
#include <map>
class CMeshLoader : public LoaderBase
{

public:
	static CMeshLoader* Instance();

	
	void Load( std::string, CMesh** ReciveMesh);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameRoot);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	//HRESULT CheckMap(std::string FileName, CMesh* Recive);
	CMeshLoader();
	~CMeshLoader();
};

