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

#include "..\MyDebug.h"
#include "EncodeDetect.h"

int EncodeDetectFile(const char *fileName, int readSize)
{
	FILE *fp;
	int encode;

	//if( fopen_s(&fp, "D:\\memo\\sendto.txt", "r") == 0)
	if( fopen_s(&fp, fileName, "r") == 0)
	{
		char *buf;
		int fsize = readSize;
		if( readSize == 0)
			fsize = FileSize(fp);

		Dprintf("%s, readSize=%dバイト\n", fileName, fsize);

		buf = (char*) new char[fsize];
		memset(buf, 0, fsize);
		fread(buf, sizeof(char), fsize, fp);
		//printf("%s\n", buf);
		fclose(fp);
		
		encode = EncodeDetect(buf, fsize);

		delete[] buf;
	}
	
	return encode;

}
int EncodeDetect(char *buf, int readSize)
{
	Encode encode= ETC;
	int i;
	int utf8, sjis, euc;
	//int utf8ReadByte=0;
	//int utf8ReadPos=0;
	int utf8NextCheck = 0;
	int sjisNextCheck = 0;
	int eucNextCheck = 0;
	int utf8Bom = 0;

	Dprintf("\ncheck start--------------------\n");
	Dprintf("checkSize %d\n", readSize);
	utf8=1;
	sjis=1;
	euc=1;
	i=0;

	//bomcheck
	if( (unsigned char)*buf==0xFE && (unsigned char)*(buf+1)==0xFF)
	{
		//UTF16-BE
		encode = UTF16BE;

	}
	else if( (unsigned char)*buf==0xFF && (unsigned char)*(buf+1)==0xFE)
	{
		//UTF16-LE
		encode = UTF16LE;
	}
	else
	{
		if( (unsigned char)*buf==0xEF && (unsigned char)*(buf+1)==0xBB && (unsigned char)*(buf+2)==0xBF)
		{
			//UTF8N
			utf8Bom = 1;
		}
		//前の状態で文字コードが1の場合そのエンコードの可能性あり
		//エンコードが一つだけ1になるまで繰り返し
		//Dprintf("EncodeCheck\n");
		//最大4バイトを使用して文字コードを判断するため4バイト後が0ならあきらめる
		while(i < readSize && *(buf+i+4) != 0)
		{
			if( (unsigned char)*(buf+i) >= 0x80)
			{
				if( utf8 == 1)
				{
					//if( i == (utf8ReadPos + utf8ReadByte) )
					if( i >= utf8NextCheck)
					{
						int utf8ReadByte;
						utf8ReadByte = IsUtf8( (unsigned char*)(buf+i) );
						if( utf8ReadByte == 0)
							utf8 = 0;

						//utf8ReadPos = i;
						utf8NextCheck = i + utf8ReadByte;
						//Dprintf("i= %d, utf8ReadPos=%d utf8ReadByte=%d\n", i, utf8ReadPos, utf8ReadByte);
					}
				}

				if( sjis == 1 && i >= sjisNextCheck)
				{
					int sjisReadByte;
					sjisReadByte= IsSjis( (unsigned char*)(buf+i) );
					if( sjisReadByte == 0)
						sjis = 0;

					sjisNextCheck = i + sjisReadByte;
				}

				if( euc == 1 && i >= eucNextCheck)
				{
					int eucReadByte;
					eucReadByte = IsEucJp( (unsigned char*)(buf+i) );
					if( eucReadByte == 0)
						euc = 0;

					eucNextCheck = i + eucReadByte;
				}

				Dprintf("index=%d 0x%02x utf8 %d  sjis %d  euc %d\t", i, (unsigned char)*(buf+i), utf8, sjis, euc);
				unsigned char *disp = (unsigned char*)(buf+i);
				Dprintf("0x%02x 0x%02x 0x%02x 0x%02x\n", *disp, *(disp+1), *(disp+2), *(disp+3) );
				if( (utf8 + sjis + euc) == 1)
				{
					if( utf8 == 1)
					{
						if( utf8Bom == 1 )
							encode = UTF8;
						else
							encode = UTF8N;
					}
					if( sjis == 1)
						encode = SJIS;
					if( euc == 1)
						encode = EUCJP;
					break;
				}
				i++;
				Dprintf("\t");
				if(utf8 == 1) Dprintf("utf8 nextCheck = %d\t", utf8NextCheck);
				if(sjis == 1) Dprintf("sjis nextCheck = %d\t", sjisNextCheck);
				if(euc == 1) Dprintf("euc nextCheck = %d", eucNextCheck);
				Dprintf("\n");
			}
			else
			{
				//Dprintf("%d 0x%02x ascii\n", i, (unsigned char)*(buf+i));
				//Dprintf("%c", *(buf+i));
				i++;
				//utf8ReadPos=i;
			}
		}
	}

	return encode;
}

int IsUtf8(unsigned char *code)
{
	int fUtf8 = 0;
	if( 0xC2 <= *code && *code <= 0xF7)
	{
		if( *code <= 0xDF)
		{
			//2byte
			if( *(code+1) >= 0x80)
				fUtf8 = 2;
		}
		else if( *code <= 0xEF)
		{
			//3byte
			if( *(code+1)>=0x80 || *(code+2)>=0x80)
				fUtf8 = 3;
		}
		else
		{
			//4byte サロゲートペア
			if( *(code+1)>=0x80 || *(code+2)>=0x80 || *(code+3)>=0x80 )
				fUtf8 = 4;
		}
	}
	return fUtf8;
}

