#pragma once
#include "GameObject.h"
////////////////////////////////////////////////
//
// �N���X��: CollisionBase
// �쐬�ҁ@: ���Y�@�G�I
// �ڍ�
//�@�����蔻��̊��N���X�B�����蔻���OnOff���̑����낢��
// ---------------------------------------------
// �X�V����:
// 20170101 �쐬
////////////////////////////////////////////////


class CCollisionBase
{
private:
	bool m_Active;						//�����蔻����Ƃ邩�Ƃ�Ȃ���
	bool m_Hit;							//����܂łɉ����������Ă��邩(����Ȃ�����)
	CGameObject*  m_HitedObject;		//���������I�u�W�F�N�g�̎Q��
	CGameObject*  m_ReferenceObject;	//���������Ă�I�u�W�F�N�g�̎Q��
protected:
	D3DXMATRIX* m_pWorld;	//���[���h�s��
	D3DXVECTOR3 m_Center;	//���S���W
	D3DXVECTOR3 m_Box;		//��`�̃T�C�Y
	LPD3DXMESH	m_pMesh;	//�f�o�b�N�\���p��Box�p���b�V��
	D3DXCOLOR	m_Color;	//�f�o�b�N�\���p��Box�̐F

public:
	CCollisionBase();
	virtual ~CCollisionBase();
	virtual bool Collision(CCollisionBase* Opponent);
	bool CheckCollision(D3DXVECTOR3 HitPos, ID::OBJECT_ID HitLayer, CGameObject* HitObject);
	void OnActive();
	void OffActive();
	void SetHitedObject(CGameObject* SetObject);

	D3DXMATRIX*	GetWorldMatrix() { return m_pWorld; };					//���[���h�s��̎擾
	void	SetWorldMatrix(D3DXMATRIX* World) { m_pWorld = World; };	//���[���h�s��̐ݒ�
	D3DXVECTOR3&	GetCenter() { return m_Center; };					//���S���W�̎擾
	void	SetCenter(D3DXVECTOR3& Center) { m_Center = Center; };		//���S���W�̐ݒ�
	D3DXVECTOR3& GetBox() { return m_Box; };							//��`�T�C�Y�̎擾				
	void	SetBox(D3DXVECTOR3& Box);									//��`�T�C�Y�̐ݒ�
	virtual void Draw();												//�`��i�f�o�b�N�\���j
	void	SetColor(D3DXCOLOR& Color) { m_Color = Color; };			//OBB�̕\���F��ݒ�i�f�o�b�N�j

};
