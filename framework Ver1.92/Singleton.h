#pragma once

template <class T>
class CSingleton
{
	friend T;
//*******メンバ変数*******
private: 
	static T* m_Instance;

public:


//*******メンバ関数*******
protected:
	CSingleton(){};
	virtual ~CSingleton(){};
private:
	CSingleton(const CSingleton&){};
	void operator= (const CSingleton&){};
public:
	static T& GetInstance(){ 
		static T Instance;
		//if (m_Instance)
		//{

		//	m_Instance = &Instance;
		//}

		return Instance;
	}

};
template<class T> T* CSingleton<T>::m_Instance = NULL;



