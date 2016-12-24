#pragma once
#include "FactoryBase.h"
#include "source\Smart_ptr.h"
#include <vector>


#pragma		comment(lib, "d3dx9.lib")
#pragma		comment(lib, "d3d9.lib")
#include		<d3d9.h>
#include		<d3dx9.h>


class CDXDeviceFactory : public CFactoryBase
{
public:



	void Create(CSmart_ptr<LPDIRECT3DDEVICE9> spReceiver){
	
		if (m_tpDevice.GetPtr() == NULL)
			m_tpDevice.SetPtr(new LPDIRECT3DDEVICE9);
		
		spReceiver = m_tpDevice;

	}


	void Delete(void){
	
		m_tpDevice.Release();
	
	}


private:


	CDXDeviceFactory(){}
	~CDXDeviceFactory(){};
	static CSmart_ptr<LPDIRECT3DDEVICE9> m_tpDevice;

};

CSmart_ptr<LPDIRECT3DDEVICE9> CDXDeviceFactory::m_tpDevice;
