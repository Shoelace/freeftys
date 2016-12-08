//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef DLLMAIN_H
#define DLLMAIN_H

#include <windows.h>
#include "PluginInterface.h"
#include "menuCmdID.h"

#include "MyDebug.h"

//npp.6.1.4.src\PowerEditor\src\resource.h
#define SCINTILLA_USER     (WM_USER + 2000)
//npp.6.1.4.src\PowerEditor\src\ScitillaComponent\ScintillaEditView.h
#define WM_DOOPEN				  	(SCINTILLA_USER + 8)

void pluginInit(HANDLE hModule);
void pluginTerminate();
void commandMenuInit();
void commandMenuCleanUp();
void setShortcutKey(ShortcutKey *sk, UCHAR key, bool isCtrl, bool isAlt, bool isShift);
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);
void aboutDlg();

#endif