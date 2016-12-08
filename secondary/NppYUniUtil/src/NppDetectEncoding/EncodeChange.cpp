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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EncodeChange.h"


//int StrToWstr(Encode formEncode, const char *src, wchar_t *dest, size_t destSize)
//{
//	int surrogatePairs;
//	int codeByte;
//	int bufSize;
//	int i;
//	
//	i=0;
//	bufSize=0;
//	surrogatePairs = 0;
//
//	//必要なサイズ計測
//	if( destSize == 0)
//	{
//		//BOM
//		if( formEncode == UTF8N )
//		{
//			//BOM追加分
//			bufSize++;
//			i=3;
//		}
//
//		while( *(src+i) != 0 )
//		{
//			switch(formEncode)
//			{
//			case SJIS:
//				codeByte = CharSjisCodeByte( (src+i) );
//				break;
//			case EUCJP:
//				codeByte = CharEucJpCodeByte( (src+i) );
//				break;
//			case UTF8N:
//			case UTF8:
//				codeByte = CharUtf8CodeByte( (src+i) );
//				if( codeByte == 4 )
//					surrogatePairs = 1;
//				break;
//			case UTF16BE:
//			case UTF16LE:
//				codeByte = CharUtf16CodeByte( (src+i) );
//				if( codeByte == 4 )
//					surrogatePairs = 1;
//				break;
//			}
//			//サロゲートペア時は2バイト必要
//			if(surrogatePairs != 1)
//			{
//				bufSize++;
//			}
//			else
//			{
//				bufSize+=2;
//				surrogatePairs = 0;
//			}
//			i += codeByte;
//		}
//		//終端文字\0分
//		bufSize++;
//	}
//	else
//	{
//		int codeByte;
//		
//		if( formEncode == UTF8N)
//		{
//			//BOM追加
//			dest[bufSize] = 0xFEFF;
//			bufSize++;
//			i=3;
//		}
//
//		while( *(src+i) != 0 && (unsigned int)bufSize<destSize)
//		{
//			//utf8の時は変換作業が入るので
//			if( formEncode == UTF8 || formEncode == UTF8N)
//			{
//				unsigned long code;
//				codeByte = CharUtf8CodeByte( (src+i) );
//
//				//utf8 -> utf16
//				code = Utf8ToUtf16( (src+i) );
//				
//				//サロゲートのチェック
//				if( code <= 0xFFFF )
//				{
//					dest[bufSize] =(wchar_t)code;
//					bufSize++;
//				}
//				else
//				{
//					//サロゲートペア
//					dest[bufSize] = code >> 16;
//					bufSize++;
//					dest[bufSize] = code & 0xFFFF;
//					bufSize++;
//				}
//			}
//			else
//			{
//				switch(formEncode)
//				{
//				case SJIS:
//					codeByte = CharSjisCodeByte( (src+i) );
//					break;
//				case EUCJP:
//					codeByte = CharEucJpCodeByte( (src+i) );
//					break;
//				case UTF16BE:
//				case UTF16LE:
//					codeByte = CharUtf16CodeByte( (src+i) );
//					break;
//				}
//				dest[bufSize] = CharToWchar( (src+i), codeByte );
//				bufSize++;
//			}
//			i += codeByte;
//		}
//		//終端文字\0分
//		dest[bufSize] = 0;
//		bufSize++;
//	}
//	return bufSize;
//}
//int WstrToStr(Encode toEncode, const wchar_t *src, char *dest, size_t destSize)
//{
//	int i;
//	int bufSize;
//	//必要なサイズ計測
//	if( destSize == 0)
//	{
//		int codeByte;
//		i=0;
//		bufSize=0;
//		
//		if( toEncode == UTF8N)
//		{
//			bufSize = 3;
//			i = 1;
//		}
//		while( *(src+i) != 0 )
//		{
//			//2バイト文字列かどうか asciiと半角(utf8)以外
//			if( *(src+i) < 0x00FF)
//			{
//				bufSize++;
//			}
//			else
//			{
//				switch(toEncode)
//				{
//				case SJIS:
//				case EUCJP:
//					if(  *(src+i) <= 0x00FF )
//						bufSize += 2;
//					else
//						bufSize+=2;
//					break;
//				case UTF8:
//				case UTF8N:
//					codeByte = WcharUtf8CodeByte( *(src+i) );
//					//サロゲートだったら次の文字もサロゲートなので一文字進める
//					if( codeByte >= 4)
//						i++;
//					bufSize+=codeByte;
//					break;
//				case UTF16BE:
//				case UTF16LE:
//					//サロゲートチェック
//					if( 0xD800 <= *(src+i) && *(src+i) <= 0xDFFF)
//					{
//						bufSize+=4;
//						i++;
//					}
//					else
//					{
//						bufSize+=2;
//					}
//					break;
//				}
//			}
//			i++;
//		}
//		//終端文字\0分
//		bufSize++;
//	}
//	else
//	{
//		int codeByte;
//		i=0;
//		bufSize=0;
//		//BOM
//		if( toEncode == UTF8N )
//		{
//			//BOM追加分
//			dest[bufSize++] = (char)0xEF;
//			dest[bufSize++] = (char)0xBB;
//			dest[bufSize++] = (char)0xBF;
//			i=1;
//		}
//
//		while( (*(src+i) != 0) && ((unsigned int)bufSize < destSize) )
//		{
//			//2バイト文字列かどうか asciiと半角(utf8)以外
//			switch(toEncode)
//			{
//			case SJIS:
//			case EUCJP:				
//				bufSize += WcharToChar( *(src+i), (dest+bufSize) );
//				break;
//			case UTF8:
//			case UTF8N:
//				codeByte = Utf16ToUtf8( (src+i), (dest+bufSize) );
//				//サロゲートだったら次の文字もサロゲートなので一文字進める
//				if( codeByte >= 4)
//					i++;
//				bufSize+=codeByte;
//				break;
//			case UTF16BE:
//			case UTF16LE:
//				//サロゲートチェック
//				if( 0xD800 <= *(src+i) && *(src+i) <= 0xDFFF)
//				{
//					WcharToChar( *(src+i), (dest+bufSize) );
//					i++;
//					WcharToChar( *(src+i), (dest+bufSize+2) );
//					bufSize+=4;
//				}
//				else
//				{
//					bufSize+=2;
//				}
//				break;
//			}
//			i++;
//		}
//		//終端文字\0分
//		dest[bufSize] = 0;
//		bufSize++;
//	}
//	return bufSize;
//}
int CharSjisCodeByte(const char *code)
{
	unsigned char *uSrc;
	int i=0;

	uSrc = (unsigned char*)code;
	//ascii or 半角カナ
	if( (*uSrc < 0x80) || (*uSrc >= 0xA0 && *uSrc < 0xE0) )
	{
		i++;
	}
	//2バイト文字
	else
	{
		i+=2;
	}

	return i;
}
int CharEucJpCodeByte(const char *code)
{
	unsigned char *uSrc;
	int i=0;

	uSrc = (unsigned char*)code;
	//ascii
	if( *uSrc < 0x80 )
	{
		i++;
	}
	//2バイト文字(半角カナも2バイト)
	else
	{
		i+=2;
	}
	return i;
}
int CharUtf8CodeByte(const char *code)
{
	unsigned char *uSrc;
	int i=0;

	uSrc = (unsigned char*)code;

	//3バイト文字以下はwchar1つに収められる それ以外はサロゲートペアのため2つ必要
	if( *uSrc <= 0x7F )		//0x80以下 ascii
		i = 1;
	else if( *uSrc <= 0xDF)	//0xC2-0xDF 2バイト文字
		i = 2;
	else if( *uSrc <= 0xEF)	//0xE0-0xF0 3バイト文字
		i = 3;
	else					//サロゲート4バイト文字
		i = 4;

	return i;
}
int WcharUtf8CodeByte(const wchar_t code)
{
	int i=0;

	//サロゲートチェック
	if( 0xD800 <= code && code <= 0xDFFF)
		i=4;
	//2バイト文字列
	else if( code < 0x07FF)
		i=2;
	//3バイト文字列として処理
	else
		i=3;

	return i;
}

