#pragma once
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
protected:
	D3DXMATRIX* m_pWorld;	//ワールド行列
	D3DXVECTOR3 m_Center;	//中心座標
	D3DXVECTOR3 m_Box;		//矩形のサイズ
	LPD3DXMESH	m_pMesh;	//デバック表示用のBox用メッシュ
	D3DXCOLOR	m_Color;	//デバック表示用のBoxの色

public:
	CCollisionBase();
	virtual ~CCollisionBase();
	virtual bool Collision(CCollisionBase* Opponent);
	bool CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject);
	void OnActive();
	void OffActive();
	void SetHitedObject(CGameObject* SetObject);

	D3DXMATRIX*	GetWorldMatrix() { return m_pWorld; };					//ワールド行列の取得
	void	SetWorldMatrix(D3DXMATRIX* World) { m_pWorld = World; };	//ワールド行列の設定
	D3DXVECTOR3&	GetCenter() { return m_Center; };					//中心座標の取得
	void	SetCenter(D3DXVECTOR3& Center) { m_Center = Center; };		//中心座標の設定
	D3DXVECTOR3& GetBox() { return m_Box; };							//矩形サイズの取得				
	void	SetBox(D3DXVECTOR3& Box);									//矩形サイズの設定
	virtual void Draw();												//描画（デバック表示）
	void	SetColor(D3DXCOLOR& Color) { m_Color = Color; };			//OBBの表示色を設定（デバック）

};
