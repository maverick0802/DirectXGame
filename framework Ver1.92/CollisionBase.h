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


#include "GameObject.h"


////////////////////////////////////////////////
//
// クラス名: CollisionBase
// 作成者　: 杉浦　宏紀
// 詳細
//　あたり判定の基底クラス。あたり判定のOnOffその他いろいろ
// ---------------------------------------------
// 更新履歴:
// 20170101 作成
////////////////////////////////////////////////


class CCollisionBase
{
private:
	bool m_Active;						//あたり判定をとるかとらないか
	bool m_Hit;							//これまでに何かあたっているか(いらないかも)
	CGameObject*  m_HitedObject;		//あたったオブジェクトの参照
	CGameObject*  m_ReferenceObject;	//くっつけられてるオブジェクトの参照
public:
	CCollisionBase();
	virtual ~CCollisionBase();
	virtual CGameObject* Collision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CCollisionBase* HitObject);
	bool CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject);
	void OnActive();
	void OffActive();
	void SetHitedObject(CGameObject* SetObject);
};
