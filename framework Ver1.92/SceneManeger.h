////////////////////////////////////////////////
// FileName  : SceneManeger
// ClassName : CSceneManeger
// auther    : Y@GI
// `Detail`
// V[ΜΆ¬Ζjόπs€
//
//**********************************************
// 1/14
//
//
//
//
//
//
//
/////////////////////////////////////////////////
#pragma once

#include "SceneBase.h"
#include <list>

class CSceneManeger
{
	//std::list<CSceneBase*> m_SceneList;
	CSceneBase* m_NowScene;
	CSceneBase* m_NextScene;

public:
	CSceneManeger(void);
	~CSceneManeger(void);
	void Initialize();
	void Updata();
	void LateUpdata();
	void PrevDraw();
	void Draw();
	void SwapScene();

};

