#pragma once
#include "C3DObj.h"
#include "BillBoard.h"


class CGoalLogo :
	public C3DObj
{
	CBillBoard m_Bill;

public:
	CGoalLogo();
	~CGoalLogo();
	void Initialize();
	void Update();
	void Draw();

};

