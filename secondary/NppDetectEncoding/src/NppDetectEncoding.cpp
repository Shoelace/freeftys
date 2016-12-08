/*
This file is:
The zlib/libpng License 
Copyright (c) 2012 freesftys<freesftys@gmail.com>

This software is provided 'as-is', without any express or implied warranty. 
In no event will the authors be held liable for any damages arising from 
the use of this software.

Permission is granted to anyone to use this software for any purpose, including 
commercial applications, and to alter it and redistribute it freely, subject to 
the following restrictions:

    1. The origin of this software must not be misrepresented; you must not 
	   claim that you wrote the original software. If you use this software in 
	   a product, an acknowledgment in the product documentation would be 
	   appreciated but is not required.
	
    2. Altered source versions must be plainly marked as such, and must not be 
       misrepresented as being the original software.
	
    3. This notice may not be removed or altered from any source distribution.

原文
http://opensource.org/licenses/Zlib

日本語訳
http://sourceforge.jp/projects/opensource/wiki/licenses%2Fzlib_libpng_license
*/

#include "NppDetectEncoding.h"

#include <map>
std::map<int, int> bufferEncode;

extern HINSTANCE g_DllhInst;
extern const TCHAR NPP_PLUGIN_NAME[];

extern NppData nppData;

bool encodeCheck;
bool openShortCut;
int g_CheckBufferSize;
bool eucjpEncoding;

TCHAR lastFullPath[FULLPATH];

TCHAR *langTypeStr[] = {
TEXT("Normaltext"),		TEXT("PHP"),		TEXT("C"),				TEXT("C++"),		TEXT("C#"),		
TEXT("Objective-C"),	TEXT("Java"),		TEXT("RC"),				TEXT("HTML"),		TEXT("XML"),		
TEXT("Makefile"),		TEXT("Pascal"),		TEXT("Batch"),			TEXT("ini"),		TEXT("NFO"),		
TEXT("udf"),			TEXT("ASP"),		TEXT("SQL"),			TEXT("VB"),			TEXT("Javascript"),		
TEXT("CSS"),			TEXT("Perl"),		TEXT("Python"),			TEXT("Lua"),		TEXT("TeX"),		
TEXT("Fortran"),		TEXT("Shell"),		TEXT("FlashAction"),	TEXT("NSIS"),		TEXT("TCL"),
TEXT("Lisp"),			TEXT("Scheme"),		TEXT("Assembly"),		TEXT("Diff"),		TEXT("Propertiesfile"),	
TEXT("Postscript"),		TEXT("Ruby"),		TEXT("Smalltalk"),		TEXT("VHDL"),		TEXT("KiXtart"),
TEXT("AutoIt"),			TEXT("CAML"),		TEXT("Ada"),			TEXT("Verilog"),	TEXT("MATLAB"),
TEXT("Haskell"),		TEXT("Inno"),		TEXT("InternalSearch"),	TEXT("CMAKEFILE"),	TEXT("YAML"),
TEXT("COBOL"),			TEXT("Gui4Cli"),	TEXT("D"),				TEXT("PowerShell"),	TEXT("R"),
TEXT("JSP"),			TEXT("External")
};
#define	LANG	sizeof(langTypeStr)/sizeof(langTypeStr[0])
TCHAR langStr[LANG][MAX_PATH];
//	static TCHAR *langStr[] = {
//TEXT(" txt "),					TEXT(" php php3 phtml "),	TEXT(" c "),			TEXT(" h hpp hxx cpp cxx cc "),			TEXT(" cs "),	
//TEXT("  "),						TEXT(" java "),				TEXT(" rc "),			TEXT(" html htm shtml shtm xhtml hta "),TEXT(" xml xsml xsl xsd kml wsdl "),				
//TEXT(" mak "),					TEXT(" pas inc "),			TEXT(" bat cmd nt "),	TEXT(" ini inf reg url "),				TEXT(" nfo "),						
//TEXT("  "),						TEXT(" asp "),				TEXT(" sql "),			TEXT(" vb vbs "),						TEXT(" js "),						
//TEXT(" css "),					TEXT(" pl pm plx "),		TEXT(" py pyw "),		TEXT(" lua "),							TEXT(" tex "),						
//TEXT(" f for f90 f95 f2k "),	TEXT(" sh bsh "),			TEXT(" as mx "),		TEXT(" nsi nsh "),						TEXT(" tcl "),						
//TEXT(" lsp lisp "),				TEXT(" scm smd ss "),		TEXT(" asm "),			TEXT(" diff patch "),					TEXT(" properties "),						
//TEXT(" ps "),					TEXT(" rb rbw "),			TEXT(" st "),			TEXT(" vhd vhdl "),						TEXT(" kix "),						
//TEXT(" au3 "),					TEXT(" ml mli sml thy "),	TEXT(" ada ads adb "),	TEXT(" v "),							TEXT(" m "),						
//TEXT(" hs lhs as las "),		TEXT(" iss "),				TEXT("  "),				TEXT(" cmake "),						TEXT(" yml "),						
//TEXT(" cbl cbd cdb cdc cob "),	TEXT("  "),					TEXT(" d "),			TEXT(" ps1 "),							TEXT(" r "),						
//TEXT(" jsp "),					TEXT(" ")
//	};

