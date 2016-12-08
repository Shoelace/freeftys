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

#include "main.h"

#include "Encode.h"
#include "EncodeDetect.h"
#include "EncodeChange.h"
#include "CharOperate.h"

#include "MyDebug.h"

#include <windows.h>

#include <locale.h>

enum CmdLineOption{ DETECTENCODE=1, CHANGEENCODE=1<<1, CHARCOUNT=1<<2, HANTOZEN=1<<3, ZENTOHAN=1<<4, DETECTONRY=1<<5};

//-i 入力ファイル
//-o 出力ファイル
//-c 文字コード変更
//-m 文字のカウント
//-z 全角を半角へ
//-h 半角を全角へ
//-g 入力されたファイルの文字コードを出力するだけ他のオプションは無視する 読み込みバイト数はファイルサイズ

//-d 自動で判定させる為中止文字エンコード判定
int main(int argc, char* argv[])
{
	unsigned int cmdOpt = 0;
	unsigned int zhOpt = 0;
	setlocale( LC_ALL, "Japanese" );
	StartConsole();

	int i;
	char *fileName =  NULL;
	char *saveFileName = NULL;
	int toEncode=0;
	if( argc <= 1)
		fileName = "testテキストファイル.txt";
	else
		fileName = argv[1];

	for(i=0; i<argc; i++)
		Dcprintf("%s ", argv[i]);
	Dprintf("\n");

	for(i=0; i<argc; i++)
	{
		if( *(argv[i]) == '-'){
			int j = 1;
			int k = i;
			int l, zth;
			//printf("コマンドラインスイッチ %s\n", (argv[i]+1) );
			//*(argv[k]+j) != 0 && 
			while( j < (int)strlen(argv[k]))
			{
				switch( *(argv[k]+j) )
				{
				case 'g':
					//他のすべてのオプションを無視して入力ファイルのエンコードのみ出力
					cmdOpt = DETECTONRY;
					if( argv[i+1] != NULL)
					{
						//次のコマンドを
						fileName = argv[k+1];
						i = argc;
						j = strlen(argv[k]);
					}
					break;
				case 'o':
					if( argv[i+1] != NULL)
					{
						//次のコマンドをアウトプットファイル名にする
						saveFileName = argv[i+1];
						i++;
					}
					printf("output file = %s\n", saveFileName);
					break;
				case 'i':
					if( argv[i+1] != NULL)
					{
						//次のコマンドを
						fileName = argv[i+1];					
						i++;
					}
					cmdOpt |= DETECTENCODE;
					printf("input file = %s\n", fileName);
					break;
				//case 'd':
				//	cmdOpt |= DETECTENCODE;
				//	printf("文字エンコード確認\n");
				//	break;
				case 'c':
					if( argv[i+1] != NULL)
					{
						//次のコマンドを
						cmdOpt |= CHANGEENCODE;
						toEncode = atoi( argv[i+1] );
						i++;
					}
					printf("文字エンコード変更 %d sjis=1 euc-jp=2 utf8=3 utf16BE=4 \n", toEncode);
					break;
				case 'm':
					cmdOpt |= CHARCOUNT;
					printf("UNICODEでの文字数カウント\n");
					break;
				case 'z':
				case 'h':
					// '-' と 'z' or 'h'分
					l = j+1;
					zth = 1;
					zhOpt = 0;
					//ZHLoAlpha=1, ZHUpAlpha=2, ZHNum=4, ZHKata=8, ZHSymbol=16, ZHAll
					while(zth)
					{
						switch( *(argv[k]+l) )
						{
						case 'a':
							printf("英字小文字\n");
							zhOpt |= ZHLoAlpha;
							break;
						case 'A':
							printf("英字大文字\n");
							zhOpt |= ZHUpAlpha;
							break;
						case 'n':
						case 'N':
							printf("数字\n");
							zhOpt |= ZHNum;
							break;
						case 'K':
						case 'k':
							printf("カタカナ\n");
							zhOpt |= ZHKata;
							break;
						case 'S':
						case 's':
							printf("記号\n");
							zhOpt |= ZHSymbol;
							break;
						default:
							zth = 0;
							break;
						}
						l++;
					}
					if( zhOpt == 0)
						zhOpt = ZHAll;
					if( *(argv[k]+j) == 'z' || *(argv[k]+j) == 'Z' )
					{
						cmdOpt |= ZENTOHAN;
						printf("全角を半角へ\n");
					}
					else
					{
						cmdOpt |= HANTOZEN;
						printf("半角を全角へ\n");
					}
					j+=l;
					break;
				}
				j++;
			}
		}	
	}
	if( cmdOpt != 0)
		CmdLineOpt( cmdOpt, fileName, saveFileName, toEncode, zhOpt);

#ifdef _DEBUG
	printf("getchar()=");
	getchar();
	printf("----\n\n\n");
#endif
	EndConsole();
	return 0;
}

