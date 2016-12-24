#include "Result.h"
#include "DXInput.h"

CResult::CResult(void)
{
}


CResult::~CResult(void)
{
}

void CResult::Initialize()
{
	m_Plate.Initialize("Result.bmp", D3DXVECTOR3(CApplicationBase::GetWidth() / 2, CApplicationBase::GetHight() / 2, 0), D3DXVECTOR2(CApplicationBase::GetWidth(), CApplicationBase::GetHight()));


}

void CResult::Update()
{

	if(CDXInput::GetKeyTrigger(DIK_SPACE))
 		CSceneMediator::Instance()->SetNextScene(ID::SCENE_TITLE);

}

void CResult::Draw()
{

	C2DObj::Draw();

}
