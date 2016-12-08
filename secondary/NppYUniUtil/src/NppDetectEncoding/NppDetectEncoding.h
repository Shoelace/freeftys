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

#ifndef NPPDETECTENCODING_H
#define NPPDETECTENCODING_H

#include "..\dllmain.h"
#include "..\resource.h"

#include "Encode.h"
#include "EncodeDetect.h"
#include "EncodeChange.h"
#include "..\Ini.h"

#define FULLPATH	1024
enum { 
	SJISCODE = 932, 
	EUCJPCODE = 20932 
};

//JpDetectEncoding
//void onDetectEncodingSetInfo(NppData *notpadPlusData);

void onDetectEncodingBeNotified(SCNotification *notifyCode);

//サブクラス化用
//void SetWndProc();
//void UnsetWndProc();

//文字コードをステータスバーへ
int StatusBarEncodeChange(HWND Hwnd, int bufferID);

//notepad++から呼ばれる関数群
void OpenSjis();
void OpenEucjp();
void EucjpToSjis();
void SjisToEucjp();
void DetectEncodeOption();
BOOL CALLBACK DetectEncodingOptionDlgProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

//enum UniMode {uni8Bit=0, uniUTF8=1, uni16BE=2, uni16LE=3, uniCookie=4, uni7Bit=5, uni16BE_NoBOM=6, uni16LE_NoBOM=7, uniEnd};
//ファイルサイズの取得
int FileSize(const TCHAR*);
//オープン後
void onOpenFiled(Sci_NotifyHeader*);
//ファイルのクローズ
void FileClose(HWND nppHwnd, const TCHAR *fileName);
//セッション機能を使ってencode指定の再オープン
void SessionReopen(HWND Hwnd, const TCHAR *fileName, int encoding, int langType);
//htmlエスケープ
void XmlEscape(const TCHAR*, TCHAR*, int);
//セッションファイル作成
void WriteSession(const TCHAR *sessionFilName, const TCHAR *fileName, int encode, int langType);
//文字コード判定
int DetectEncode(const TCHAR*);
//拡張子から言語タイプの検出
int ExtensionToLang(TCHAR *extension);
//拡張子を初期化
void InitLangStr();

#endif