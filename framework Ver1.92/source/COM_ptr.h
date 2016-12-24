#pragma once

template<class T>

class CCOM_ptr
{
private:
	T* m_pPtr;

protected:
	void AddRef(T * pPtr)
	{
		pPtr -> AddRef();					//�Q�ƃJ�E���^�����Z
	}

	void Release(T* pPtr)
	{
		pPtr -> Release();					//�Q�ƃJ�E���^�[������
	}

public:
	//�R���X�g���N�^
	explicit CCOM_ptr(T* pPtr = NULL, bool bAdd = false)
	{
		if (pPtr && bAdd)
			AddRef(pPtr);

		m_pPtr = pPtr;
	}

	//�R�s�[�R���X�g���N�^
	CCOM_ptr(const CCOM_ptr& src){
		// �R�s�[���̎Q�ƃJ�E���^��1���₷
		if (src->m_pPtr)
			AddRef(src.m_pPtr);

		// �R�s�[
		m_pPtr = src.m_pPtr;
	}

	//�f�X�g���N�^
	~CCOM_ptr(){ if (m_pPtr) Release(m_pPtr); }

	//���Z�q
	//�����Z�q(COM�|�C���^���m)
	CCOM_ptr& operator =(const CCOM_ptr& src)
	{
	
		if (m_pPtr)
			Release(m_pPtr);

		if (src.m_pPtr)
			AddRef(src.m_pPtr);

		m_pPtr = src.m_pPtr;

		return *this;
	}

	//�����Z�q(Interfase���m)
	void operator=(T* pPtr)
	{
	
		if (m_pPtr)
			Release(m_pPtr);

		m_pPtr = pPtr;
	}

	//!=��r���Z�q
	bool operator != (int Val)
	{
	
		if (Val != (int)m_pPtr)
			return true;

		return false;
	}

	//==��r���Z�q
	bool operator == (int Val)
	{

		if (Val == (int)m_pPtr)
			return true;

		return false;
	}

	//�|�C���^��݂��o��
	T* GetPtr(){ return m_pPtr; }
	
	//�|�C���^�̃A�h���X��݂��o��
	T** GetPtrPtr(){ return &m_pPtr; }

	//Interface�����֐��p�̃|�C���^�A�h���X�󂯓n��
	T** ToCreator()
	{
		if (m_pPtr)
			Release(m_pPtr);

		return &m_pPtr;
	}

};