////NppMainProc
//HWND mainHwnd;//nppDataから取ればいいが念のため
//WNDPROC mainOldWndProc;
//LRESULT CALLBACK MainWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void onDetectEncodingBeNotified(SCNotification *notifyCode)
{
	switch(notifyCode->nmhdr.code)
	{
	//ファイルが開いたらファイルを読み込んでエンコード解析してセッションを使って開く
	case NPPN_FILEOPENED:
		onOpenFiled(&notifyCode->nmhdr);
		break;
	//ファイルクローズなので連想配列からBufferIDの削除
	case NPPN_FILECLOSED:
		Dprintf("ファイルのエンコード配列 個数 %d\n", (int)bufferEncode.size() );
		bufferEncode.erase(notifyCode->nmhdr.idFrom);
		Dprintf("クローズ後 ファイルのエンコード配列 個数 %d\n", (int)bufferEncode.size() );
		break;
	
	//ファイルの保存
	case NPPN_FILEBEFORESAVE:
		EucjpPreUnicode((HWND)notifyCode->nmhdr.hwndFrom, notifyCode->nmhdr.idFrom);
		break;

	//初期化(起動時にセッションの復元を行うとセッションの復元のほうが早いため正常に動かない可能性あり)
	case NPPN_READY:
		DetectEncodeSettingLoad();
		break;

	//表示中のファイルが変わったら連想配列からエンコードを取り出してステータスバーへ
	case NPPN_BUFFERACTIVATED:
		//Dprintf("BufferID %d\n", notifyCode->nmhdr.idFrom);
		StatusBarEncodeChange((HWND)notifyCode->nmhdr.hwndFrom, notifyCode->nmhdr.idFrom);
		break;

	//終了処理
	case NPPN_SHUTDOWN:
		//UnsetWndProc();
		DetectEncodeSettingSave();
		//ファイルのエンコード配列が空でなければ空に(念のため)
		bufferEncode.clear();
		break;
	}
	return;
}
/*
//void onDetectEncodingSetInfo(NppData *notpadPlusData)
//{
//	mainHwnd = notpadPlusData->_nppHandle;
//	SetWndProc();
//	return;
//}
//void SetWndProc()
//{
//	mainOldWndProc = (WNDPROC)SetWindowLongPtr(mainHwnd, GWLP_WNDPROC, (LONG_PTR)MainWndProc);
//	return;
//}
//void UnsetWndProc()
//{
//	SetWindowLongPtr(mainHwnd, GWLP_WNDPROC, (LONG_PTR)mainOldWndProc);
//	return;
//}
//LRESULT CALLBACK MainWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
//{
//	TCHAR fullPath[FULLPATH];
//	TCHAR lnkPath[FULLPATH];
//	int encoding=0;
//	switch(uMsg)
//	{
//		case NPPM_DOOPEN:
//		case WM_DOOPEN:
//		{
//
//			if( ResolveShortCut((TCHAR *)lParam, lnkPath, FULLPATH) == S_OK)
//			{
//				Dprintf("ショートカット処理\n");
//				_tcscpy_s(fullPath, (size_t)FULLPATH, lnkPath);
//			}
//			else
//			{
//				_tcscpy_s(fullPath, (size_t)FULLPATH, (TCHAR *)lParam);
//			}
//
//			//エンコードの判定
//			encoding = DetectEncode(fullPath);
//			Dprintf("エンコード %d\n", encoding);
//
//			//BufferID id = doOpen((const TCHAR *)lParam);
//			//if (id != BUFFER_INVALID)
//			//{
//			//	return switchToFile(id);
//			//}
//		}
//		break;
//	}
//	return CallWindowProc(mainOldWndProc, hwnd, uMsg, wParam, lParam);
//}
*/
int StatusBarEncodeChange(HWND Hwnd, int bufferID)
{
	int encoding = -1;
	
	std::map<int, int>::iterator it = bufferEncode.find(bufferID);
	if( it != bufferEncode.end() )
	{
		encoding = it->second;
		//エンコードの文字列の設定
		if( encoding == SJISCODE )
			SendMessage(Hwnd, NPPM_SETSTATUSBAR, (WPARAM)STATUSBAR_UNICODE_TYPE, (LPARAM)TEXT("Shift-JIS"));
		else
			SendMessage(Hwnd, NPPM_SETSTATUSBAR, (WPARAM)STATUSBAR_UNICODE_TYPE, (LPARAM)TEXT("EUC-JP"));
	}
	return encoding;
}
void OpenSjis()
{
	TCHAR fullPath[FULLPATH];
	SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, FULLPATH, (LPARAM)fullPath);
	//前回開いたファイルと同じ場合はセッションを作って開かない
	_tcscpy_s(lastFullPath, FULLPATH, fullPath );

	//現在の言語のタイプの取得 開き直すファイルをアクティブにして言語タイプを
	int langType = 0;
	SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)fullPath);
	SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&langType);

	FileClose(nppData._nppHandle, fullPath);
	SessionReopen(nppData._nppHandle, fullPath, SJISCODE, langType);
	return;
}
void OpenEucjp()
{
	TCHAR fullPath[FULLPATH];
	SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, FULLPATH, (LPARAM)fullPath);
	//前回開いたファイルと同じ場合はセッションを作って開かない
	_tcscpy_s(lastFullPath, FULLPATH, fullPath );

	//現在の言語のタイプの取得 開き直すファイルをアクティブにして言語タイプを
	int langType = 0;
	SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)fullPath);
	SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&langType);

	FileClose(nppData._nppHandle, fullPath);
	SessionReopen(nppData._nppHandle, fullPath, EUCJPCODE, langType);
	return;
}
void EucjpToSjis()
{
	if( MessageBox(NULL, L"元の状態に戻せなくなりますのでご注意ください", L"注意!!", MB_OKCANCEL) == IDOK)
	{
		TCHAR fullPath[FULLPATH];

		SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, 0);

		SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, FULLPATH, (LPARAM)fullPath);
		
		FILE *fp;
		char *eucjp;
		char *sjis;
		int sjisLen;

		if( _tfopen_s(&fp, fullPath, TEXT("r")) == 0)
		{
			int fsize;
			fsize = FileSize(fp);

			Dprintf("%s, readSize=%dバイト\n", fullPath, fsize);

			eucjp = (char*) new char[fsize];
			memset(eucjp, 0, sizeof(char)*fsize);
			fsize = fread(eucjp, sizeof(char), fsize, fp);
			//Dprintf("%s\n", buf);
			fclose(fp);
		}
		sjisLen = EucjpToSjis(eucjp, NULL, 0);
		sjis = (char*)new char[sjisLen];
		memset(sjis, 0, sizeof(char)*sjisLen);
		sjisLen = EucjpToSjis(eucjp, sjis, sjisLen);

		if( _tfopen_s(&fp, fullPath, TEXT("w")) == 0)
		{
			//終端文字分を削る
			fwrite(sjis, sizeof(char), sjisLen-1, fp);
			fclose(fp);
		}
		
		if(sjis != NULL) delete[] sjis;
		if(eucjp != NULL) delete[] eucjp;
			
		//前回開いたファイルと同じ場合はセッションを作って開かない
		_tcscpy_s(lastFullPath, FULLPATH, fullPath );

		//現在の言語のタイプの取得 開き直すファイルをアクティブにして言語タイプを
		int langType = 0;
		SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)fullPath);
		SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&langType);

		FileClose(nppData._nppHandle, fullPath);
		SessionReopen(nppData._nppHandle, fullPath, SJISCODE, langType);
	}
	return;
}
void SjisToEucjp()
{
	if( MessageBox(NULL, L"元の状態に戻せなくなりますのでご注意ください", L"注意!!", MB_OKCANCEL) == IDOK)
	{
		TCHAR fullPath[FULLPATH];

		SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, 0);

		SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, FULLPATH, (LPARAM)fullPath);
		
		FILE *fp;
		char *sjis;
		char *eucjp;
		int eucjpLen;

		if( _tfopen_s(&fp, fullPath, TEXT("r")) == 0)
		{
			int fsize;
			fsize = FileSize(fp);

			Dprintf("%s, readSize=%dバイト\n", fullPath, fsize);

			sjis = (char*) new char[fsize];
			memset(sjis, 0, sizeof(char)*fsize);
			fsize = fread(sjis, sizeof(char), fsize, fp);
			//Dprintf("%s\n", buf);
			fclose(fp);
		}
		eucjpLen = SjisToEucjp(sjis, NULL, 0);
		eucjp = (char*)new char[eucjpLen];
		memset(eucjp, 0, sizeof(char)*eucjpLen);
		eucjpLen = SjisToEucjp(sjis, eucjp, eucjpLen);

		if( _tfopen_s(&fp, fullPath, TEXT("w")) == 0)
		{
			//終端文字分を削る
			fwrite(eucjp, sizeof(char), eucjpLen-1, fp);
			fclose(fp);
		}
		
		if(eucjp != NULL) delete[] eucjp;
		if(sjis != NULL) delete[] sjis;

		//前回開いたファイルと同じ場合はセッションを作って開かない
		_tcscpy_s(lastFullPath, FULLPATH, fullPath );

		//現在の言語のタイプの取得 開き直すファイルをアクティブにして言語タイプを
		int langType = 0;
		SendMessage(nppData._nppHandle, NPPM_SWITCHTOFILE, 0, (LPARAM)fullPath);
		SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&langType);

		FileClose(nppData._nppHandle, fullPath);
		SessionReopen(nppData._nppHandle, fullPath, EUCJPCODE, langType);
	}
	return;
}