int CharUtf16CodeByte(const char *code)
{
	unsigned int uSrc = (unsigned int)*code;
	if( 0xD8 <= uSrc && uSrc <= 0xDF)
		return 4;
	return 2;
}
unsigned long Utf8CodeToUnicode(unsigned long code)
{
	unsigned long unicode = 0;
	if( code <= 0x7F )
	{
		//1バイト
		unicode = code;
	}
	else if( code <= 0xDFFF )
	{
		//2バイト
		unicode = ( (code & 0x1F00)>>2 ) | (code & 0x3F);
	}
	else if( code <= 0xEFFFFF )
	{
		//3バイト
		unicode = ( (code & 0x0F0000) >>4 ) | ( (code & 0x3F00)>>2 ) | (code & 0x3F);
	}
	else //if( (unsigned int)*code <= 0xF7)
	{
		//4バイト
		//一度unicodeへ
		unicode = ( (code & 0x07)>>6 ) | ( (code & 0x3F)>>4 ) | ( (code & 0x3F)>>2 ) | (code & 0x3F);
	}
	return unicode;
}
unsigned long Utf16CodeToUnicode(unsigned long code)
{
	unsigned long unicode = 0;
	//サロゲート以外はそのまま
	if( 0xD8000000 <= code && code <= 0xDFFF0000)
	{
		//4バイト サロゲートペア
		unsigned int low, high;
		unsigned int first,second;
		first = code >> 8;
		second = code & 0xFF;
		//第1バイト
		low  = (first & 0x3F) << 2;			//110110pp ppyyyyzz -> yyyyzz -> yyyyzz00
		high = ((first >> 6) & 0xF) + 1;	//110110pp ppyyyyzz -> 110110 ->     pppp+1
		unicode = high << 16 | low << 8;	//uuuuu yyyyzz00 00000000
		//第2バイト
		unicode = unicode | ( second & 0x3F); //110111zz zzwwwwww -> zz zzwwwwww
	}
	else
	{
		unicode = code;
	}

	return unicode;
}
unsigned long Utf8ToUnicode(const char *code)
{
	//unicode -> utf16 はサロゲート以外 上位バイト 下位バイトに分ける
	//utf16 -> utf8 各バイトで最初に0が出て来た以降をつなげる
	//http://homepage1.nifty.com/nomenclator/unicode/ucs_utf.htm
	//(1byte)00000000 0yyyyyyy(0x007F)				-> 0yyyyyyy
	//(2byte)00000xxx xxyyyyyy(0x07FF)				-> 110xxxxx 10yyyyyy (0xC2～0xDF) mask(0x1F 0x3F)
	//(3byte)xxxxyyyy yyzzzzzz(0xFFFF)				-> 1110xxxx 10yyyyyy 10zzzzzz (0xE0～0xEF) mask(0x0F 0x3F 0x3F)
	//(4byte)00000000 000xxxyy yyyyzzzz zzwwwwww (UNICODE) (U+10000 … U+1FFFFF)サロゲートペア 
	//(4byte)11110xxx 10yyyyyy 10zzzzzz 10wwwwww (UTF-8) (0xF0～0xF7) mask(0x07 0x3F 0x3F 0x3F)
	//(4byte)110110pp ppyyyyzz 110111zz zzwwwwww (UTF-16)(pppp = xxxyy - 1) 第1バイト0xD800 第2バイト0xDC00
	unsigned long unicode = 0;
	if( (unsigned int)*code <= 0x7F )
	{
		//1バイト
		unicode = *code;
	}
	else if( (unsigned int)*code <= 0xDF )
	{
		//2バイト
		unicode = ( (*code & 0x1F)<<6 ) | (*(code+1) & 0x3F);
	}
	else if( (unsigned int)*code <= 0xEF )
	{
		//3バイト
		unicode = ( (*code & 0x0F)<<6*2 ) | ( (*(code+1) & 0x3F)<<6 ) | (*(code+2) & 0x3F);
	}
	else //if( (unsigned int)*code <= 0xF7)
	{
		//4バイト
		//一度unicodeへ
		unicode = ( (*code & 0x07)<<6*3 ) | ( (*(code+1) & 0x3F)<<6*2 ) | ( (*(code+2) & 0x3F)<<6 ) | (*(code+3) & 0x3F);
	}

	return unicode;
}
unsigned long Utf16ToUnicode(const wchar_t *code)
{
	unsigned long unicode = 0;
	//サロゲート以外はそのまま
	if( 0xD800 <= *code && *code <= 0xDFFF)
	{
		//4バイト サロゲートペア
		unsigned int  low, high;
		//第1バイト
		low  = (*code & 0x3F) << 2;			//110110pp ppyyyyzz -> yyyyzz -> yyyyzz00
		high = ((*code >> 6) & 0xF) + 1;	//110110pp ppyyyyzz -> 110110 ->     pppp+1
		unicode = high << 16 | low << 8;	//uuuuu yyyyzz00 00000000
		//第2バイト
		unicode = unicode | ( *(code+1) & 0x3F); //110111zz zzwwwwww -> zz zzwwwwww
	}
	else
	{
		unicode = *code;
	}

	return unicode;
}
int UnicodeToUtf8(unsigned int unicode, char *dest)
{
	//unicode -> utf16 はサロゲート以外 上位バイト 下位バイトに分ける
	//utf16 -> utf8 各バイトで最初に0が出て来た以降をつなげる
	//http://homepage1.nifty.com/nomenclator/unicode/ucs_utf.htm
	//(1byte)00000000 0yyyyyyy(0x007F)				-> 0yyyyyyy
	//(2byte)00000xxx xxyyyyyy(0x07FF)				-> 110xxxxx 10yyyyyy (0xC2～0xDF) mask(0x1F 0x3F)
	//(3byte)xxxxyyyy yyzzzzzz(0xFFFF)				-> 1110xxxx 10yyyyyy 10zzzzzz (0xE0～0xEF) mask(0x0F 0x3F 0x3F)
	//(4byte)00000000 000xxxyy yyyyzzzz zzwwwwww (UNICODE) (U+10000 … U+1FFFFF)サロゲートペア 
	//(4byte)11110xxx 10yyyyyy 10zzzzzz 10wwwwww (UTF-8) (0xF0～0xF7) mask(0x07 0x3F 0x3F 0x3F)
	//(4byte)110110pp ppyyyyzz 110111zz zzwwwwww (UTF-16)(pppp = xxxyy - 1) 第1バイト0xD800 第2バイト0xDC00

	int useCount = 0;
	if( unicode <= 0x007F )
	{
		//1バイト
		useCount = 1;
		if( dest != NULL)
		{
			*dest = unicode;
		}
	}
	else if( unicode <= 0x07FF )
	{
		//2バイト
		useCount = 2;

		if( dest != NULL)
		{
			*dest		= (unicode >> 6)	& 0x1F | 0xC0;
			*(dest+1)	= unicode			& 0x3F | 0x80;
		}
	}
	else if( unicode <= 0xFFFF )
	{
		//3バイト
		useCount = 3;
		if( dest != NULL)
		{
			*dest		= (unicode >> 12)	& 0x0F | 0xE0;
			*(dest+1)	= (unicode >> 6)	& 0x3F | 0x80;
			*(dest+2)	= unicode			& 0x3F | 0x80;
		}
	}
	else //if( unicode <= 0x1FFFFF)
	{
		//4バイト
		useCount = 4;
		if( dest != NULL)
		{
			*dest		= (unicode >> 18)	& 0x07 | 0xF0;
			*(dest+1)	= (unicode >> 12)	& 0x3F | 0x80;
			*(dest+2)	= (unicode >> 6)	& 0x3F | 0x80;
			*(dest+3)	= unicode			& 0x3F | 0x80;
		}
	}

	return useCount;
}
int UnicodeToUtif16(unsigned int unicode, wchar_t *dest)
{
	int useCount = 0;
	//サロゲート以外はunicodeをそのまま入れる
	if( unicode <= 0x1FFFFF)
	{
		useCount=2;

		if( dest != NULL )
		{
			//4byte サロゲートペア
			//unicode から ucs(utf16 2byte)へ
			unicode -= 0x10000;
			//0x3FF = (11 1111 1111)2 10bit
			*dest  = unicode >> 10 | 0xD800;
			*(dest+1) = unicode & 0x3FF | 0xDC00;
		}

	}
	else
	{
		useCount=1;

		if( dest != NULL )
		{
			*dest = (wchar_t)unicode;
		}
	}

	return useCount;
}
unsigned long Utf8ToUtf16(const char *c)
{
	unsigned char *uSrc;
	unsigned long  code;
	int i=0;

	uSrc = (unsigned char*)c;

	//3バイト文字以下はwchar1つに収められる それ以外はサロゲートペアのため2つ必要
	if( *uSrc <= 0x7F )
	{
		//0x80以下 ascii
		code = *uSrc;
	}
	else if( *uSrc <= 0xDF)
	{
		//0xC2-0xDF 2バイト文字
		code = ( (*uSrc & 0x1F)<<6 ) | (*(uSrc+1) & 0x3F);
	}
	else if( *uSrc <= 0xEF)
	{
		//0xE0-0xF0 3バイト文字
		code = ( (*uSrc & 0x0F)<<6*2 ) | ( (*(uSrc+1) & 0x3F)<<6 ) | (*(uSrc+2) & 0x3F);
	}
	else
	{
		unsigned int first, second;
		//一度unicodeへ
		code = ( (*uSrc & 0x07)<<6*3 ) | ( (*(uSrc+1) & 0x3F)<<6*2 ) | ( (*(uSrc+2) & 0x3F)<<6 ) | (*(uSrc+3) & 0x3F) ;
		//unicode から ucs(utf16 2byte)へ
		code -= 0x10000;
		//0x3FF = (11 1111 1111)2 10bit
		second = code & 0x3FF | 0xDC00;
		first  = code >> 10 | 0xD800;

		code = first << 16 | second;
	}

	return code;
}
wchar_t CharToWchar(const char *c, int byteSize)
{
	unsigned int code;
	int i;

	if( byteSize <= 2)
	{
		code = 0;
		for(i=0; i<byteSize; i++)
		{
			code += (unsigned char)*(c+i);
			code = code<<8;
			//printf("%c\n", *(c+i));
		}
		code = code >> 8;
	}
	else
	{
		code = -1;
	}
	//printf("char to code %X\n", code);
	return (wchar_t)code;
}

