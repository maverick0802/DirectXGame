#pragma once

template<class T>

class CCOM_ptr
{
private:
	T* m_pPtr;

protected:
	void AddRef(T * pPtr)
	{
		pPtr -> AddRef();					//参照カウンタを加算
	}

	void Release(T* pPtr)
	{
		pPtr -> Release();					//参照カウンターを減少
	}

public:
	//コンストラクタ
	explicit CCOM_ptr(T* pPtr = NULL, bool bAdd = false)
	{
		if (pPtr && bAdd)
			AddRef(pPtr);

		m_pPtr = pPtr;
	}

	//コピーコンストラクタ
	CCOM_ptr(const CCOM_ptr& src){
		// コピー元の参照カウンタを1つ増やす
		if (src->m_pPtr)
			AddRef(src.m_pPtr);

		// コピー
		m_pPtr = src.m_pPtr;
	}

	//デストラクタ
	~CCOM_ptr(){ if (m_pPtr) Release(m_pPtr); }

	//演算子
	//＝演算子(COMポインタ同士)
	CCOM_ptr& operator =(const CCOM_ptr& src)
	{
	
		if (m_pPtr)
			Release(m_pPtr);

		if (src.m_pPtr)
			AddRef(src.m_pPtr);

		m_pPtr = src.m_pPtr;

		return *this;
	}

	//＝演算子(Interfase同士)
	void operator=(T* pPtr)
	{
	
		if (m_pPtr)
			Release(m_pPtr);

		m_pPtr = pPtr;
	}

	//!=比較演算子
	bool operator != (int Val)
	{
	
		if (Val != (int)m_pPtr)
			return true;

		return false;
	}

	//==比較演算子
	bool operator == (int Val)
	{

		if (Val == (int)m_pPtr)
			return true;

		return false;
	}

	//ポインタを貸し出す
	T* GetPtr(){ return m_pPtr; }
	
	//ポインタのアドレスを貸し出す
	T** GetPtrPtr(){ return &m_pPtr; }

	//Interface生成関数用のポインタアドレス受け渡し
	T** ToCreator()
	{
		if (m_pPtr)
			Release(m_pPtr);

		return &m_pPtr;
	}

};

