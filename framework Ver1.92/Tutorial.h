#pragma once
#include "c2dobj.h"
class CTutorial :
	public C2DObj
{
	CPlate m_FadeWhite;
	bool bTutFade;
	bool bEnd;
	bool bEnd2;
	bool bEnd3;
public:
	CTutorial(void);
	~CTutorial(void);
	void Initialize();
	void Update();
	void Draw();

};

