#include "GoalLogo.h"


CGoalLogo::CGoalLogo()
{
}


CGoalLogo::~CGoalLogo()
{



}

void CGoalLogo::Initialize()
{

	m_Bill.Initialize("Summer.jpg", D3DXVECTOR3(0, 26, 22), D3DXVECTOR2(10, 10));
	SetPos(D3DXVECTOR3(10, 10, 10));
}

void CGoalLogo::Update()
{

	m_Bill.Update();

}


void CGoalLogo::Draw()
{

	m_Bill.Draw();

}