int WcharToChar(const wchar_t c, char *dest)
{
	int useCharCount = 0;
	if( c <= 0xFF )
	{
		if( dest != NULL)
			*dest = (char)c;
		useCharCount++;
	}
	else
	{
		if( dest != NULL)
		{
			*dest = (char)(c>>8);
			*(dest+1) = (char)(c & 0xFF);
		}
		useCharCount = 2;
	}
	return useCharCount;

}



int Utf16ToUtf8(const wchar_t *c, char *dest)
{
	int i = 0;

	//ascii
	if( *c <= 0x7F)
	{
		*dest = (char)*c;
		i = 1;
	}
	else if( *c <= 0x07FF )
	{
		//2バイト文字
		*dest =		((*c >> 6)  & 0x3F) | 0xC0;
		*(dest+1) = ( *c		& 0x3F) | 0x80;

		i = 2;
	}
	//サロゲートペア
	else if( 0xD800 <= *c && *c <= 0xDFFF)
	{	
		//4バイト文字
		unsigned long unicode;
		unsigned int  low, high;
		//第1バイト
		low  = (*c & 0x3F) << 2; //110110pp ppyyyyzz -> yyyyzz -> yyyyzz00
		high = ((*c >> 6) & 0xF) + 1;  //110110pp ppyyyyzz -> 110110 ->     pppp+1
		unicode = high << 16 | low << 8;
		//第2バイト
		unicode = unicode | ( *(c+1) & 0x3F); //110111zz zzwwwwww -> zz zzwwwwww

		*dest =		( (unicode >> 18) & 0x7)  | 0xF;
		*(dest+1) = ( (unicode >> 12) & 0x3F) | 0x80;
		*(dest+2) = ( (unicode >> 6)  & 0x3F) | 0x80;
		*(dest+3) = (  unicode		  & 0x3F) | 0x80;
		
		i = 4;
	}
	else
	{
		//3バイト文字
		*dest =	   ( (*c >> 12) & 0x3F ) | 0xE0;
		*(dest+1) =( (*c >> 6)	& 0x3F ) | 0x80;
		*(dest+2) =(  *c		& 0x3F ) | 0x80;
		i = 3;
	}

	return i;
}

