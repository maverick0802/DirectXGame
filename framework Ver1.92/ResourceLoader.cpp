#include "ResourceLoader.h"
#include <memory>

CResourceLoader::CResourceLoader()
{
}


CResourceLoader::~CResourceLoader()
{
}

CResourceLoader* CResourceLoader::Instance()
{

	static CResourceLoader Instance;


	return &Instance;
}

//LoaderBase* CResourceLoader::FindLoader()
//{ 
//	//ID::RESOURCE_ID ResourceID;
//	//ResourceID = ExtractResourceID(FileName);
//
//	//switch (ResourceID)
//	//{
//	//case ID::RESOURCE_MESH:
//	//	return CMeshLoader::Instance();
//	//	
//	//	break;
//	//case ID::RESOURCE_TEXTURE:
//	//	return CTextureLoader::Instance();			
//	//	break;
//	//}
//	//return NULL;
//}


ID::RESOURCE_ID CResourceLoader::ExtractResourceID(std::string FileName)
{

	//�@.�@�ȍ~�𒲂ׂăt�@�C���̎�ނ�����
	FileName.find(".");
	std::string FileType;
	FileType = FileName.substr(FileName.find(".") + 1,FileName.size());
	
	if(FileType == "x")
		return ID::RESOURCE_MESH;
	else if(FileType == "png" || FileType == "jpg" || FileType == "bmp" || FileType == "gif")
		return ID::RESOURCE_TEXTURE;

	return ID::RESOURCE_NONE;
}