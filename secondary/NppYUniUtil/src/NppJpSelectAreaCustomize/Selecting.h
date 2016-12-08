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

#ifndef SELECTING_H
#define SELECTING_H

#include "..\PluginInterface.h"
#include "..\menuCmdID.h"

#define UTF8BYTE	4

class Selecting{
public:
	Selecting();
	~Selecting();
	
	void Init(NppData nppData);

	//void DBLClick(HWND hWnd, int pos);
	//void Left(bool select);
	//void Right(bool select);

	//高速アクセス用
	void DBLClick(SciFnDirect pSciMsg, sptr_t pSciWndData, int pos);
	void Left(SciFnDirect pSciMsg, sptr_t pSciWndData, bool select);
	void Right(SciFnDirect pSciMsg, sptr_t pSciWndData, bool select);

	// direction
	typedef enum{
		TOHALF,	//0-> 全->半
		TOFULL,	//1-> 半->全
		TOHIRA, //2-> カタ->ひら
		TOKATA	//3-> ひら->カタ
	}DIRECTION;

	// opt bit処理
	enum ZenHanOpt{ 
		ZHLoAlpha	=0x01,		//1 -> LoAlpha
		ZHUpAlpha	=0x01<<1,	//2 -> UpAlpha
		ZHNum		=0x01<<2,	//4 -> Num
		ZHKata		=0x01<<3,	//8 -> kata
		ZHSymbol	=0x01<<4,	//16-> symbol
		ZHAll		=0xFF
	};
		
	void ZenToHan(const DIRECTION direction, int opt=ZHAll);
	void HiraToKata(const DIRECTION direction);

private:
	HWND nppHwnd;
	HWND mainScintilla;
	HWND secondScintilla;

	HWND _hWnd;
	int _pos;
	unsigned char utfChar[UTF8BYTE+1];

	//高速化処理
	unsigned long utf8Code;
	int GetUtf8Code(const char *src, int pos, int *startPos);
	//高速化処理(char*をずっと保持する現在の行が保持できる最大数より巨大な場合再作成させる
	char* lineStr;
	int lineStrLength;
	//現在のlineStrのバッファのサイズ確認と確保
	bool HeapLineStr(int length);
	
	int SetChar(int readPos);
	int SetChar(int readPos, const char *str);
	int GetUTFCode();
	int GetMultibyteCharacter(int UTFCode);
	
	//コードの分割用
	int ZenHanStr(const char *src, size_t srcSize, char *dest, size_t destSize, const DIRECTION direction, int opt);
	//コード分割用
	unsigned int ZenHan(const unsigned int code, const DIRECTION direction, int opt, unsigned int *daku);
	//全角→半角時,濁点、半濁点かどうかがdakuに帰る　半角→全角時は濁点、半濁点をどうかをdakuに入れる
	unsigned int ZenHanKata(unsigned int UTFCode, unsigned int *daku, const DIRECTION direction);
	//記号全半変換
	unsigned int ZenHanSymbol(unsigned int UTFCode, const DIRECTION direction);

	enum CodeKind {
		error = -1,
		Hankaku,
		hEtc, hEsc, hWord, hAlpha, hUpAlpha, hLoAlpha, hNum, hKata, hPunc, hSpace, hNewLine, hKataEtc,
		Zenkaku,
		zEtc, zEsc, zWord, zAlpha, zUpAlpha, zLoAlpha, zNum, zKata, zPunc, zSpace, zHira, zKanji, zHiraEtc, zKataEtc,
	};

	int CodeKind(unsigned int utfCode, bool closely=false);
	int CodeClosely(unsigned int utfCode);
};
#endif