/////////////////////////////////////////
//
//	DebugWindow
//	(2015-08-31)
//	
//	ファイル名：DebugWindow.h
//	担当：杉浦  亨
//
//--------------------------------------
//
//	printf等で出力可能なコンソールウィンドウを出す。
//	デバッグビルドのみ有効。
//
//--------------------------------------
//
//	2015-08-31	作成
//

//--	インクルードガード
#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#if !defined(_____DEBUGWINDOW_H_INCLUDED_____) || (_MSC_VER > 1000)
#define _____DEBUGWINDOW_H_INCLUDED_____

//--	ライブラリ追加
#pragma comment(lib, "kernel32.lib")

//--	インクルード
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
			//--	初期化フラグを建てる
			m_Init = true;

			//--	コンソールウィンドウを出す
			if( ! AllocConsole() ){
				//--	失敗だったらフラグを折って戻る
				m_Init = false;
				return;
			}

			//--	標準出力先をさっき出したウィンドウに変更
			m_ConsoleHr = _open_osfhandle( (long)GetStdHandle( STD_OUTPUT_HANDLE ), _O_TEXT );
			//--	出力モード
			*stdout = *_fdopen( m_ConsoleHr, "w" );
			//--	バッファを生成
			setvbuf( stdout, NULL, _IONBF, 0 );
	#endif
		}

		void UnInit(){
	#if _DEBUG
			//--	コンソールを閉じる
			_close( m_ConsoleHr );
			//--	初期化フラグを折る
			m_Init = false;
	#endif
		}

	private:
		bool m_Init;		//初期化フラグ
		int m_ConsoleHr;	//コンソールのハンドル
	};
}
#endif //_____DEBUGWINDOW_H_INCLUDED_____