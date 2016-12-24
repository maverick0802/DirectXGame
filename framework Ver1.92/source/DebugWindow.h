/////////////////////////////////////////
//
//	DebugWindow
//	(2015-08-31)
//	
//	�t�@�C�����FDebugWindow.h
//	�S���F���Y  ��
//
//--------------------------------------
//
//	printf���ŏo�͉\�ȃR���\�[���E�B���h�E���o���B
//	�f�o�b�O�r���h�̂ݗL���B
//
//--------------------------------------
//
//	2015-08-31	�쐬
//

//--	�C���N���[�h�K�[�h
#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#if !defined(_____DEBUGWINDOW_H_INCLUDED_____) || (_MSC_VER > 1000)
#define _____DEBUGWINDOW_H_INCLUDED_____

//--	���C�u�����ǉ�
#pragma comment(lib, "kernel32.lib")

//--	�C���N���[�h
#include<wincon.h>
#include<io.h>
#include <Fcntl.h>

namespace Debug{
	class DebugWindow{
	public:
		DebugWindow(){
			m_Init = false;
			m_ConsoleHr = 0;
		}

		~DebugWindow(){
			if( m_Init ){
				UnInit();
			}
		}

		void Init(){
	#if _DEBUG
			//--	�������t���O�����Ă�
			m_Init = true;

			//--	�R���\�[���E�B���h�E���o��
			if( ! AllocConsole() ){
				//--	���s��������t���O��܂��Ė߂�
				m_Init = false;
				return;
			}

			//--	�W���o�͐���������o�����E�B���h�E�ɕύX
			m_ConsoleHr = _open_osfhandle( (long)GetStdHandle( STD_OUTPUT_HANDLE ), _O_TEXT );
			//--	�o�̓��[�h
			*stdout = *_fdopen( m_ConsoleHr, "w" );
			//--	�o�b�t�@�𐶐�
			setvbuf( stdout, NULL, _IONBF, 0 );
	#endif
		}

		void UnInit(){
	#if _DEBUG
			//--	�R���\�[�������
			_close( m_ConsoleHr );
			//--	�������t���O��܂�
			m_Init = false;
	#endif
		}

	private:
		bool m_Init;		//�������t���O
		int m_ConsoleHr;	//�R���\�[���̃n���h��
	};
}
#endif //_____DEBUGWINDOW_H_INCLUDED_____