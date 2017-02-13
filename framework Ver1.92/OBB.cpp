#include "OBB.h"



COBB::COBB()
{

	m_pMesh = NULL;
	m_Next = NULL;
	SetBox(D3DXVECTOR3(1, 1, 1));
}


COBB::~COBB()
{

	m_pMesh->Release();
	m_pMesh = NULL;

}

bool COBB::Collision(CCollisionBase* HitObject)
{

	//自分と相手のワールド行列を取得
	D3DXMATRIX* MatMe = GetWorldMatrix();
	D3DXMATRIX* MatOpp = HitObject->GetWorldMatrix();
	D3DXVECTOR3 Localvec[6];
	D3DXVECTOR3 BoxLength[6];
	D3DXVECTOR3 MePos;
	D3DXVECTOR3 OppPos;

	//座標位置の算出
	D3DXVec3TransformCoord(&MePos, &GetCenter(), MatMe);
	D3DXVec3TransformCoord(&OppPos, &HitObject->GetCenter(), MatOpp);

	//右上前のベクトル抽出
	Localvec[0] = D3DXVECTOR3(MatMe->_11, MatMe->_12, MatMe->_13);
	Localvec[1] = D3DXVECTOR3(MatMe->_21, MatMe->_22, MatMe->_23);
	Localvec[2] = D3DXVECTOR3(MatMe->_31, MatMe->_32, MatMe->_33);
	Localvec[3] = D3DXVECTOR3(MatOpp->_11, MatOpp->_12, MatOpp->_13);
	Localvec[4] = D3DXVECTOR3(MatOpp->_21, MatOpp->_22, MatOpp->_23);
	Localvec[5] = D3DXVECTOR3(MatOpp->_31, MatOpp->_32, MatOpp->_33);


	//あたり判定のボックス取得
	D3DXVECTOR3 myBox = GetBox();
	D3DXVECTOR3 youBox = HitObject->GetBox();
	BoxLength[0] = Localvec[0] * myBox.x;
	BoxLength[1] = Localvec[1] * myBox.y;
	BoxLength[2] = Localvec[2] * myBox.z;
	BoxLength[3] = Localvec[3] * youBox.x;
	BoxLength[4] = Localvec[4] * youBox.y;
	BoxLength[5] = Localvec[5] * youBox.z;

	D3DXVECTOR3 CenterVec = OppPos - MePos;


	float fLength;
	D3DXVECTOR3 vSep;

	for (int nCnt = 0; nCnt < 6; ++nCnt)
	{
		vSep = Localvec[nCnt];
		fLength = 0.0f;
		for (int nNum = 0; nNum < 6; ++nNum)
		{

			fLength += fabsf(D3DXVec3Dot(&vSep, &BoxLength[nNum]));

		}

		if (fLength < fabsf(D3DXVec3Dot(&vSep, &CenterVec)))
		{

			return false;

		}

	}

	for (int nCnt = 0; nCnt < 3; ++nCnt)
	{
		for (int nNum1 = 3; nNum1 < 6; ++nNum1)
		{
			D3DXVec3Cross(&vSep, &Localvec[nCnt], &Localvec[nNum1]);
			D3DXVec3Normalize(&vSep, &vSep);
			fLength = 0.0f;
			for (int nNum2 = 0; nNum2 < 6; ++nNum2)
			{

				fLength += fabsf(D3DXVec3Dot(&vSep, &BoxLength[nNum2]));

			}

			if (fLength < fabsf(D3DXVec3Dot(&vSep, &CenterVec)))
			{

				return false;

			}
		}
	}

	SetColor(D3DXCOLOR(0,255,0,100));
	HitObject->SetColor(D3DXCOLOR(0, 255, 0, 100));

	return true;
}

void COBB::Draw()
{
	D3DXMATRIX world;

	D3DXMatrixTranslation(&world, m_Center.x, m_Center.y, m_Center.z);
	world *= *m_pWorld;

	LPDIRECT3DDEVICE9 pDevice = *CDirectX3D::Create()->GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &world);
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(m_Color.r / 255, m_Color.g / 255, m_Color.b / 255, m_Color.a / 255);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	m_pMesh->DrawSubset(0);

}