unsigned int JisToSjis(const unsigned int jis, int *useByte)
{
	unsigned int sjis;
	int use;

	//ascii or 半角カナ
	if( jis <= 0x00F0)
	{
		//ascii
		if( jis < 0x00F0)
		{
			sjis = jis;
		}
		//半角カナ (8bitバージョン 8bit目を下すと7bitバージョンへ)
		else
		{
			sjis = jis;
		}
		use = 1;

	}
	else
	{
		unsigned int firstByte;
		unsigned int secondByte;

		firstByte = (jis >> 8) & 0xFF;
		secondByte = jis & 0xFF;
		//JIS(0x21～0x7E)
		//第2バイトから
		/*
			基本 JISの0x開始バイト(0x21)を引いてSJISの開始バイトを足す(0x40)
			JISの第1バイトの2つ分をSJISの第1バイト1つに収めるため 0x21(0x40～0x9E) 0x022(0x9F～0xFC)にずらす(Shift)

			第1バイトが偶数なら
			B2=(B2-0x21)+0x40　(-0x21 + 0x40 = 0x1F)
			(B2>=0x7F) B2+=0x1
			奇数
			B2=(B2-0x21)+0x9F  (-0x21 + 0x9F = 0x7E)
		*/
		if( firstByte & 0x1)
		{
			secondByte += 0x1F;
			if( secondByte >= 0x7F )
				secondByte += 0x1;
		}		
		else
		{
			secondByte += 0x7E;
		}

		//第一バイト
		/*
			JISの開始コード(0x21)を引いてSJISの開始コードを足す
			JISの第1バイト2つ分をSJISの第1バイト1つ分に収めるため、奇数なら-1をして同じ第1バイトへ変換する
			2つ分を１つ分にするため領域が１つ飛ばしとなるので割る2をして詰める
			0xA0～0xE0は半角カタカナ領域と被るため使用させないようにしている可能性大 その為 0xA0以上は+0x40をする
			B1=(B1-0x21)
			(B1==奇数) B1=B1-0x1
			B1=B1/2
			B1=B1+0x81
			(B1>=0xA0) B1=B1+0x40 (0xE0-0xA0)

			※単純にそのまま2で割れば小数点以下切捨てのため奇数判定がいらなくなるため短縮用に行う
		*/
		firstByte -= 0x21;
		firstByte /= 2;
		firstByte += 0x81;
		if( firstByte >= 0xA0)
			firstByte += 0x40;
		//参考http://darkcrow00.tripod.com/letter.htm
		//firstByte += 0x1;
		//firstByte /= 2;
		//if( firstByte < 0x30 )
		//{
		//	firstByte += 0x70;
		//}
		//else
		//{
		//	firstByte += 0xB0;
		//}
		sjis = (firstByte << 8) | secondByte;

		use = 2;
	}
	if( useByte != NULL)
		*useByte = use;
	
	//printf("JIS %X\n", jis);
	//printf("SJIS %X\n", sjis);
	return sjis;
}
unsigned int SjisToJis(const unsigned int sjis, int *useByte)
{
	unsigned int jis;
	int use;

	//ascii or 半角カナ
	if( sjis < 0x00F0)
	{
		//ascii
		if( sjis < 0x0080)
		{
			jis = sjis;
		}
		//半角カナ (8bitバージョン 8bit目を下すと7bitバージョンへ)
		else
		{
			jis = sjis;
		}
		use = 1;
	}
	else
	{
		unsigned int firstByte;
		unsigned int secondByte;

		firstByte = (sjis >> 8) & 0xFF;
		secondByte = sjis & 0xFF;

		//第1バイトから
		if( firstByte >= 0xE0)
			firstByte -= 0x40;
		firstByte -= 0x81;
		firstByte = firstByte * 2 + 0x21;
		if( secondByte >= 0x9F)
			firstByte++;

		//第2バイト
		//第2バイトが0x9F以上なら第1バイトは次の物なので第２バイトは0x21～(-0x9F+0x21)
		//0x9F以下で0x7F以上なら-1(0x7Fを避けるため) 0x1F(-0x40+0x21)をして終了
		if( secondByte >= 0x9F)
		{
			secondByte -= 0x7E;
		}
		else
		{
			if( secondByte >= 0x7F)
				secondByte--;
			secondByte -= 0x1F;
		}
		jis = (firstByte << 8) | secondByte;

		use = 2;
	}

	if( useByte != NULL)
		*useByte = use;

	//printf("SJIS %X\n", sjis);
	//printf("JIS %X\n", jis);
	return jis;
}