void EucjpPreUnicode(HWND Hwnd, int bufferID)
{
	Dprintf("ファイルの保存\n");
	//WideCharToMultiByteをunicode->cp20932(euc-jp)を行うといくつかの文字が失われるのを
	//事前にunicodeのコードを変えることによって防ぐ
	//全角チルダが壊れるなど
	//uni 0xFF5E utf8(0xEFBD9E) -> euc-jp A1C1に変換されない uni 0x301C utf8(0xE3809C)からならOK)
	if( eucjpEncoding != true && encodeCheck != true)
		return;
	
	int currentScintilla = -1;
	HWND scintillaHwnd;
	int textLen;
	char *text;
	int i, charByte;
	bool change = false;
	int encode;
	
	//カレントファイルの文字コードの取得
	std::map<int, int>::iterator it = bufferEncode.find(bufferID);
	if( it == bufferEncode.end() )
		return;
	encode = it->second;
	if( encode != 20932 )
		return;

	//保存するバッファをアクティブにしてデータを取得、変更し保存する
	SendMessage(Hwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		scintillaHwnd = nppData._scintillaMainHandle;
	else
		scintillaHwnd = nppData._scintillaSecondHandle;

	//バッファのファイル名の取得
	TCHAR fullPath[MAX_PATH*2];
	SendMessage(Hwnd, NPPM_GETFULLPATHFROMBUFFERID, bufferID, (LPARAM)fullPath);
	//取得したファイル名でアクティブにする
	SendMessage(Hwnd, NPPM_SWITCHTOFILE, 0, (LPARAM)fullPath);
	

	//現在のファイルの文字列の長さ取得
	textLen = SendMessage(scintillaHwnd, SCI_GETTEXT, 0, 0);
	Dprintf("text length = %d\n", textLen);
	//配列を作成して文字列をすべて取得
	text = new char[textLen];
	SendMessage(scintillaHwnd, SCI_GETTEXT, textLen, (LPARAM)text);

	//置き換えが必要な文字を検索置き換え
	for(i=0; i<textLen; ++i)
	{
		charByte = CharUtf8CodeByte((const char *)&text[i]);
		if(charByte != 3)
			i += charByte - 1;
		else
		{
			Dprintf("hit tilda %X %X %X\n", text[i], text[i+1], text[i+2]);
			//uni 0xFF5E utf8(0xEFBD9E) なら変換用に uni 0x301C utf8(0xE3809C)へ置き換え
			if( CompCharHex( (unsigned char*)&text[i], 0xEFBD9E) == 0)
			{
				text[i] = (char)0xE3;
				text[i+1] = (char)0x80;
				text[i+2] = (char)0x9C;

				change = true;
			}
			Dprintf("change tilda %X %X %X\n", text[i], text[i+1], text[i+2]);
		}
	}

	//置き換えた文字列をscintillaに適用
	if( change == true)
		SendMessage(scintillaHwnd, SCI_SETTEXT, 0, (LPARAM)text);

	delete[] text;
}
void DetectEncodeOption()
{
	DialogBox(g_DllhInst, MAKEINTRESOURCE(IDD_DIALOG_DETECTENCODING_OPTION), nppData._nppHandle, DetectEncodingOptionDlgProc);
}
BOOL CALLBACK DetectEncodingOptionDlgProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int maxDigit = 100;
	char buf[maxDigit];
	switch(uMsg)
	{
	case WM_INITDIALOG:
		if( encodeCheck == true )
			SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_DETECTENCODING), BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		if( openShortCut == true )
			SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_OPENSHORTCUT), BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		if( eucjpEncoding == true)
			SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_EUCJPENCODING), BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

		_itoa_s(g_CheckBufferSize, buf, maxDigit, 10);
		SetDlgItemTextA(hWndDlg, IDC_EDIT_CHECKBUFFERSIZE, buf);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			//エンコードの自動判定
			if( SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_DETECTENCODING), BM_GETCHECK, 0, 0) ==	BST_CHECKED )
				encodeCheck = true;
			else
				encodeCheck = false;

			//ショートカット先を開く
			if( SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_OPENSHORTCUT), BM_GETCHECK, 0, 0) ==	BST_CHECKED )
				openShortCut = true;
			else
				openShortCut = false;

			//euc-jp保存時にunicodeを自動で編集する
			if( SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_EUCJPENCODING), BM_GETCHECK, 0, 0) ==	BST_CHECKED )
				eucjpEncoding = true;
			else
				eucjpEncoding = false;

			GetDlgItemTextA(hWndDlg, IDC_EDIT_CHECKBUFFERSIZE, buf, maxDigit);
			g_CheckBufferSize = atoi(buf);
			EndDialog(hWndDlg, 1);
			return TRUE;

		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWndDlg, 0);
		return TRUE;
	}
	return FALSE;
}
int FileSize(const TCHAR *fullPath)
{
	HANDLE	hFile;
	DWORD	lowFileSize;
	DWORD	hiFileSize;
	hFile = CreateFile(fullPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		MessageBox(NULL, L"reade error", L"error", MB_OK);
		return -1;
	}
	lowFileSize = GetFileSize(hFile, &hiFileSize);
	if( lowFileSize == -1)
	{
		MessageBox(NULL, L"getsize error", L"error", MB_OK);
		return -1;
	}
	CloseHandle(hFile);

	return (int)lowFileSize;
}

