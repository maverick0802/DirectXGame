#pragma once

template <class T>
class CSingleton
{
	friend T;
//*******ƒƒ“ƒo•Ï”*******
private: 
	static T* m_Instance;

public:


//*******ƒƒ“ƒoŠÖ”*******
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