unsigned int JisToEucjp(const unsigned int jis, int *useByte)
{
	unsigned int eucjp;
	int use;

	//ascii or 半角カナ
	if( jis < 0x00F0 )
	{		
		if( jis >= 0x00A1)
		{
			//半角カナ (8bitバージョン 8bit目を下すと7bitバージョンへ)
			eucjp = jis | 0x8E00;
			use = 2;
		}
		else
		{
			//ascii
			eucjp = jis;
			use = 1;
		}
	}
	else
	{
		eucjp = jis | 0x8080;

		use = 2;
	}

	if( useByte != NULL)
		*useByte = use;

	//printf("JIS %X\n", jis);
	//printf("EUC-JP %X\n", eucjp);
	return eucjp;
}
unsigned int EucjpToJis(const unsigned int eucjp, int *useByte)
{
	unsigned int jis;
	int use;
	
	//ascii or 半角カナ
	if( eucjp < 0xA100 )
	{
		if( eucjp >= 0x8E00)
		{
			//半角カナ(8bitバージョン 8bit目を下すと7bitバージョンへ)
			jis = eucjp - 0x8E00;
		}
		else 
		{
			//ascii
			jis = eucjp;
		}
		use = 1;
	}
	else
	{
		//jis = (eucjp | 0x8080) ^ 0x8080;
		jis = eucjp & 0x7F7F;

		use = 2;
	}

	if( useByte != NULL)
		*useByte = use;

	//printf("EUC-JP %X\n", eucjp);
	//printf("JIS %X\n", jis);
	return jis;
}

