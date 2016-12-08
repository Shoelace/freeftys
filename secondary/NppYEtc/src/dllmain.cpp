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

#include "dllmain.h"
#include "NppYEtc.h"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("YEtc");
enum { 
	ABOUT, 
	SEPARATE1, PREVFOLD, PREVFOLDALT, NEXTFOLD, NEXTFOLDALT, SEPARATE2, INSERTTODAY,
	MENUCOUNT
};

const int nbFunc = MENUCOUNT;
FuncItem funcItem[nbFunc];
ShortcutKey sk[nbFunc];

NppData nppData;


BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			StartConsole();
			pluginInit(hinstDll);
			break;

		case DLL_PROCESS_DETACH:
			pluginTerminate();
			EndConsole();
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
	nppData = notpadPlusData;
	YEtcSetInfo(&nppData);
	return;
}
extern "C" __declspec(dllexport) const TCHAR * getName()
{
	return NPP_PLUGIN_NAME;
}
extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
	*nbF = nbFunc;
	return funcItem;
}
extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
	return ;
}
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return TRUE;
}
#endif

void pluginInit(HANDLE hModule)
{
	commandMenuInit();
	return;
}
void pluginTerminate()
{
	commandMenuCleanUp();
	return;
}
void commandMenuInit()
{
    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
	setCommand(ABOUT, TEXT("About"), aboutDlg, NULL, false);
	
	//[キー
	setShortcutKey(&sk[PREVFOLD], VK_OEM_4, true, false, false);
	setCommand(PREVFOLD, TEXT("PrevFold"), PrevFold, &sk[PREVFOLD], false);
	setShortcutKey(&sk[PREVFOLDALT], VK_OEM_4, true, true, false);
	setCommand(PREVFOLDALT, TEXT("PrevFoldAlt"), PrevFoldAlt, &sk[PREVFOLDALT], false);
	
	//]キー
	setShortcutKey(&sk[NEXTFOLD], VK_OEM_6, true, false, false);
	setCommand(NEXTFOLD, TEXT("NextFold"), NextFold, &sk[NEXTFOLD], false);
	setShortcutKey(&sk[NEXTFOLDALT], VK_OEM_6, true, true, false);
	setCommand(NEXTFOLDALT, TEXT("NextFoldAlt"), NextFoldAlt, &sk[NEXTFOLDALT], false);

	//Shift + F5
	setShortcutKey(&sk[INSERTTODAY], VK_F5, false, false, true);
	setCommand(INSERTTODAY, TEXT("InsertToday"), InsertToday, &sk[INSERTTODAY], false);
	return;
}
void commandMenuCleanUp()
{
	//Delete ShortcutKey
	return;
}
void setShortcutKey(ShortcutKey *sk, UCHAR key, bool isCtrl, bool isAlt, bool isShift){
	sk->_key = key;
	sk->_isCtrl = isCtrl;
	sk->_isAlt = isAlt;
	sk->_isShift = isShift;
	return;
}
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}
void aboutDlg()
{
	::MessageBox(NULL, TEXT("適当機能詰め\n何かあったら freesftys@yahoo.co.jp まで"), TEXT("y-util"), MB_OK);
}