void CmdLineOpt(unsigned int cmdOpt, const char *fileName, const char *saveFileName, int changeTo, int zhOpt)
{
	int fSize;
	char *buf = NULL;
	void *dest = NULL;
	int charMode;
	Encode encode = ETC;
	int block = 1024;
	
	if( cmdOpt & DETECTONRY)
	{
		char *lastFileName;
		encode = (Encode)EncodeDetectFile(fileName, 0);
		switch(encode)
		{
		case UTF16BE:	printf("UTF-16BE\t");break;
		case UTF16LE:	printf("UTF-16LE\t");break;
		case UTF8N:		printf("UTF-8N\t\t");break;
		case UTF8:		printf("utf-8\t\t");break;
		case SJIS:		printf("s-jis\t\t");break;
		case EUCJP:		printf("euc-jp\t\t");break;
		case ETC:
		default:
			printf("any or ascii\t");
			break;
		}
		lastFileName = strrchrn(fileName, '\\', 2);
		printf("<- %s\n", lastFileName);
		return;
	}
	
	fSize = FileRead(fileName, &buf, 0);
	if( cmdOpt & DETECTENCODE)
	{
		//--detect encode
		//encode = EncodeDetectFile(fileName, 100);
		encode = (Encode)EncodeDetect(buf, fSize);
		switch(encode)
		{
		case UTF16BE:	printf("encode == UTF-16BE\n");	break;
		case UTF16LE:	printf("encode == UTF-16LE\n");	break;
		case UTF8N:		printf("encode == UTF-8N\n");	break;
		case UTF8:		printf("encode == utf-8\n");	break;
		case SJIS:		printf("encode == s-jis\n");	break;
		case EUCJP:		printf("encode == euc-jp\n");	break;
		case ETC:
		default:
			printf("encode == any or ascii\n");
			break;
		}
	}
	
	if( cmdOpt & CHANGEENCODE && encode != ETC)
	{
		Encode to;
		switch(changeTo)
		{
		case 1: to = SJIS; break;
		case 2: to = EUCJP; break;
		case 3: to = UTF8; break;
		case 4: to = UTF16BE; break;
		}
		//LoUpCase((wchar_t*)buf, 0, ZHLoCaseAlpha);
		//TitleCase((wchar_t*)buf, 0, ZTitleCase);
		charMode = CmdEncodeChange(buf, &dest, encode, to);
	}
	//全部asciiの場合ETCになるので条件から外す
	if( cmdOpt & CHARCOUNT)// && encode != ETC)
	{
		//if( dest != NULL)
		//{
		//	if( charMode )
		//	CmdCharCount(dest, encode);
		//}
		//else
		{
			CmdCharCount(buf, encode);
		}
	}
	//テストとして特定のエンコードへ変更するときのみ受け付ける//utf8 = 3 UTF16BE = 4
	if( (cmdOpt & ( HANTOZEN | ZENTOHAN)) && changeTo == 3)
	{
		////テストutf16be
		//int reverse = 0;
		//wchar_t *zhBuf = NULL;
		//int zhBufLen;
		//if( cmdOpt & HANTOZEN )
		//	reverse = 1;

		//zhBufLen = ZenHanStrW((const wchar_t*)buf, wcslen((const wchar_t*)buf), NULL, 0, zhOpt, reverse);
		//zhBuf = (wchar_t*)new wchar_t[zhBufLen];
		//zhBufLen = ZenHanStrW((const wchar_t*)buf, wcslen((const wchar_t*)buf), zhBuf, zhBufLen, zhOpt, reverse);

		//if( dest != NULL)
		//	delete[] dest;

		//dest = (wchar_t*) new wchar_t[zhBufLen];
		//memset(dest, 0, sizeof(wchar_t)*zhBufLen);
		//wcscpy_s((wchar_t*)dest, zhBufLen, zhBuf);

		//delete[] zhBuf;
		//charMode = 2;

		int reverse = 0;
		char *zhBuf = NULL;
		int zhBufLen;
		if( cmdOpt & HANTOZEN )
			reverse = 1;

		zhBufLen = ZenHanStrA((const char*)dest, strlen((const char*)dest), NULL, 0, zhOpt, reverse);
		zhBuf = (char*)new char[zhBufLen];
		zhBufLen = ZenHanStrA((const char*)dest, strlen((const char*)dest), zhBuf, zhBufLen, zhOpt, reverse);

		if( dest != NULL)
			delete[] dest;

		dest = (char*) new char[zhBufLen];
		memset(dest, 0, sizeof(char)*zhBufLen);
		strcpy_s((char*)dest, zhBufLen, zhBuf);

		delete[] zhBuf;
	}

	if( dest != NULL)
	{
		if( saveFileName != NULL )
		{
			FILE *fp;
			if( fopen_s(&fp, saveFileName, "wb") == 0)
			{
				int len;
				if( charMode == 1)
					len = strlen((char*)dest);
				else
					len = wcslen((wchar_t*)dest);

				fwrite(dest, charMode, len, fp);

				fclose(fp);
			}			
			//if( _wfopen_s(&fp, L"test.txt", L"w,ccs=UTF-8") == 0 )
			//{
			//	fwprintf(fp, L"%s", wbuf);
			//	fclose(fp);
			//}
		}
		else
		{
			if( charMode == 1)
				printf("%s\n", dest);
			else
				wprintf(L"%s\n", dest);
		}
	}

	if( buf != NULL) delete[] buf;
	if( dest != NULL) delete[] dest;

	//int zhsize;
	//wchar_t *zhbuf;
	//printf("\n全角半角変換\n");
	//printf("サイズ %d\n", wcslen(wbuf) );
	//zhsize = ZenHanStr(wbuf+30, 50, NULL, 0, ZHKata | ZHLoAlpha, 0);
	//printf("全角->半角変換バッファサイズ %d\n", zhsize);
	//zhbuf = (wchar_t*) new wchar_t[zhsize];
	//zhsize = ZenHanStr(wbuf+30, 50, zhbuf, zhsize, ZHKata | ZHLoAlpha, 0);
	//wprintf(L"%s\n", zhbuf);
	//if(zhbuf) delete[] zhbuf;

	//zhsize = ZenHanStr(wbuf+30, 50, NULL, 0, ZHKata | ZHLoAlpha, 1);
	//printf("半角->全角変換バッファサイズ %d\n", zhsize);
	//zhbuf = (wchar_t*) new wchar_t[zhsize];
	//zhsize = ZenHanStr(wbuf+30, 50, zhbuf, zhsize, ZHKata | ZHLoAlpha, 1);
	//wprintf(L"%s\n", zhbuf);
	//if(zhbuf) delete[] zhbuf;


	//if( wbuf ) delete[] wbuf;
	//if( cbuf ) delete[] cbuf;
	return;
}