void onOpenFiled(Sci_NotifyHeader *nmhdr)
{	
	if( openShortCut != true && encodeCheck != true)
		return;

	//セッションを保存→セッションのエンコード部変更→セッション読み込み
	int encoding = -1;
	bool fShortCut = false;
	TCHAR fullPath[FULLPATH] = L"" ;
	TCHAR lnkPath[FULLPATH] = L"";

	//int currentScintilla;
	//HWND scintillaHwnd;
	//encoding = SendMessage((HWND)notifyCode->nmhdr.hwndFrom, NPPM_GETBUFFERENCODING, notifyCode->nmhdr.idFrom, 0);
	//Dprintf("encode %d\n" , encoding);

	//現在のファイルのフルパスを取得
	SendMessage((HWND)nmhdr->hwndFrom, NPPM_GETFULLPATHFROMBUFFERID, nmhdr->idFrom, (LPARAM)fullPath);
	Dprintf("fullPath %s\n", fullPath);

	//現在の言語のタイプの取得 開き直すファイルをアクティブにして言語タイプを
	int langType = 0;
	langType = SendMessage((HWND)nmhdr->hwndFrom, NPPM_GETBUFFERLANGTYPE, nmhdr->idFrom, 0);
	Dprintf("langType %d\n", langType);
	
	if( openShortCut == true )
	{
		TCHAR *extension;
		int result;
		extension = _tcsrchr(fullPath, '.');
		if( extension != NULL)
		{
			result = _tcscmp(TEXT(".lnk"), extension);
			if( extension != NULL && result == 0)
			{
				if( ResolveShortCut(fullPath, lnkPath, FULLPATH) == S_OK)
				{
					Dprintf("ショートカット処理\n");
					//_tcscpy_s(fullPath, (size_t)FULLPATH, lnkPath);
					extension = _tcsrchr(lnkPath, '.');
					if( extension != NULL)
					{
						Dprintf("拡張子 : %s\n", extension);
						langType = ExtensionToLang(extension);
						Dprintf("LangType : %d\n", langType);
					}

					fShortCut = true;
				}
			}
		}
	}

	if( encodeCheck == true )
	{

		//エンコードの判定
		if( fShortCut == true )
		{
			//前回開いたファイルと同じ場合はセッションを作って開かない
			if( _tcscmp(lastFullPath, lnkPath) == 0)
			{
				_tcscpy_s(lastFullPath, FULLPATH, TEXT("") );	
				return;
			}
			//今回開いたパスを保存
			_tcscpy_s(lastFullPath, FULLPATH, lnkPath);

			encoding = DetectEncode(lnkPath);
		}
		else
		{
			//前回開いたファイルと同じ場合はセッションを作って開かない
			if( _tcscmp(lastFullPath, fullPath) == 0)
			{
				_tcscpy_s(lastFullPath, FULLPATH, TEXT("") );	
				return;
			}

			//今回開いたパスを保存
			_tcscpy_s(lastFullPath, FULLPATH, fullPath);
			
			encoding = DetectEncode(fullPath);
		}
	}
	

	if( encoding != -1)
	{
		//一度閉じてエンコード指定でセッションを開きなおす
		FileClose((HWND)nmhdr->hwndFrom, fullPath);

		//セッションで再オープン
		if( fShortCut == true )
			SessionReopen((HWND)nmhdr->hwndFrom, lnkPath, encoding, langType);
		else
			SessionReopen((HWND)nmhdr->hwndFrom, fullPath, encoding, langType);
	}
	else if( fShortCut == true )
	{
		FileClose((HWND)nmhdr->hwndFrom, fullPath);

		//ショートカット先を開く
		SendMessage((HWND)nmhdr->hwndFrom, NPPM_DOOPEN, 0, (LPARAM)lnkPath);
	}

	return;
}
void FileClose(HWND nppHwnd, const TCHAR *fileName)
{
	//開いたファイルをアクティブへ
	SendMessage(nppHwnd, NPPM_SWITCHTOFILE, 0, (LPARAM)fileName);		
	//アクティブファイルを閉じる
	SendMessage(nppHwnd, NPPM_MENUCOMMAND, 0, (LPARAM)IDM_FILE_CLOSE);

	return;
}
void SessionReopen(HWND Hwnd, const TCHAR *fileName, int encoding, int langType)
{
	//セッションファイルの作成
	TCHAR sessionFileName[FULLPATH];
	SendMessage(Hwnd, NPPM_GETPLUGINSCONFIGDIR, FULLPATH, (LPARAM)sessionFileName);
	_tcscat_s(sessionFileName, FULLPATH, TEXT("\\tmp.xml") );

	int fileNameLen = _tcsclen(fileName)*5;
	TCHAR *escapeFileName = (TCHAR*)new TCHAR[fileNameLen];
	//セッションファイル用にファイル名をhtmlエスケープ
	XmlEscape(fileName, escapeFileName, fileNameLen);
	//セッションファイルの作成
	WriteSession(sessionFileName, escapeFileName, encoding, langType);
	delete[] escapeFileName;
	
	//セッションを開く
	SendMessage(Hwnd, NPPM_LOADSESSION, 0, (LPARAM)sessionFileName);
	
	//開いたファイルをアクティブへ
	SendMessage(Hwnd, NPPM_SWITCHTOFILE, 0, (LPARAM)fileName);

	//バッファIDの取得
	int bufferID;
	bufferID = SendMessage(Hwnd, NPPM_GETCURRENTBUFFERID, 0, 0);
	Dprintf("OpenFile BufferID %d, Encode %d\n", bufferID, encoding);
	bufferEncode.insert( std::map<int, int>::value_type(bufferID, encoding) );

	StatusBarEncodeChange(Hwnd, bufferID);

	return;
}
void XmlEscape(const TCHAR *fileName, TCHAR *escapeFileName, int escapeLen)
{
	const int digit=5;
	TCHAR code[digit];
	int bufferPos=0;
	ZeroMemory(escapeFileName, sizeof(TCHAR)*escapeLen);
	for(int i=0; i<escapeLen; i++)
	{
		if( fileName[i] == 0 )
			break;

		if( fileName[i] >= 0x80)
		{
			_itot_s((int)fileName[i], code, digit, 16);
			_tcscat_s(escapeFileName, escapeLen, TEXT("&#x"));
			_tcscat_s(escapeFileName, escapeLen, code);
			_tcscat_s(escapeFileName, escapeLen, TEXT(";"));
			bufferPos += 8;
		}
		else
		{
			escapeFileName[bufferPos] = (TCHAR)fileName[i];
			bufferPos++;
			escapeFileName[bufferPos] = 0;
		}
	}
	return;
}
void WriteSession(const TCHAR *sessionFilName, const TCHAR *fileName, int encode, int langType)
{
	FILE *fp;
	if( _tfopen_s(&fp, sessionFilName, TEXT("w+")) == 0)
	{
		_ftprintf_s(fp, 
TEXT("<NotepadPlus>\n \
<Session activeView=\"0\">\n \
	<mainView activeIndex=\"0\">\n \
		<File firstVisibleLine=\"0\" xOffset=\"0\" scrollWidth=\"1\" startPos=\"0\" endPos=\"0\" selMode=\"0\" lang=\"%s\" encoding=\"%d\" filename=\"%s\" />\n \
	</mainView>\n \
	<subView activeIndex=\"0\" />\n \
</Session>\n \
</NotepadPlus>")
		,
		langTypeStr[langType], encode, fileName);
		fclose(fp);
	}
}
int DetectEncode(const TCHAR *loadFile)
{
	//const int blockSize = 500;	//128 kB
	//char data[blockSize+8]={""};
	int encoding = -1;
	
	FILE *fp;
	if( _tfopen_s(&fp, loadFile, TEXT("rb")) == 0)
	{
		int blockSize = g_CheckBufferSize;
		char *data;
		int lenFile;
		if( blockSize <= 0 )
			blockSize = FileSize(fp);

		data = new char[blockSize+8];

		lenFile = fread(data, 1, blockSize+8, fp);
		if( lenFile > blockSize)
			lenFile = blockSize;
		fclose(fp);
	
		encoding = EncodeDetect(data, lenFile);
		//int i=0;
		//int utfCount=0;//0xE2～0xEFの出現数のカウントをする
		//int code=0;// 1-sjis 2-euc 3-utf8 4-utf16BE 5-utf16LE
		//unsigned char *detectEncode = (unsigned char*)data;
		////BOMか確認 utf8(EF BB BF) utf16BE(FE FF) utf16LE(FF FE)
		//if( detectEncode[0]==0xEF && detectEncode[1]==0xBB && detectEncode[2]==0xBF )
		//	code=3;
		//else if( detectEncode[0]==0xFE && detectEncode[1]==0xFF )
		//	code=4;
		//else if( detectEncode[0]==0xFF && detectEncode[1]==0xFE )
		//	code=5;			
		//if(code == 0)
		//{
		//	//最低100文字でコードの判定を行う 0はEOFのため即時終了
		//	while( (detectEncode[i] != 0) && (i<lenFile)) {
		//		//0x80以下の場合はasciiコードですべてのコードで一緒なのでキャンセル
		//		if( detectEncode[i] > 0x80)	{
		//			//utf8 日本語環境のため主に3バイトコードにて判定
		//			//2バイト以降に0x80以下と0xC0以上が出てきたらsjis それ以外はsjisとutf8両方ありえるのでスキップ
		//			if( (detectEncode[i]>=0xE0) && (detectEncode[i]<=0xEF) ){
		//				code = 1;
		//				if( (detectEncode[i+1] <= 0x7F) || (detectEncode[i+2] <= 0x7F) || 
		//					(detectEncode[i+1] >= 0xC0) || (detectEncode[i+2] >= 0xC0) ) {
		//					break;
		//				}
		//				i+=2;
		//				utfCount++;
		//			} else if( (detectEncode[i]>=0x81 && detectEncode[i]<=0x9f) || (detectEncode[i]>=0xe0 && detectEncode[i]<=0xfc)) {
		//				if( (detectEncode[i+1]>=0x40 && detectEncode[i+1]<=0x7e) ||	(detectEncode[i+1]>=0x80 && detectEncode[i+1]<=0xfc))
		//				{
		//					code=1;
		//					if( (detectEncode[i] >= 0xE3) && (detectEncode[i] <= 0xEF) )
		//						utfCount++;
		//				}
		//				i++;
		//			} else {
		//				//euc-jpの場合2文字連続で計測->4byte連続でa1～feはsjis,utf8ともかなり確率的に低い
		//				if( detectEncode[i]>=0xa1 && detectEncode[i]<=0xfe){
		//					if( detectEncode[i+1]>=0xa1 && detectEncode[i+1]<=0xfe){
		//						if( detectEncode[i+2]>=0xa1 && detectEncode[i+2]<=0xfe){
		//							if( detectEncode[i+3]>=0xa1 && detectEncode[i+3]<=0xfe){
		//								code=2;
		//								break;
		//							}
		//						}
		//					}								
		//				}
		//			}
		//		}
		//		i++;
		//	}
		//	if( (code==1) && (utfCount>10) && (i>=lenFile) )
		//		code=4;

		//	if(code < 3) {
		//		//_pscratchTilla->execute(SCI_SETCODEPAGE, SC_CP_UTF8);
		//		switch(code) {
		//			case 1:
		//				encoding = 932;
		//				break;
		//			case 2:
		//				encoding = 20932;
		//				break;
		//			default:
		//				break;
		//		}
		//	}
		//}
		//sjisとeuc-jp以外はnotepad++に処理させる

		delete[] data;

		switch(encoding)
		{
		case SJIS:
			encoding = SJISCODE;
			break;
		case EUCJP:
			encoding = EUCJPCODE;
			break;
		default:
			encoding = -1;
			break;
		}

	}

	return encoding;
	/*		
	//追加編集
	//const int blockSize = 128 * 1024;	//128 kB
	const int blockSize = 500;	//128 kB
	char data[blockSize+8]={""};
	int lenFile;
	
	FILE *fp = generic_fopen(longFileName, TEXT("rb"));
	if (fp) {
		lenFile = fread(data, 1, blockSize+8, fp);
		if( lenFile > blockSize)
			lenFile = blockSize;
		fclose(fp);

		int i=0;
		int utfCount=0;//0xE2～0xEFの出現数のカウントをする
		int code=0;// 1-sjis 2-euc 3-utf8 4-utf16BE 5-utf16LE
		unsigned char *detectEncode = (unsigned char*)data;
		//BOMか確認 utf8(EF BB BF) utf16BE(FE FF) utf16LE(FF FE)
		if( detectEncode[0]==0xEF && detectEncode[1]==0xBB && detectEncode[2]==0xBF )
			code=3;
		else if( detectEncode[0]==0xFE && detectEncode[1]==0xFF )
			code=4;
		else if( detectEncode[0]==0xFF && detectEncode[1]==0xFE )
			code=5;			
		if(code == 0)
		{
			//最低100文字でコードの・ｻ定を行う 0はEOFのため即時終了
			while( (detectEncode[i] != 0) && (i<lenFile)) {
				//0x80以下の場合はasciiコードですべてのコードで一緒なのでキャンセル
				if( detectEncode[i] > 0x80)	{
					//utf8 日本語環境のため主に3バイトコードにて判定
					//2バイト以降に0x80以下と0xC0以上が出てきたらsjis それ以外はsjisとutf8両方ありえるのでスキップ
					if( (detectEncode[i]>=0xE0) && (detectEncode[i]<=0xEF) ){
						code = 1;
						if( (detectEncode[i+1] <= 0x7F) || (detectEncode[i+2] <= 0x7F) || 
							(detectEncode[i+1] >= 0xC0) || (detectEncode[i+2] >= 0xC0) ) {
							break;
						}
						i+=2;
						utfCount++;
					} else if( (detectEncode[i]>=0x81 && detectEncode[i]<=0x9f) || (detectEncode[i]>=0xe0 && detectEncode[i]<=0xfc)) {
						if( (detectEncode[i+1]>=0x40 && detectEncode[i+1]<=0x7e) ||	(detectEncode[i+1]>=0x80 && detectEncode[i+1]<=0xfc))
						{
							code=1;
							if( (detectEncode[i] >= 0xE3) && (detectEncode[i] <= 0xEF) )
								utfCount++;
						}
						i++;
					} else {
						//euc-jpの場合2文字連続で計測->4byte連続でa1～feはsjis,utf8ともかなり確率的に低い
						if( detectEncode[i]>=0xa1 && detectEncode[i]<=0xfe){
							if( detectEncode[i+1]>=0xa1 && detectEncode[i+1]<=0xfe){
								if( detectEncode[i+2]>=0xa1 && detectEncode[i+2]<=0xfe){
									if( detectEncode[i+3]>=0xa1 && detectEncode[i+3]<=0xfe){
										code=2;
										break;
									}
								}
							}								
						}
					}
				}
				i++;
			}
			if( (code==1) && (utfCount>10) && (i>=lenFile) )
				code=4;

			if(code < 3) {
				//_pscratchTilla->execute(SCI_SETCODEPAGE, SC_CP_UTF8);
				switch(code) {
					case 1:
						encoding = 932;
						break;
					case 2:
						encoding = 20932;
						break;
					default:
						break;
				}
			}
		}
	}
	//終了
	*/
}

