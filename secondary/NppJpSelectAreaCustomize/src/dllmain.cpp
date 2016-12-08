//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
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

#include "NppJpSelectAreaCustomize.h"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("Jp Select Area Customize");

const int nbFunc = MENU_COUNT;
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
		EndConsole();
        pluginTerminate();
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
	onJpSelectAreaCustomizeBeNotified(notifyCode);
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
	//float f;
	//int ii;
	//Ini::getInstance()->setIniPath(NULL);
	//Ini::getInstance()->writeDate(_T("TEST section"), _T("TEST key"), _T("TEST date"));
	//Ini::getInstance()->writeDate(_T("TEST section"), _T("TEST key1"), 10.5f);
	//Ini::getInstance()->writeDate(_T("TEST section"), _T("TEST key2"), 10);
	//Ini::getInstance()->readDate(_T("TEST section"), _T("TEST key1"), &f);
	//Ini::getInstance()->readDate(_T("TEST section"), _T("TEST key2"), &ii);
	//Dprintf("Ini i=%d  f=%f\n", ii, f);
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
	setCommand(PLUG_ABOUT, TEXT("About"), aboutDlg, NULL, false);
	//sk[PLUG_LEFTCSMOVE]._key = VK_LEFT; sk[PLUG_LEFTCSMOVE]._isCtrl = true; sk[PLUG_LEFTCSMOVE]._isAlt = false; sk[PLUG_LEFTCSMOVE]._isShift = false;

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
	
	////
	//setCommand(HTOZ, TEXT("半角->全角"), hanToZen, NULL, false);
	//setCommand(HKATATOZ, TEXT("半角カタカナ->全角"), hanKataToZen, NULL, false);
	//setCommand(HALPHATOZ, TEXT("半角アルファベット->全角"), hanAlphaToZen, NULL, false);
	//setCommand(HUPALPHATOZ, TEXT("半角アルファベット(大)->全角"), hanUpAlphaToZen, NULL, false);
	//setCommand(HLOALPHATOZ, TEXT("半角アルファベット(小)->全角"), hanLoAlphaToZen, NULL, false);
	//setCommand(HNUMTOZ, TEXT("半角数字->全角"), hanNumToZen, NULL, false);
	//setCommand(HSYMBOLTOZ, TEXT("半角記号->全角"), hanSymbolToZen, NULL, false);

	//setCommand(ZTOH, TEXT("全角->半角"), zenToHan, NULL, false); 
	//setCommand(ZKATATOH, TEXT("全角カタカナ->半角"), zenKataToHan, NULL, false);
	//setCommand(ZALPHATOH, TEXT("全角アルファベット->半角"), zenAlphaToHan, NULL, false);
	//setCommand(ZUPALPHATOH, TEXT("全角アルファベット(大)->半角"), zenUpAlphaToHan, NULL, false);
	//setCommand(ZLOALPHATOH, TEXT("全角アルファベット(小)->半角"), zenLoAlphaToHan, NULL, false);
	//setCommand(ZNUMTOH, TEXT("全角数字->半角"), zenNumToHan, NULL, false);
	//setCommand(ZSYMBOLTOH, TEXT("全角記号->半角"), zenSymbolToHan, NULL, false);

	//setCommand(HITOKA, TEXT("ひらがな->カタカナ"), hiraToKata, NULL, false);
	//setCommand(KATOHI, TEXT("カタカナ->ひらがな"), kataToHira, NULL, false);
	return;
}
void setShortcutKey(ShortcutKey *sk, UCHAR key, bool isCtrl, bool isAlt, bool isShift){
	sk->_key = key;
	sk->_isCtrl = isCtrl;
	sk->_isAlt = isAlt;
	sk->_isShift = isShift;
	return;
}
void commandMenuCleanUp()
{
	//Delete ShortcutKey
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
	::MessageBox(NULL, L"日本語の選択領域の変更+αプラグイン", L"日本語選択領域プラグイン", MB_OK);
	//::SendMessage(nppData._scintillaMainHandle, SCI_INDICSETALPHA, 29, 255);
	//::SendMessage(nppData._scintillaMainHandle, SCI_INDICSETOUTLINEALPHA, 29, 255);	
	//::SendMessage(nppData._scintillaMainHandle, SCI_INDICSETSTYLE, 29, INDIC_STRAIGHTBOX);
	//::SendMessage(nppData._scintillaMainHandle, SCI_INDICSETFORE, 29, 0xffffff);
	//::SendMessage(nppData._scintillaMainHandle, SCI_INDICSETUNDER, 29, false);
	//execute(SCI_INDICSETSTYLE, SCE_UNIVERSAL_FOUND_STYLE_SMART, INDIC_ROUNDBOX);
	//execute(SCI_INDICSETALPHA, SCE_UNIVERSAL_FOUND_STYLE_SMART, 100);
	//execute(SCI_INDICSETUNDER, SCE_UNIVERSAL_FOUND_STYLE_SMART, true);
}
//void test(){
//	::MessageBox(NULL, L"test", L"test", MB_OK);
//}
