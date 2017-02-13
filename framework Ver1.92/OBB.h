#pragma once

//******************************
//
//　インクルード
//
//******************************
#include "CollisionBase.h"
#include <list>


//*******************************
//
// クラス定義
//
//*******************************
class COBB :
	public CCollisionBase
{
	///////////////////////////
	// メンバ変数
	//////////////////////////
private:
	COBB*		m_Next;		//次のOBB

	//////////////////////////
	//　メンバ関数
	//////////////////////////
public:
	COBB();
	virtual ~COBB();
	bool Collision(CCollisionBase* Opponent);							//あたり判定
	COBB*	GetNext() { return m_Next; };								//次のOBBを取得
	void	SetNext(COBB* Next) { m_Next = Next; };						//次のOBBを取得
	void	Draw();														//描画（デバック描画）

};

