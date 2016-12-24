#include "Tutorial.h"
#include "DXInput.h"

CTutorial::CTutorial()
{
	bTutFade = true;
	bEnd = false;
	bEnd2 = false;
	bEnd3 = false;
}


CTutorial::~CTutorial()
{
}

void CTutorial::Initialize()
{

	m_Plate.Initialize("Title2.bmp", D3DXVECTOR3(CApplicationBase::GetWidth() / 2, CApplicationBase::GetHight() / 2, 0), D3DXVECTOR2(CApplicationBase::GetWidth(), CApplicationBase::GetHight()));
	m_FadeWhite.Initialize(D3DXVECTOR3(CApplicationBase::GetWidth() / 2, CApplicationBase::GetHight() / 2, -1), D3DXVECTOR2(CApplicationBase::GetWidth(), CApplicationBase::GetHight()), D3DXCOLOR(255,255,255,255));

}

void CTutorial::Update()
{
	if(bTutFade)
	{
	 bTutFade = !m_FadeWhite.FadeOut(3, 0);
	}
	else if(!bEnd)
	{
		bEnd = m_FadeWhite.FadeIn(3, 255);
	}
	else if(!bEnd2)
	{
		bEnd2 = m_Plate.FadeOut(1,0);
	}
	else if(!bEnd3)
		bEnd3 = m_FadeWhite.FadeOut(3,0);

}
void CTutorial::Draw()
{
	C2DObj::Draw();
	m_FadeWhite.Draw();
}