void DetectEncodeSettingSave()
{
	int nBuf;
	int i;

	if( encodeCheck == true)
		nBuf=1;
	else
		nBuf=0;
	Ini::getInstance()->writeDate(TEXT("JpDetectEncode"), TEXT("EncodeCheck"), nBuf);

	nBuf = (openShortCut == true)? 1 : 0;
	Ini::getInstance()->writeDate(TEXT("JpDetectEncode"), TEXT("OpenShortCut"), nBuf);

	for( i=0; i<LANG; i++)
	{
		Ini::getInstance()->writeDate(TEXT("JpDetectEncode"), langTypeStr[i], (const TCHAR*)langStr[i]);
	}
	
	Ini::getInstance()->writeDate(TEXT("JpDetectEncode"), TEXT("CheckBufferSize"), g_CheckBufferSize);

	
	nBuf = (eucjpEncoding == true)? 1 : 0;
	Ini::getInstance()->writeDate(TEXT("JpDetectEncode"), TEXT("EucjpEncoding"), nBuf);
	return;
}
void DetectEncodeSettingLoad()
{
	TCHAR configDir[MAX_PATH];
	TCHAR buf[MAX_PATH];
	int nBuf;

	//iniの読み込み
	SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)configDir);
	Ini::getInstance()->setIniPath(configDir);

	//iniがない場合
	if( Ini::getInstance()->checkIniFile() == 0 )
	{
		encodeCheck = true;
		openShortCut = true;
		InitLangStr();
		g_CheckBufferSize = 500;
		eucjpEncoding = true;
	}
	else
	{
		int i;
		Ini::getInstance()->readDate(TEXT("JpDetectEncode"), TEXT("EncodeCheck"), buf, MAX_PATH);
		nBuf = _ttoi(buf);
		if( nBuf != 0)
			encodeCheck = true;
		else
			encodeCheck = false;

		Ini::getInstance()->readDate(TEXT("JpDetectEncode"), TEXT("OpenShortCut"), buf, MAX_PATH);
		nBuf = _ttoi(buf);
		if( nBuf != 0)
			openShortCut = true;
		else
			openShortCut = false;

		for( i=0; i<LANG; i++)
		{
			Ini::getInstance()->readDate(TEXT("JpDetectEncode"), langTypeStr[i], langStr[i], MAX_PATH);
		}

		Ini::getInstance()->readDate(TEXT("JpDetectEncode"), TEXT("CheckBufferSize"), &g_CheckBufferSize);

		Ini::getInstance()->readDate(TEXT("JpDetectEncode"), TEXT("EucjpEncoding"), buf, MAX_PATH);
		nBuf = _ttoi(buf);
		eucjpEncoding = (nBuf != 0) ? true : false;
	}

	return;
}

