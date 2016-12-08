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

#include "Encode.h"

unsigned int FileSize(FILE *fp)
{
	fpos_t fsize = -1;
	if( fseek(fp, 0, SEEK_END) == 0)
	{
		fgetpos(fp, &fsize);
	}
	fseek(fp, 0, SEEK_SET);
	return (unsigned int)fsize;
}

#include <windows.h>
#include <shobjidl.h>
#include <shlguid.h>
HRESULT ResolveShortCut(LPWSTR lpszLinkFile, LPWSTR lpszPath, size_t nPathSize)
{
	//http://msdn.microsoft.com/en-us/library/bb776891%28VS.85%29.aspx
	//本来TCHARが使われているのでUNICODEがコンパイラで設定されてなければcharで扱われるので注意!!

	HRESULT result;
	IShellLinkW *psl;
	WIN32_FIND_DATA wfd;

	//COM初期化
	CoInitialize(NULL);

	//COM(IShellLink)の作成
	result = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if( SUCCEEDED(result) )
	{
		//IPersistFileの作成
		IPersistFile *ppf;
		result = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if( SUCCEEDED(result) )
		{
			//ショートカットを読み込む
			result = ppf->Load(lpszLinkFile, STGM_READ);
			if( SUCCEEDED(result) )
			{
				//サンプルでは psl->Resolve(hwnd, 0); をやっているが
				//リンク先が消されていたり、名前が変更されているときに
				//通知するHWNDの登録を行っている今回は無くても構わないので削除した

				//ショートカット先の取得
				result = psl->GetPath(lpszPath, nPathSize, &wfd, SLGP_SHORTPATH);
			}
			ppf->Release();
		}
		psl->Release();		
	}
	//COMの解放
	CoUninitialize();
	return result;
}
