#pragma once
#include "GameObject.h"

//////////////////////////////////////////////////////////
//　クラス名  :　CCollisionBase
//　作成者    :　杉浦宏紀
//　更新履歴  :　20161229 : クラス定義
// ---------------------------------------------------------
//　～詳細～
// あたり判定の基底クラス
///////////////////////////////////////////////////////////
class CCollisionBase
{
public:
	CCollisionBase();
	virtual ~CCollisionBase();

	virtual	bool CheckCollision(CGameObject*) = 0;
};