int ExtensionToLang(TCHAR *extension)
{	
	//スペース区切りの拡張子の作成用のため 10文字以上の拡張子があったら流す
	const int extensionSize = 10;
	TCHAR lookExtension[extensionSize] = TEXT("");
	int i;
	int langType;
	TCHAR *find;

	_tcscat_s(lookExtension, sizeof(lookExtension)/sizeof(lookExtension[0]), extension);
	_tcscat_s(lookExtension, sizeof(lookExtension)/sizeof(lookExtension[0]), TEXT("."));
	_tcslwr_s(lookExtension, extensionSize);
	langType = 0;
	for(i=0; i<LANG; i++)
	{
		find = (TCHAR*)_tcsstr( (const TCHAR*)langStr[i], (const TCHAR*)lookExtension);
		if( find != NULL )
		{
			langType = i;
			break;
		}
	}
	return langType;
}

void InitLangStr()
{
	TCHAR *initLangStr[] = {
//TEXT("\" txt \""),					TEXT("\" php php3 phtml \""),	TEXT("\" c \""),			TEXT("\" h hpp hxx cpp cxx cc \""),			TEXT("\" cs \""),	
//TEXT("\"  \""),						TEXT("\" java \""),				TEXT("\" rc \""),			TEXT("\" html htm shtml shtm xhtml hta \""),TEXT("\" xml xsml xsl xsd kml wsdl \""),				
//TEXT("\" mak \""),					TEXT("\" pas inc \""),			TEXT("\" bat cmd nt \""),	TEXT("\" ini inf reg url \""),				TEXT("\" nfo \""),						
//TEXT("\"  \""),						TEXT("\" asp \""),				TEXT("\" sql \""),			TEXT("\" vb vbs \""),						TEXT("\" js \""),						
//TEXT("\" css \""),					TEXT("\" pl pm plx \""),		TEXT("\" py pyw \""),		TEXT("\" lua \""),							TEXT("\" tex \""),						
//TEXT("\" f for f90 f95 f2k \""),	TEXT("\" sh bsh \""),			TEXT("\" as mx \""),		TEXT("\" nsi nsh \""),						TEXT("\" tcl \""),						
//TEXT("\" lsp lisp \""),				TEXT("\" scm smd ss \""),		TEXT("\" asm \""),			TEXT("\" diff patch \""),					TEXT("\" properties \""),						
//TEXT("\" ps \""),					TEXT("\" rb rbw \""),			TEXT("\" st \""),			TEXT("\" vhd vhdl \""),						TEXT("\" kix \""),						
//TEXT("\" au3 \""),					TEXT("\" ml mli sml thy \""),	TEXT("\" ada ads adb \""),	TEXT("\" v \""),							TEXT("\" m \""),						
//TEXT("\" hs lhs as las \""),		TEXT("\" iss \""),				TEXT("\"  \""),				TEXT("\" cmake \""),						TEXT("\" yml \""),						
//TEXT("\" cbl cbd cdb cdc cob \""),	TEXT("\"  \""),					TEXT("\" d \""),			TEXT("\" ps1 \""),							TEXT("\" r \""),						
//TEXT("\" jsp \""),					TEXT("\" \"")
TEXT(".txt."),					TEXT(".php.php3.phtml."),	TEXT(".c."),			TEXT(".h.hpp.hxx.cpp.cxx.cc."),			TEXT(".cs."),	
TEXT(".."),						TEXT(".java."),				TEXT(".rc."),			TEXT(".html.htm.shtml.shtm.xhtml.hta."),TEXT(".xml.xsml.xsl.xsd.kml.wsdl."),				
TEXT(".mak."),					TEXT(".pas.inc."),			TEXT(".bat.cmd.nt."),	TEXT(".ini.inf.reg.url."),				TEXT(".nfo."),						
TEXT(".."),						TEXT(".asp."),				TEXT(".sql."),			TEXT(".vb.vbs."),						TEXT(".js."),						
TEXT(".css."),					TEXT(".pl.pm.plx."),		TEXT(".py.pyw."),		TEXT(".lua."),							TEXT(".tex."),						
TEXT(".f.for.f90.f95.f2k."),	TEXT(".sh.bsh."),			TEXT(".as.mx."),		TEXT(".nsi.nsh."),						TEXT(".tcl."),						
TEXT(".lsp.lisp."),				TEXT(".scm.smd.ss."),		TEXT(".asm."),			TEXT(".diff.patch."),					TEXT(".properties."),						
TEXT(".ps."),					TEXT(".rb.rbw."),			TEXT(".st."),			TEXT(".vhd.vhdl."),						TEXT(".kix."),						
TEXT(".au3."),					TEXT(".ml.mli.sml.thy."),	TEXT(".ada.ads.adb."),	TEXT(".v."),							TEXT(".m."),						
TEXT(".hs.lhs.as.las."),		TEXT(".iss."),				TEXT(".."),				TEXT(".cmake."),						TEXT(".yml."),						
TEXT(".cbl.cbd.cdb.cdc.cob."),	TEXT(".."),					TEXT(".d."),			TEXT(".ps1."),							TEXT(".r."),						
TEXT(".jsp."),					TEXT("..")
	};

	int i;

	for( i=0; i<LANG; i++)
	{
		_tcscpy_s(langStr[i], MAX_PATH, initLangStr[i]);
	}
	return;
}