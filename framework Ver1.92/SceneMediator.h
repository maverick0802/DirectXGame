#pragma once
namespace ID{

	typedef enum{

		SCENE_NULL = -1,
		SCENE_TITLE = 0,
		SCENE_MAIN,
		SCENE_END

	}SCENE_ID;

}


class CSceneMediator
{

	ID::SCENE_ID m_NowScene;
	ID::SCENE_ID m_NextScene;

public:
	CSceneMediator();
	~CSceneMediator();

	static CSceneMediator* Instance();
	ID::SCENE_ID GetNowScene();
	ID::SCENE_ID GetNextScene();
	void SetNextScene(ID::SCENE_ID SceneID);
	void SetNowScene(ID::SCENE_ID SceneID);
};

