#include "TitleLogo.h"
#include "source\ApplicationBase.h"
#include "DXInput.h"
#include "SceneMediator.h"

CTitleLogo::CTitleLogo()
{
}


CTitleLogo::~CTitleLogo()
{
}

void CTitleLogo::Initialize()
{

	m_Plate.Initialize("Title.bmp", D3DXVECTOR3(CApplicationBase::GetWidth() / 2, CApplicationBase::GetHight() / 2, 0), D3DXVECTOR2(CApplicationBase::GetWidth(), CApplicationBase::GetHight()));
	m_FadeWhite.Initialize(D3DXVECTOR3(CApplicationBase::GetWidth() / 2, CApplicationBase::GetHight() / 2, -1), D3DXVECTOR2(CApplicationBase::GetWidth(), CApplicationBase::GetHight()), D3DXCOLOR(255,255,255,0));
}


void CTitleLogo::Update()
{
	static bool PushSpace = false;
	if (CDXInput::GetKeyTrigger(DIK_SPACE))
	{
		PushSpace = true;
	}
	if(PushSpace)
		if(m_FadeWhite.FadeIn(3,255))
					CSceneMediator::Instance()->SetNextScene(ID::SCENE_MAIN);

}

void CTitleLogo::Draw()
{


	C2DObj::Draw();
	m_FadeWhite.Draw();

}
