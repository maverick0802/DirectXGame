#pragma once
#include "C2DObj.h"
class CTitleLogo :
	public C2DObj
{
	CPlate m_FadeWhite;
public:
	void Initialize();
	void Update();
	void Draw();
	CTitleLogo();
	~CTitleLogo();
};

