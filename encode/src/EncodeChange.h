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
#ifndef ENCODECHANGE_H
#define ENCODECHANGE_H

#include "Encode.h"

//ゼロ終端 return 必要なバイト数 or 使用バイト数
int StrToWstr(Encode, const char*, wchar_t*, size_t);
int WstrToStr(Encode, const wchar_t*, char*, size_t);
//各文字のマルチバイト数判断
int CharSjisCodeByte(const char*);
int CharEucJpCodeByte(const char*);
int CharUtf8CodeByte(const char*);
int WcharUtf8CodeByte(const wchar_t);
int CharUtf16CodeByte(const char*);

//int -> Unicode
unsigned long Utf8CodeToUnicode(unsigned long);
unsigned long Utf16CodeToUnicode(unsigned long);
//char -> unicode
unsigned long Utf8ToUnicode(const char*);
unsigned long Utf16ToUnicode(const wchar_t*);

//return 使用char数 char*がNULLなら入力したcodeに必要なchar数が返るだけ
int UnicodeToUtf8(unsigned int, char*);
int UnicodeToUtif16(unsigned int, wchar_t*);

//utf8をutf16(wchar_t)に変換 サロゲートはintの上位2バイトと下位2バイトへ
unsigned long Utf8ToUtf16(const char*);
//utf16をutf8へ returnはchar数　e.g.サロゲートは4が返る
int Utf16ToUtf8(const wchar_t*, char*);

//CharToWchar char2つをwchar_tに押し込む 1バイトはそのまま入れる WcharToCharは逆関数return useCharCount
wchar_t CharToWchar(const char*, int);
int WcharToChar(const wchar_t, char*);

//return code int*=out マルチバイト数 jis規格=8bitJIS
unsigned int JisToSjis(const unsigned int, int*);
unsigned int SjisToJis(const unsigned int, int*);
//int = 0 or char* = NULL 必要バイト数が返る
int SjisToJisStr(const char *sjis, char *jis, int jisCharSize);

unsigned int JisToEucjp(const unsigned int, int*);
unsigned int EucjpToJis(const unsigned int, int*);
//int = 0 or char* = NULL 必要バイト数が返る
int EucjpToJisStr(const char *eucjp, char *jis, int jisCharSize);

enum JisEscape{ JISASCII, JISKANJI, JISHANKANA };
int GetJisEscape(unsigned int);
//int = 0 or char* = NULL 必要バイト数が返る const char *jis -> char *sjisへ SjisToEucjp逆関数
int EucjpToSjis(const char*, char*, int);
int SjisToEucjp(const char*, char*, int);


#endif