int CmdEncodeChange(const char *str, void **dest, Encode from, Encode to)
{
	int charMode = 0;
	int sjislen, euclen, utf8len;
	char *sjis, *euc, *utf8;
	int utf16len;
	wchar_t *utf16;

	if( from == to)
		return 0;

	//init
	euc = NULL;
	euclen = 0;
	sjis = (char*)str;
	sjislen = 0;
	utf8 = NULL;
	utf8len = 0;
	if( from == UTF16LE || from == UTF16BE)
		utf16 = (wchar_t*)(str+2);
	else
		utf16 = (wchar_t*)str;
	utf16len = 0;

	//encodeChange euc -> sjis -> utf16 -> utf8 -> utf16 -> sjis -> euc 引っ掛ったところで開始と終了
	switch( from )
	{
	case EUCJP:
		sjislen = EucjpToSjis(str, NULL, 0);
		sjis = (char*) new char[sjislen];
		memset(sjis, 0, sizeof(char)*sjislen);
		sjislen = EucjpToSjis(str, sjis, sjislen);
		if( to == SJIS)
		{
			*dest = (void*)sjis;
			//*dest = (char*) new char[sjislen];
			//strcpy_s((char*)*dest, sjislen, sjis);
			//delete[] sjis;
			return sizeof(char);
		}
	case SJIS:
		utf16len = MultiByteToWideChar(CP_ACP, NULL, sjis, -1, NULL, 0);
		utf16 = (wchar_t*) new wchar_t[utf16len];
		memset(utf16, 0, sizeof(wchar_t)*utf16len);
		utf16len = MultiByteToWideChar(CP_ACP, NULL, sjis, -1, utf16, utf16len);

		//sjisの場合
		if( sjislen != 0)
		{
			delete[] sjis;
			sjis = NULL;
			sjislen = 0;
		}

		if( to == UTF16BE || to == UTF16LE)
		{
			*dest = (void*)utf16;
			//*dest = (wchar_t*) new wchar_t[utf16len];
			//wcscpy_s((wchar_t*)*dest, utf16len, utf16);
			//delete[] utf16;
			return sizeof(wchar_t);
		}
	case UTF16BE:
	case UTF16LE:
		utf8len = WideCharToMultiByte(CP_UTF8, NULL, utf16, -1, NULL, 0, NULL, NULL);
		utf8 = (char*) new char[utf8len];
		memset(utf8, 0, sizeof(char)*utf8len);
		utf8len = WideCharToMultiByte(CP_UTF8, NULL, utf16, -1, utf8, utf8len, NULL, NULL);

		//utf16の場合
		if( utf16len != 0)
		{
			delete[] utf16;
			utf16 = NULL;
			utf16len = 0;
		}

		if( to == UTF8 || to == UTF8N)
		{
			*dest = (void*)utf8;
			//*dest = (void*)new char[utf8len];
			//strcpy_s((char*)*dest, utf8len, utf8);
			//delete[] utf8;
			return sizeof(char);
		}
		break;
	}

	//utf8start init
	if( utf8 == NULL)
	{
		if( from == UTF8 )
			utf8 = (char*)(str+3);
		else
			utf8 = (char*)str;
	}
		
	switch( from )
	{
	case UTF8:
	case UTF16BE:
	case UTF16LE:
		utf16len = MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, NULL, 0);
		utf16 = (wchar_t*) new wchar_t[utf16len];
		memset(utf16, 0, sizeof(wchar_t)*utf16len);
		utf16len = MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, utf16, utf16len);
		//utf8の場合
		if( utf8len != 0)
		{
			delete[] utf8;
			utf8 = NULL;
			utf8len = 0;
		}
		if( to == UTF16BE || to == UTF16LE)
		{
			*dest = (void*)utf16;
			//*dest = (wchar_t*) new wchar_t[utf16len];
			//wcscpy_s((wchar_t*)*dest, utf16len, utf16);
			//delete[] utf16;
			return sizeof(wchar_t);
		}
	case SJIS:
		sjislen = WideCharToMultiByte(CP_ACP, NULL, utf16, -1, NULL, 0, NULL, NULL);
		sjis = (char*) new char[sjislen];
		sjislen = WideCharToMultiByte(CP_ACP, NULL, utf16, -1, sjis, sjislen, NULL, NULL);
		//utf16の場合
		if( utf16len != 0)
		{
			delete[] utf16;
			utf16 = NULL;
			utf16len = 0;
		}
		if( to == SJIS)
		{
			*dest = (void*)sjis;
			//*dest = (char*) new char[sjislen];
			//strcpy_s((char*)*dest, sjislen, sjis);
			//delete[] sjis;
			return sizeof(char);
		}
	case EUCJP:
		euclen = SjisToEucjp(sjis, NULL, 0);
		euc = (char*) new char[euclen];
		euclen = SjisToEucjp(sjis, euc, euclen);
		//sjisの場合
		if( sjislen != 0)
		{
			delete[] sjis;
			sjis = NULL;
			sjislen = 0;
		}
		if( to == SJIS)
		{
			*dest = (void*)euc;
			//*dest = (char*) new char[euclen];
			//strcpy_s((char*)*dest, euclen, euc);
			//delete[] euc;
			return 1;
		}
		break;
	}

	return 0;
}
void CmdCharCount(const char *str, Encode encode)
{
	//--charArea unicode
	wchar_t *buf;
	int i;
	int codeKind;
	int count[AllCodeCount+1] = { 0 };
	//int hEtcCount, hEscCount, hWordCount, hAlphaCount, hUpAlphaCount, hLoAlphaCount;
	//int hNumCount, hKataCount, hPuncCount, hSpaceCount, hNewLineCount;
	//int hKataEtcCount;
	//int zEtcCount, zEscCount, zWordCount, zAlphaCount, zUpAlphaCount, zLoAlphaCount;
	//int zNumCount, zKataCount, zPuncCount, zHiraCount, zKanjiCount, zSpaceCount;
	//int zHiraEtcCount, zKataEtcCount;

	//hEtcCount = 0;
	//hEscCount = 0;
	//hWordCount = 0;
	//hAlphaCount = 0;
	//hUpAlphaCount = 0;
	//hLoAlphaCount = 0;
	//hNumCount = 0;
	//hKataCount = 0;
	//hPuncCount = 0;
	//hSpaceCount = 0;
	//hNewLineCount = 0;
	//zEtcCount = 0;
	//zEscCount = 0;
	//zWordCount = 0;
	//zAlphaCount = 0;
	//zUpAlphaCount = 0;
	//zLoAlphaCount = 0;
	//zNumCount = 0;
	//zKataCount = 0;
	//zPuncCount = 0;
	//zHiraCount = 0;
	//zKanjiCount = 0;
	//zSpaceCount = 0;
	//zHiraEtcCount = 0;
	//zKataEtcCount = 0;
	//hKataEtcCount = 0;

	
	CmdEncodeChange( str, (void**)&buf, encode, UTF16BE);
	int len = wcslen(buf);
	for(i=0; i<len ; i++)
	{
		codeKind = CodeKind(buf[i], 1);
		if( Hankaku < codeKind && codeKind < Zenkaku)
			count[Hankaku]++;
		else if( Zenkaku < codeKind)
			count[Zenkaku]++;

		count[codeKind]++;
		count[AllCodeCount]++;
		//wprintf(L"%c", str[i]);
		//switch(codeKind)
		//{
		//case hEtc:		hEtcCount++; break;
		//case hEsc:		hEscCount++; break;
		//case hWord:		hWordCount++; break;
		//case hAlpha:	hAlphaCount++; break;
		//case hUpAlpha:	hUpAlphaCount++; break;
		//case hLoAlpha:	hLoAlphaCount++; break;
		//case hNum:		hNumCount++; break;
		//case hKata:		hKataCount++; break;
		//case hPunc:		hPuncCount++; break;
		//case hSpace:	hSpaceCount++; break;
		//case hNewLine:	hNewLineCount++; break;

		//case zEtc:		zEtcCount++; break;
		//case zEsc:		zEscCount++; break;
		//case zWord:		zWordCount++; break;
		//case zAlpha:	zAlphaCount++; break;
		//case zUpAlpha:	zUpAlphaCount++; break;
		//case zLoAlpha:	zLoAlphaCount++; break;
		//case zNum:		zNumCount++; break;
		//case zKata:		zKataCount++; break;
		//case zPunc:		zPuncCount++; break;
		//case zHira:		zHiraCount++; break;
		//case zKanji:	zKanjiCount++; break;
		//case zSpace:	zSpaceCount++;break;
		//}
		//wprintf(L" ");
	}
	
	i=0;
	
	wprintf(L"半-全て %d\n"		, count[i++]);
	wprintf(L"半-記号 %d\n"		, count[i++]);
	wprintf(L"半-制御文字 %d\n"	, count[i++]);
	wprintf(L"半-文字 %d\n"		, count[i++]);
	wprintf(L"半-英字 %d\n"		, count[i++]);
	wprintf(L"半-英字大 %d\n"	, count[i++]);
	wprintf(L"半-英字小 %d\n"	, count[i++]);
	wprintf(L"半-数字 %d\n"		, count[i++]);
	wprintf(L"半-カナ %d\n"		, count[i++]);
	wprintf(L"半-約物 %d\n"		, count[i++]);
	wprintf(L"半-SP %d\n"		, count[i++]);
	wprintf(L"半-改行 %d\n"		, count[i++]);
	wprintf(L"半-カナ記号 %d\n"	, count[i++]);

	wprintf(L"全-全て %d\n"		, count[i++]);
	wprintf(L"全-記号 %d\n"		, count[i++]);
	wprintf(L"全-制御 %d\n"		, count[i++]);
	wprintf(L"全-文字 %d\n"		, count[i++]);
	wprintf(L"全-英字 %d\n"		, count[i++]);
	wprintf(L"全-英字大 %d\n"	, count[i++]);
	wprintf(L"全-英字小 %d\n"	, count[i++]);
	wprintf(L"全-数字 %d\n"		, count[i++]);
	wprintf(L"全-カナ %d\n"		, count[i++]);
	wprintf(L"全-約物 %d\n"		, count[i++]);
	wprintf(L"全-SP %d\n"		, count[i++]);
	wprintf(L"全-ひら %d\n"		, count[i++]);
	wprintf(L"全-漢字 %d\n"		, count[i++]);
	wprintf(L"全-ひら記号 %d\n"	, count[i++]);
	wprintf(L"全-カナ記号 %d\n"	, count[i++]);
	
	wprintf(L"全 %d\n"			, count[i++]);

	//wprintf(L"半-記号 %d\n"		, hEtcCount);
	//wprintf(L"半-制御文字 %d\n"	, hEscCount);
	//wprintf(L"半-文字 %d\n"		, hWordCount);
	//wprintf(L"半-英字 %d\n"		, hAlphaCount);
	//wprintf(L"半-英字大 %d\n"	, hUpAlphaCount);
	//wprintf(L"半-英字小 %d\n"	, hLoAlphaCount);
	//wprintf(L"半-数字 %d\n"		, hNumCount);
	//wprintf(L"半-カナ %d\n"		, hKataCount);
	//wprintf(L"半-約物 %d\n"		, hPuncCount);
	//wprintf(L"半-SP %d\n"		, hSpaceCount);
	//wprintf(L"半-改行 %d\n"		, hNewLineCount);

	//wprintf(L"全-記号 %d\n"		, zEtcCount);
	//wprintf(L"全-制御 %d\n"		, zEscCount);
	//wprintf(L"全-文字 %d\n"		, zWordCount);
	//wprintf(L"全-英字 %d\n"		, zAlphaCount);
	//wprintf(L"全-英字大 %d\n"	, zUpAlphaCount);
	//wprintf(L"全-英字小 %d\n"	, zLoAlphaCount);
	//wprintf(L"全-数字 %d\n"		, zNumCount);
	//wprintf(L"全-カナ %d\n"		, zKataCount);
	//wprintf(L"全-約物 %d\n"		, zPuncCount);
	//wprintf(L"全-ひら %d\n"		, zHiraCount);
	//wprintf(L"全-漢字%d\n"		, zKanjiCount);
	//wprintf(L"全-SP %d\n"		, zSpaceCount);

	
	if( buf != NULL) delete[] buf;
	return;
}
unsigned int FileRead(const char *fileName, char **buf, int readSize)
{
	FILE *fp;
	int fsize = readSize;

	if( fopen_s(&fp, fileName, "rb") == 0)
	{
		if( fsize == 0)
			fsize = FileSize(fp);

		Dcprintf("%s, readSize=%dバイト\n", fileName, fsize);

		*buf = (char*) new char[fsize];
		memset(*buf, 0, fsize);
		fsize = fread(*buf, sizeof(char), fsize/sizeof(char), fp);
		//printf("%s\n", buf);
		fclose(fp);
	}
	return fsize;
}


char* strrchrn(const char *src, int c, int count)
{
	char *pos;
	int length;
	int hitCount;
	int i;
	
	pos = (char*)src;
	length = strlen(src);
	hitCount = 0;
	for(i=length; i>=0; i--)
	{
		if( *(src+i) == c )
		{
			hitCount++;
			if( count == hitCount)
			{
				pos = (char*)src+i;
				break;
			}
		}
	}
	return pos;
}