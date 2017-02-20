#include <Windows.h>
#include "ApplicationBase.h"
#include "DXAppBase.h"
#include "Smart_ptr.h"
#include "DebugWindow.h"
#include "COM_ptr.h"

#pragma		comment(lib, "d3dx9.lib")
#pragma		comment(lib, "d3d9.lib")
#include		<d3d9.h>
#include		<d3dx9.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCommandLine, int cmdShow)

{
	//Debug::DebugWindow Debug;
	//Debug.Init();

	//CApplicationBase::SetDebug();
	CSmart_ptr<CApplicationBase> sp_Game(new CDXAppBase);
 	sp_Game->Run(hInstance);
	

}