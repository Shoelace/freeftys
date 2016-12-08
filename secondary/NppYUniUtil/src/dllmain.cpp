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

//#include "..\..\NppDetectEncoding\src\NppDetectEncoding.h"
//#include "..\..\NppHorizontalRuler\src\NppHorizontalRuler.h"
//#include "..\..\NppJpSelectAreaCustomize\src\NppJpSelectAreaCustomize.h"
//#include "..\..\NppYEtc\src\NppYEtc.h"
//#include "..\..\NppDynamicFonts\src\NppDynamicFonts.h"

#include "NppDetectEncoding\NppDetectEncoding.h"
#include "NppHorizontalRuler\NppHorizontalRuler.h"
#include "NppJpSelectAreaCustomize\NppJpSelectAreaCustomize.h"
#include "NppYEtc\NppYEtc.h"
#include "NppDynamicFonts\NppDynamicFonts.h"
#include "resource.h"


HINSTANCE g_DllhInst;

const TCHAR NPP_PLUGIN_NAME[] = TEXT("NppYUniUtil");
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
	onDynamicFontsBeNotified(notifyCode);
	onJpSelectAreaCustomizeBeNotified(notifyCode);
	onHorizontalRulerBeNotified(notifyCode);
	onDetectEncodingBeNotified(notifyCode);
	return ;
}
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = TRUE;
	result = onHorizontalRulerMessageProc(Message, wParam, lParam);

	return result;
}
#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
	return TRUE;
}
#endif

void pluginInit(HANDLE hModule)
{
	g_DllhInst = (HINSTANCE)hModule;
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
	//sk[PLUG_LEFTCSMOVE]._key = VK_LEFT; sk[PLUG_LEFTCSMOVE]._isCtrl = true; sk[PLUG_LEFTCSMOVE]._isAlt = false; sk[PLUG_LEFTCSMOVE]._isShift = false;

//YUtil
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
	
//JpSelectAreaCustomize
	////Ctrl+Left
	//setShortcutKey(&sk[PLUG_LEFT_C], VK_LEFT, true, false, false);
	//setCommand(PLUG_LEFT_C, TEXT("divide left move"), leftCtrl, &sk[PLUG_LEFT_C], false);
	////Ctrl+Shift+Left
	//setShortcutKey(&sk[PLUG_LEFT_C_S], VK_LEFT, true, false, true);
	//setCommand(PLUG_LEFT_C_S, TEXT("divide left select move"), leftCtrlShift, &sk[PLUG_LEFT_C_S], false);
	////Ctrl+Right
	//setShortcutKey(&sk[PLUG_RIGHT_C], VK_RIGHT, true, false, false);
	//setCommand(PLUG_RIGHT_C, TEXT("divide right move"), rightCtrl, &sk[PLUG_RIGHT_C], false);
	////Ctrl+Shift+Right
	//setShortcutKey(&sk[PLUG_RIGHT_C_S], VK_RIGHT, true, false, true);
	//setCommand(PLUG_RIGHT_C_S, TEXT("divide right select move"), rightCtrlShift, &sk[PLUG_RIGHT_C_S], false);
	////半->全
	//setCommand(HTOZ, TEXT("半角->全角"), hanToZen, NULL, false);
	//setCommand(HKATATOZ, TEXT("半角カタカナ->全角"), hanKataToZen, NULL, false);
	//setCommand(HALPHATOZ, TEXT("半角アルファベット->全角"), hanAlphaToZen, NULL, false);
	//setCommand(HUPALPHATOZ, TEXT("半角アルファベット(大)->全角"), hanUpAlphaToZen, NULL, false);
	//setCommand(HLOALPHATOZ, TEXT("半角アルファベット(小)->全角"), hanLoAlphaToZen, NULL, false);
	//setCommand(HNUMTOZ, TEXT("半角数字->全角"), hanNumToZen, NULL, false);
	//setCommand(HSYMBOLTOZ, TEXT("半角記号->全角"), hanSymbolToZen, NULL, false);
	////全->半
	//setCommand(ZTOH, TEXT("全角->半角"), zenToHan, NULL, false); 
	//setCommand(ZKATATOH, TEXT("全角カタカナ->半角"), zenKataToHan, NULL, false);
	//setCommand(ZALPHATOH, TEXT("全角アルファベット->半角"), zenAlphaToHan, NULL, false);
	//setCommand(ZUPALPHATOH, TEXT("全角アルファベット(大)->半角"), zenUpAlphaToHan, NULL, false);
	//setCommand(ZLOALPHATOH, TEXT("全角アルファベット(小)->半角"), zenLoAlphaToHan, NULL, false);
	//setCommand(ZNUMTOH, TEXT("全角数字->半角"), zenNumToHan, NULL, false);
	//setCommand(ZSYMBOLTOH, TEXT("全角記号->半角"), zenSymbolToHan, NULL, false);
	////ひらがな、カタカナ
	//setCommand(HITOKA, TEXT("ひらがな->カタカナ"), hiraToKata, NULL, false);
	//setCommand(KATOHI, TEXT("カタカナ->ひらがな"), kataToHira, NULL, false);
	
//HorizonRuler
	setCommand(RULERTOGGLE, TEXT("RulerToggle"), RulerToggle, NULL, false);
	setCommand(RULERVISIBLE, TEXT("RulerVisible"), RulerVisible, NULL, false);
	setCommand(RULEROPTION, TEXT("RulerOption"), RulerOption, NULL, false);

//JpDetectEncoding
	setCommand(OPEN_SJIS, TEXT("SJISで開く"), OpenSjis, NULL, false);
	setCommand(OPEN_EUCJP, TEXT("EUC-JPで開く"), OpenEucjp, NULL, false);
	setCommand(EUC2SJIS, TEXT("EUC-JPをSJISにする"), EucjpToSjis, NULL, false);
	setCommand(SJIS2EUC, TEXT("SJISをEUC-JPにする"), SjisToEucjp, NULL, false);
	setCommand(DETECTENCODEOPTION, TEXT("DetectEncodeOption"), DetectEncodeOption, NULL, false);

//DynamicFonts
	setCommand(SELECTFONT, TEXT("Select Font"), SelectFont, NULL, false);
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
	::MessageBox(NULL, TEXT("UnionPlugin freesftys@yahoo.co.jp"), TEXT("Y-UnionPlugin"), MB_OK);
}


