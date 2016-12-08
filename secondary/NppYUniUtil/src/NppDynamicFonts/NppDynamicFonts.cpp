/*
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

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <string>

#include "MyEtc.h"

#include "NppDynamicFonts.h"

extern HINSTANCE g_DllhInst;
extern NppData nppData;

int g_nppFontSize;
std::string g_nppFontName;
std::vector<std::wstring> g_fonts;
int g_nppFontEnable;

void onDynamicFontsBeNotified(SCNotification *notifyCode)
{
	switch(notifyCode->nmhdr.code)
	{
	case NPPN_BUFFERACTIVATED:
	case NPPN_LANGCHANGED:
	case NPPN_WORDSTYLESUPDATED:
		SetStyleFontData();
		return;
	case NPPN_READY:
		LoadFonts(1);
		DynamicFontsSettingLoad();
		SetStyleFontData();
		return;
	case NPPN_SHUTDOWN:
		DynamicFontsSettingSave();
		LoadFonts(0);
		return;
	}
	return;
}
int LoadFonts(int add)
{
	#define FONTPATH L"./plugins/fonts/"
	#define FINDPATH L"./plugins/fonts/*.ttf"
	//TCHAR modulePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	int nAddFont=0;
	
	//GetModuleFileName(NULL, modulePath, MAX_PATH);
	//Dprintf("path %s\n", modulePath);

	hFind = FindFirstFile(FINDPATH, &FindFileData);
	if(hFind != INVALID_HANDLE_VALUE )
	{
			do
			{
				wchar_t *pwFontFile=0;
				int len=0;

				len += (int)wcslen(FONTPATH);
				len += (int)wcslen(FindFileData.cFileName);
				len++;

				pwFontFile = (wchar_t*)malloc(len*sizeof(wchar_t));
				memset(pwFontFile, 0, len*sizeof(wchar_t));

				wcscpy_s(pwFontFile, len, FONTPATH);
				wcscat_s(pwFontFile, len, FindFileData.cFileName);
				
				if( add == 1)
					nAddFont = AddFontResourceEx(pwFontFile, FR_PRIVATE, NULL);
				else
				{
					BOOL result;
					result = RemoveFontResourceEx(pwFontFile, FR_PRIVATE, NULL);
					Dprintf("%s %d\n", pwFontFile, result);
				}

				//Dprintf("%s%s\n",FONTPATH, FindFileData.cFileName);
				Dprintf("%s\n",pwFontFile);

				free(pwFontFile);
			}
			while(FindNextFile(hFind, &FindFileData));

			FindClose(hFind);
	}else{
		Dprintf("notfile");
	}
	///終了
	return 1;
}

void DynamicFontsSettingSave()
{
	if( !g_nppFontName.empty() )
	{
		TCHAR fontName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, NULL, g_nppFontName.c_str(), -1, fontName, MAX_PATH);
		Ini::getInstance()->writeDate(TEXT("DynamicFonts"), TEXT("fontName"), (const TCHAR*)fontName);
		Ini::getInstance()->writeDate(TEXT("DynamicFonts"), TEXT("fontSize"), g_nppFontSize);
		Ini::getInstance()->writeDate(TEXT("DynamicFonts"), TEXT("fontEnable"), g_nppFontEnable);
	}

	return;
}
void DynamicFontsSettingLoad()
{
	//iniの読み込み
	TCHAR configDir[MAX_PATH];
	SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)configDir);
	Ini::getInstance()->setIniPath(configDir);

	if( Ini::getInstance()->checkIniFile() )
	{
		//ある
		TCHAR fontName[MAX_PATH];
		char *fontNameA;
		Ini::getInstance()->readDate(TEXT("DynamicFonts"), TEXT("fontName"), fontName, MAX_PATH);
		Ini::getInstance()->readDate(TEXT("DynamicFonts"), TEXT("fontSize"), &g_nppFontSize);
		WtoC(fontName, -1, &fontNameA);
		g_nppFontName = fontNameA;
		delete[] fontNameA;
		Ini::getInstance()->readDate(TEXT("DynamicFonts"), TEXT("fontEnable"), &g_nppFontEnable);
	}
	else
	{
		g_nppFontEnable = 0;
		//char fontName[MAX_PATH];
		////初期化
		//SendMessage(nppData._scintillaMainHandle, SCI_STYLEGETFONT, STYLE_DEFAULT, (LPARAM)fontName);
		//g_nppFontName = fontName;
		//g_nppFontSize = (int)SendMessage(nppData._scintillaMainHandle, SCI_STYLEGETSIZE, STYLE_DEFAULT, 0);
	}
	return;
}
void SelectFont()
{
	char fontName[MAX_PATH];
	//wchar_t *wstr;
	INT_PTR result;


	g_nppFontSize = (int)SendMessage(nppData._scintillaMainHandle, SCI_STYLEGETSIZE, STYLE_DEFAULT, 0);
	Dprintf("fontsize %d\n", g_nppFontSize);

	if( g_nppFontName.empty() )
	{
		SendMessage(nppData._scintillaMainHandle, SCI_STYLEGETFONT, STYLE_DEFAULT, (LPARAM)fontName);
		//CtoW(fontName, -1, &wstr);
		//g_nppFontName = wstr;
		//delete[] wstr;
		g_nppFontName = fontName;
	}
	Dprintf("fontName %s\n", g_nppFontName.c_str());

	result = DialogBox(g_DllhInst, MAKEINTRESOURCE(IDD_DIALOG_DYNAMICFONTS_OPTION), nppData._nppHandle, DynamicFontsOptionDlgProc);
	if( result == 1)
	{	
		//char *cstr;	
		//WtoC((wchar_t*)g_nppFontName.c_str(), -1, &cstr);STYLE_DEFAULT
		//WideCharToMultiByte(CP_ACP, NULL, g_nppFontName.c_str(), -1, fontName, MAX_PATH, NULL, NULL);
		SetStyleFontData();
	}
	return ;
}
void SetStyleFontData()
{
	if( (g_nppFontEnable == 1) && ( !g_nppFontName.empty() ) )
	{
		//int styleBit = SendMessage(nppData._scintillaMainHandle, SCI_GETSTYLEBITS, 0, 0);
		//Dprintf("bits 0x%x", styleBit);
		//STYLE_MAX idごとにフォントなどを設定できる、そして文字ごとにidを個別に適用できる 本来はSTYLE_MAXまでできるが
		//5bitまで使用っぽいので127にする先頭～stylebitまではインジケータのスタイル定義に使用なので2ビット以降256まで
		int styleEnd = 127;
		for(int i=0; i<styleEnd; ++i)
		{
			SendMessage(nppData._scintillaMainHandle, SCI_STYLESETSIZE, i, g_nppFontSize);
			SendMessage(nppData._scintillaSecondHandle, SCI_STYLESETSIZE, i, g_nppFontSize);
		
			SendMessage(nppData._scintillaMainHandle, SCI_STYLESETFONT, i, (LPARAM)(char*)g_nppFontName.c_str());
			SendMessage(nppData._scintillaSecondHandle, SCI_STYLESETFONT, i, (LPARAM)(char*)g_nppFontName.c_str());
		}	
	}
}
BOOL CALLBACK DynamicFontsOptionDlgProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		InitDlg(hWndDlg);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			OkDlg(hWndDlg);
			EndDialog(hWndDlg, 1);
			break;
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
bool InitDlg(HWND hWndDlg)
{
	HWND comboHwnd;
	LOGFONT logfont;
	HDC hDC;
	TCHAR fontName[MAX_PATH];
	TCHAR tsSize[5];
	int index;

	if( g_fonts.empty() )
	{
		logfont.lfCharSet = DEFAULT_CHARSET;
		logfont.lfFaceName[0] = L'\0';
		logfont.lfPitchAndFamily = 0;
		hDC = GetDC(hWndDlg);
			EnumFontFamiliesEx(hDC, &logfont, (FONTENUMPROC)EnumeFontsExProc, 0, 0);
		ReleaseDC(hWndDlg, hDC);
	}

	comboHwnd = GetDlgItem(hWndDlg, IDC_COMBO_DYNAMICFONT_SELECT);
	MultiByteToWideChar(CP_ACP, NULL, g_nppFontName.c_str(), -1, fontName, MAX_PATH);
	for(std::vector<std::wstring>::iterator it = g_fonts.begin(); it != g_fonts.end(); ++it)
	{
		index = SendMessage(comboHwnd, CB_ADDSTRING, 0, (LPARAM)it->c_str());
		if( *it == fontName )
			SendMessage(comboHwnd, CB_SETCURSEL, index, 0);

	}
	//index = SendMessage(comboHwnd, CB_FINDSTRING, 0, (LPARAM)g_nppFontName.c_str());
	//SendMessage(comboHwnd, CB_SETCURSEL, --index, 0);

	
	comboHwnd = GetDlgItem(hWndDlg, IDC_COMBO_DYNAMICFONT_SIZE);
	for(int i=8; i<25; i++)
	{
		_itot_s(i, tsSize, sizeof(tsSize)/sizeof(tsSize[0]), 10);
		index = SendMessage(comboHwnd, CB_ADDSTRING, 0, (LPARAM)tsSize);
		if( g_nppFontSize == i)
		{
			//index = (int)SendMessage(comboHwnd, CB_GETCOUNT, 0, 0);
			//SendMessage(comboHwnd, CB_SETCURSEL, --index, 0);
			SendMessage(comboHwnd, CB_SETCURSEL, index, 0);
		}
	}
	
	comboHwnd = GetDlgItem(hWndDlg, IDC_CHECKBOX_DYNAMICFONTS_ENABLE);
	if( g_nppFontEnable != 0)
		SendMessage(comboHwnd, BM_SETCHECK, BST_CHECKED, 0);

	return true;
}
bool OkDlg(HWND hWndDlg)
{
	int index;
	//int itemStrLen;
	TCHAR itemStr[MAX_PATH];
	char *cItemStr;
	//5桁以上の数字が入ることはまずありえない為
	TCHAR buf[5];
	int fontSize;
	HWND comboHwnd;
	
	comboHwnd = GetDlgItem(hWndDlg, IDC_COMBO_DYNAMICFONT_SELECT);
	//index = (int)SendMessage(comboHwnd, CB_GETCURSEL, 0, 0);
	//itemStrLen = (int)SendMessage(comboHwnd, CB_GETLBTEXTLEN, index, 0);
	//itemStr = (TCHAR*) new TCHAR[itemStrLen];
	//SendMessage(comboHwnd, CB_GETLBTEXT, index, (LPARAM)itemStr);
	//delete[] itemStr;
	GetWindowText(comboHwnd, itemStr, MAX_PATH);
	WtoC(itemStr, -1, &cItemStr);
	g_nppFontName = cItemStr;
	delete[] cItemStr;

	comboHwnd = GetDlgItem(hWndDlg, IDC_COMBO_DYNAMICFONT_SIZE);
	index = (int)SendMessage(comboHwnd, CB_GETCURSEL, 0, 0);
	SendMessage( comboHwnd, CB_GETLBTEXT, index, (LPARAM)buf);
	fontSize = _ttoi(buf);
	g_nppFontSize = fontSize;

	//代用
	index = (int)SendMessage(GetDlgItem(hWndDlg, IDC_CHECKBOX_DYNAMICFONTS_ENABLE), BM_GETCHECK, 0, 0);
	if( index != 0 )
		g_nppFontEnable = 1;
	else
		g_nppFontEnable = 0;
	Dprintf("fontName %s fontSize %d fontEnable\n", g_nppFontName.c_str(), g_nppFontSize, g_nppFontEnable);
	return true;
}
int CALLBACK EnumeFontsExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, DWORD fontType, LPARAM lParam)
{
	std::wstring str(lpelfe->elfLogFont.lfFaceName);
	for( std::vector<std::wstring>::iterator it = g_fonts.begin(); it != g_fonts.end(); ++it)
	{
		if( *(it) == str)
			return 1;
	}
	g_fonts.push_back( str );
	//Dprintf("%s\n", lpelfe->elfFullName );
	return 1;
}
//SCI_SENDMSG: SCI_STYLESETFONT 0 "MS Serif"
//SCI_SENDMSG: SCI_STYLESETSIZE 0, 15
