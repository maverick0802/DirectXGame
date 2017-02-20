#pragma once

//******************************
//
//　インクルード
//
//******************************
#include "CollisionBase.h"
#include <list>


//******************************
//
//　定数定義
//
//******************************

//******************************
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
	const D3DXCOLOR DEFAULTCOLOR = D3DXCOLOR(255,   0, 0, 100);
	const D3DXCOLOR HITCOLOR	 = D3DXCOLOR(  0, 255, 0, 100);

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

