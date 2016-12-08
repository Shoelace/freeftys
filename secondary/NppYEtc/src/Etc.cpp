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

#include "Etc.h"


void Etc::Init(NppData *nppData)
{
	this->nppHwnd = nppData->_nppHandle;
	this->mainHwnd = nppData->_scintillaMainHandle;
	this->subHwnd = nppData->_scintillaSecondHandle;
}
void Etc::PrevFold(bool alt)
{
	int curPos;
	int curLine;
	int foldLevel;

	HWND scintillaHwnd;
	int currentScintilla;
	//現在のscintillaの取得 0->main 1->sub
	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		scintillaHwnd = this->mainHwnd;
	else
		scintillaHwnd = this->subHwnd;

	curPos = ::SendMessage(scintillaHwnd, SCI_GETCURRENTPOS , 0, 0);
	curLine = ::SendMessage(scintillaHwnd, SCI_LINEFROMPOSITION , curPos, 0);
	foldLevel = ::SendMessage(scintillaHwnd, SCI_GETFOLDLEVEL, curLine, 0) & SC_FOLDLEVELNUMBERMASK;
	if(alt == false)
	{
		int prevLine;

		prevLine = ::SendMessage(scintillaHwnd, SCI_GETFOLDPARENT, curLine, 0);
		::SendMessage(scintillaHwnd, SCI_GOTOLINE, prevLine, 0);
	}
	else
	{
		int i;
		for(i=curLine-1; i>=0; i--)
		{
			if( (::SendMessage(scintillaHwnd, SCI_GETFOLDLEVEL, i, 0) & SC_FOLDLEVELNUMBERMASK) != foldLevel)
				break;
		}
		::SendMessage(scintillaHwnd, SCI_GOTOLINE, i, 0);
	}
	return;
}

void Etc::NextFold(bool alt)
{
	int curPos;
	int curLine;
	int foldLevel;

	HWND scintillaHwnd;
	int currentScintilla;
	//現在のscintillaの取得 0->main 1->sub
	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		scintillaHwnd = this->mainHwnd;
	else
		scintillaHwnd = this->subHwnd;

	curPos = ::SendMessage(scintillaHwnd, SCI_GETCURRENTPOS , 0, 0);
	curLine = ::SendMessage(scintillaHwnd, SCI_LINEFROMPOSITION , curPos, 0);
	foldLevel = ::SendMessage(scintillaHwnd, SCI_GETFOLDLEVEL, curLine, 0) & SC_FOLDLEVELNUMBERMASK;
	if(alt == false)
	{
		int nextLine;

		nextLine = ::SendMessage(scintillaHwnd, SCI_GETLASTCHILD, curLine, foldLevel);
		if( nextLine == curLine)
			nextLine = ::SendMessage(scintillaHwnd, SCI_GETLASTCHILD, curLine, foldLevel-1);
		::SendMessage(scintillaHwnd, SCI_GOTOLINE, nextLine, 0);
	}
	else
	{
		int line;
		int i;

		line = ::SendMessage(scintillaHwnd, SCI_GETLINECOUNT, 0, 0);
		for(i=curLine+1; i<=line; i++)
		{
			if( (::SendMessage(scintillaHwnd, SCI_GETFOLDLEVEL, i, 0) & SC_FOLDLEVELNUMBERMASK) != foldLevel)
				break;
		}
		::SendMessage(scintillaHwnd, SCI_GOTOLINE, i, 0);
	}
	return;
}
void Etc::InsertToday()
{
	//int curPos;
	SYSTEMTIME time;
	char insertTime[MAX_PATH];
	int len;


	HWND scintillaHwnd;
	int currentScintilla;
	//現在のscintillaの取得 0->main 1->sub
	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		scintillaHwnd = this->mainHwnd;
	else
		scintillaHwnd = this->subHwnd;
	//curPos = ::SendMessage(scintillaHwnd, SCI_GETCURRENTPOS , 0, 0);

	GetLocalTime(&time);
	sprintf_s(insertTime, MAX_PATH, "%04d/%02d/%02d %02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute);
	len = strlen(insertTime);
	//::SendMessage(scintillaHwnd, SCI_INSERTTEXT, -1, (LPARAM)&insertTime);
	::SendMessage(scintillaHwnd, SCI_ADDTEXT, len, (LPARAM)&insertTime);

	return;
}