int EucjpToSjis(const char *eucjp, char *sjis, int sjisCharSize)
{
	int i = 0;
	int sjisByte;
	int eucjpByte;
	int jisCode;
	int sjisLen, eucLen;
	//+1は終端文字分
	eucLen = strlen(eucjp)+1;
	sjisLen = 0;
	while( (i < eucLen) )
	{
		eucjpByte = CharEucJpCodeByte( (eucjp+i) );
		jisCode = EucjpToJis( CharToWchar( (eucjp+i) , eucjpByte), NULL);
		
		if( sjis != NULL && sjisCharSize != 0)
		{
			WcharToChar(JisToSjis(jisCode, &sjisByte), (sjis+sjisLen));
			if( sjisLen + sjisByte > sjisCharSize )
				break;
		}
		else
			JisToSjis(jisCode, &sjisByte);

		sjisLen += sjisByte;
		i += eucjpByte;
	}
	return sjisLen;
}
int SjisToEucjp(const char *sjis, char *eucjp, int eucjpCharSize)
{
	int i = 0;
	int sjisByte;
	int eucjpByte;
	int jisCode;
	int sjisLen, eucLen;
	//+1は終端文字分
	sjisLen = strlen(sjis)+1;
	eucLen = 0;
	while( (i < sjisLen) )
	{
		sjisByte = CharSjisCodeByte( (sjis+i) );
		jisCode = SjisToJis( CharToWchar( (sjis+i) , sjisByte), NULL);
		
		if( eucjp != NULL && eucjpCharSize != 0)
		{
			WcharToChar( JisToEucjp(jisCode, &eucjpByte), (eucjp+eucLen));
			if( eucLen + eucjpByte > eucjpCharSize )
				break;
		}
		else
			JisToEucjp(jisCode, &eucjpByte);

		eucLen += eucjpByte;
		i += sjisByte;
	}
	return eucLen;
}

int GetJisEscape(unsigned int jis)
{
	//http://ja.wikipedia.org/wiki/%E6%BC%A2%E5%AD%97%E3%82%B7%E3%83%95%E3%83%88%E3%82%B3%E3%83%BC%E3%83%89
	if( jis < 0x80)
	{
		//ascii 0x1B 0x28 0x42(ESC ( B)
		return JISASCII;
		//if( jis >= 0x20) ラテン(半角英数)0x1B 0x28 0x4A(ESC ( J)
	}
	else if( jis <= 0x00FF)
	{
		//半角カナ 0x1B 0x28 0x49(ESC ( I)
		return JISHANKANA;
	}
	else
	{
		//漢字コード 0x1B 0x24 0x42(ESC $ B)
		return JISKANJI;
	}
}