int IsSjis(unsigned char *code)
{
	int fSjis = 0;

	//0xA0-0xDF  0x81-9F,0xE0-0xFD 0x40-0xFE
	//半角カタカナを含めるとeucとすごく被るため判定を厳しくする
	//具体的には外字エリアは全てnotにする
	/*
		0x84C0 - 0x86FF
		0x87A0 - 0x888F
		0xEAA5 - 0xECFF
		0xEF40 - 0xF9FF
		0xFC50 - 0xFFFF
	*/

	if( 0xA0 <= *code && *code <= 0xDF)
	{
		//半角かな時は次のバイトがSJISの第一バイト or Asciiかどうかまで確認
		//if( *(code+1) < 0x80 ||
		//		(	(0x81 <= *(code+1) && *(code+1) <= 0x9F) || 
		//			(0xE0 <= *(code+1) && *(code+1) <= 0xFF) 
		//		)
		//	)
		{
			fSjis = 1;
		}
	}
	else if( 0x81 <= *code && *code <= 0x9F)
	{
		//0x84C0 - 0x86FF
		//0x87A0 - 0x888F
		//外字エリア
		if( (CompCharHex((unsigned char*)code, 0x84C0-1) == -1) &&
			(CompCharHex((unsigned char*)code, 0x86FF+1) == 1) )
		{
			Dprintf("外字エリア 0x84C0 - 0x86FF code 0x%x\n", *code);
		}
		else if( (CompCharHex((unsigned char*)code, 0x87A0-1) == -1) &&
			(CompCharHex((unsigned char*)code, 0x888F+1) == 1) )
		{
			Dprintf("外字エリア 0x87A0 - 0x888F code 0x%x\n", *code);
		}
		else
		{
			if( 0x40 <= *(code+1) && *(code+1) <= 0x7E)
				fSjis = 2;
			else if( 0x80 <= *(code+1) && *(code+1) <= 0xFC)
				fSjis = 2;
		}
	}
	else if( 0xE0 <= *code && *code <= 0xFF)
	{
		//0xEAA5 - 0xECFF
		//0xEF40 - 0xF9FF
		//0xFC50 - 0xFFFF
		//以上を使いたいのでスタートは-1をする
		if( (CompCharHex((unsigned char*)code, 0xEAA5-1) == -1) &&
			(CompCharHex((unsigned char*)code, 0xECFF+1) == 1)
			)
		{
			Dprintf("外字エリア 0xEAA5 - 0xECFF code 0x%x\n", *code);
		}
		else if( (CompCharHex((unsigned char*)code, 0xEF40-1) == -1) &&
			(CompCharHex((unsigned char*)code, 0xF9FF+1) == 1)
			)
		{
			Dprintf("外字エリア 0xEF40 - 0xF9FF code 0x%x\n", *code);
		}
		else if( (CompCharHex((unsigned char*)code, 0xFC50-1) == -1) )
			//&& (CompCharHex((unsigned char*)code, 0xFFFF+1) == 1) )
		{
			Dprintf("外字エリア 0xFC50 - 0xFFFF code 0x%x\n", *code);
		}
		else
		{
			if( 0x40 <= *(code+1) && *(code+1) <= 0x7E)
				fSjis = 2;
			else if( 0x80 <= *(code+1) && *(code+1) <= 0xFC)
				fSjis = 2;
		}
	}

	return fSjis;
}

int IsEucJp(unsigned char *code)
{
	int fEuc=0;
	
	//0xA1-0xFE 0xA1-0xFE と 0x8E 0xA0-0xDFを使用
	if( *code == 0x8E)
	{
		//半角カナ
		if( 0xA0 < *(code+1) && *(code+1) <= 0xDF)
			fEuc=2;
	}
	else if( 0xA1 <= *code && *code <= 0xFE)
	{
		if( 0xA0 <= *(code+1) && *(code+1) <= 0xFE)
			fEuc=2;
	}
	else if( *code == 0x8F)
	{
		//3byte
		if( 0xA1 <= *code && *code <= 0xFE)
		{
			if( 0xA0 <= *(code+1) && *(code+1) <= 0xFE)
			{
				Dprintf("euc-jp 3byte\n");
				fEuc=3;
			}
		}
	}
	return fEuc;
}

// code > comp  = -1;  code == comp = 0;  code < comp = 1;
int CompCharHex(unsigned char *code, unsigned long comp)
{
	//最大で4バイトまでしか扱わない為
	unsigned int byte[4];
	int compResult=0;
	int compByte;
	int i;
	int j;
	
	for(i=31; i>0; i--)
	{
		//Dprintf("0x%x\n", (long)(1<<i));
		if( (comp & (1 << i)) >= 1 )
			break;
	}
	//Dprintf("0x%x %d %d\n", comp, i, i/8);
	compByte = i/8;
	for(j=0; j<=compByte; j++)
	{
		byte[j] = ((comp>>j*8) & 0xFF);
		//Dprintf("j=%d 0x%02x\n",j, byte[j]);
	}

	//Dprintf("compByte %d code ", compByte+1);
	//for(i=0; i<=compByte; i++)
	//	Dprintf("0x%02X ", *(code+i) );
	//Dprintf("comp 0x%X ", comp);

	j=0;
	for(i=compByte; i>=0; i--)
	{
		//Dprintf("code 0x%02x, comp 0x%02x\n", *(code+j), byte[i]);
		if( *(code+j) != byte[i] )
		{
			if( *(code+j) > byte[i] )
			{
				compResult = -1;
				break;
			}
			else
			{
				compResult = 1;
				break;
			}
		}
		j++;
	}
	
	//switch(compResult)
	//{
	//case -1:
	//	Dprintf("result %d code>comp\n", compResult);
	//	break;
	//case 0:
	//	Dprintf("result %d code=comp\n", compResult);
	//	break;
	//case 1:
	//	Dprintf("result %d code<comp\n", compResult);
	//	break;
	//}
	
	return compResult;
}