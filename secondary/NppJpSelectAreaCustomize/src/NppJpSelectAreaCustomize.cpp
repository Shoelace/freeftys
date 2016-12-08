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

#include "NppJpSelectAreaCustomize.h"
//#include "Ini.h"
#include "Selecting.h"

extern const TCHAR NPP_PLUGIN_NAME[];

extern NppData nppData;
extern FuncItem funcItem[];

Selecting selecting;

//サブメニュー作成用
WNDPROC OldNppWndProc;
LRESULT CALLBACK NewNppWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
HMENU g_SubMenu;

//scintillaサブクラス化用
////高速アクセス用に分ける
////本来は分けなくてもいいが高速アクセスするときにウィンドウごとのsptr_tが必要になるためif文削除用に分ける
////main
//WNDPROC OldScintillaMainWndProc;
//LRESULT CALLBACK NewScintillaMainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
////sub
//WNDPROC OldScintillaSubWndProc;
//LRESULT CALLBACK NewScintillaSubWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
WNDPROC OldScintillaWndProc;
LRESULT CALLBACK NewScintillaWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
SciFnDirect pSciMsg;
sptr_t pSciMainWndData;
sptr_t pSciSubWndData;

void NppWndProcSet()
{
	OldNppWndProc = (WNDPROC)SetWindowLongPtr(nppData._nppHandle, GWLP_WNDPROC, (LONG)NewNppWndProc);
	OldScintillaWndProc = (WNDPROC)SetWindowLongPtr(nppData._scintillaMainHandle, GWLP_WNDPROC, (LONG)NewScintillaWndProc);
	OldScintillaWndProc = (WNDPROC)SetWindowLongPtr(nppData._scintillaSecondHandle, GWLP_WNDPROC, (LONG)NewScintillaWndProc);
	//高速にscintillaにアクセス
	pSciMsg = (SciFnDirect)SendMessage(nppData._scintillaMainHandle, SCI_GETDIRECTFUNCTION, 0, 0);
	pSciMainWndData = (sptr_t)SendMessage(nppData._scintillaMainHandle, SCI_GETDIRECTPOINTER, 0, 0);
	pSciSubWndData = (sptr_t)SendMessage(nppData._scintillaSecondHandle, SCI_GETDIRECTPOINTER, 0, 0);
	return;
}
void NppWndProcUnSet()
{
	SetWindowLongPtr(nppData._nppHandle, GWLP_WNDPROC, (LONG_PTR)OldNppWndProc);
	SetWindowLongPtr(nppData._scintillaMainHandle, GWLP_WNDPROC, (LONG_PTR)OldScintillaWndProc);
	SetWindowLongPtr(nppData._scintillaSecondHandle, GWLP_WNDPROC, (LONG_PTR)OldScintillaWndProc);
	return;
}
LRESULT CALLBACK NewNppWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_COMMAND:
		//Dprintf("wm_command\n");
		switch(LOWORD(wParam ))
		{
		case HTOZ:			hanToZen();			 return TRUE;
		case HKATATOZ:		hanKataToZen();		 return TRUE;
		case HALPHATOZ:		hanAlphaToZen();	 return TRUE;
		case HUPALPHATOZ:	hanUpAlphaToZen();	 return TRUE;
		case HLOALPHATOZ:	hanLoAlphaToZen();	 return TRUE;
		case HNUMTOZ:		hanNumToZen();		 return TRUE;
		case HSYMBOLTOZ:	hanSymbolToZen();	 return TRUE;
		case ZTOH:			zenToHan ();		 return TRUE;
		case ZKATATOH:		zenKataToHan();		 return TRUE;
		case ZALPHATOH:		zenAlphaToHan();	 return TRUE;
		case ZUPALPHATOH:	zenUpAlphaToHan();	 return TRUE;
		case ZLOALPHATOH:	zenLoAlphaToHan();	 return TRUE;
		case ZNUMTOH:		zenNumToHan();		 return TRUE;
		case ZSYMBOLTOH:	zenSymbolToHan();	 return TRUE;
		case HITOKA:		hiraToKata();		 return TRUE;
		case KATOHI:		kataToHira();		 return TRUE;
		}
		break;
	}
	return CallWindowProc(OldNppWndProc, hwnd, uMsg, wParam, lParam);
}
void CreateSubMenu()
{
	g_SubMenu = CreateMenu();
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HTOZ, TEXT("半角->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HKATATOZ, TEXT("半角カタカナ->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HALPHATOZ, TEXT("半角アルファベット->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HUPALPHATOZ, TEXT("半角アルファベット(大)->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HLOALPHATOZ, TEXT("半角アルファベット(小)->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HNUMTOZ, TEXT("半角数字->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HSYMBOLTOZ, TEXT("半角記号->全角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, MF_SEPARATOR, NULL);
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZTOH, TEXT("全角->半角")); 
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZKATATOH, TEXT("全角カタカナ->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZALPHATOH, TEXT("全角アルファベット->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZUPALPHATOH, TEXT("全角アルファベット(大)->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZLOALPHATOH, TEXT("全角アルファベット(小)->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZNUMTOH, TEXT("全角数字->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, ZSYMBOLTOH, TEXT("全角記号->半角"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, MF_SEPARATOR, NULL);
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, HITOKA, TEXT("ひらがな->カタカナ"));
	InsertMenu(g_SubMenu, -1, MF_BYPOSITION, KATOHI, TEXT("カタカナ->ひらがな"));

	InsertMenu( GetMenu(nppData._nppHandle), funcItem[PLUG_ABOUT]._cmdID, MF_BYCOMMAND | MF_POPUP, (UINT_PTR)g_SubMenu, L"サブメニュー");
}
void DestorySubMenu()
{
	if( g_SubMenu != NULL)
		DestroyMenu( g_SubMenu );
}
LRESULT CALLBACK NewScintillaWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//WM_LBUTTONDOWN -> WM_LBUTTONUP -> WM_LBUTTONDOWN ->(DBLCLICK判定 true WM_LBUTTONDBLCLK) -> WM_LBUTTONUP
	
	sptr_t targetHwnd = NULL;

	switch(uMsg)
	{
	//case WM_LBUTTONUP:
	//	Dprintf("LbuttonUp\n\n");
	//	break;
	//case WM_LBUTTONDBLCLK:
	//	Dprintf("LbuttonDBL\n");
	//	break;
	case WM_KEYDOWN:
		if( hwnd == nppData._scintillaMainHandle)
		{
			targetHwnd = pSciMainWndData;
			//Dprintf("main\n");
		}
		else if( hwnd == nppData._scintillaSecondHandle)
		{
			targetHwnd = pSciSubWndData;
			//Dprintf("sub\n");
		}
		if( targetHwnd != NULL)
		{
			switch(wParam)
			{
			case VK_LEFT:
				//Dprintf("left key\n");
				if( GetKeyState(VK_CONTROL) < 0 )
				{
					if( GetKeyState(VK_SHIFT) < 0)
						selecting.Left(pSciMsg, targetHwnd, true);
					else
						selecting.Left(pSciMsg, targetHwnd, false);
					return TRUE;
				}
				break;
			case VK_RIGHT:
				//Dprintf("right key\n");
				if( GetKeyState(VK_CONTROL) < 0 )
				{
					//Dprintf("onCtrl\n");
					if( GetKeyState(VK_SHIFT) < 0)
						selecting.Right(pSciMsg, targetHwnd, true);
					else
						selecting.Right(pSciMsg, targetHwnd, false);
					//if( GetKeyState(VK_SHIFT) < 0)
					//	selecting.Right(true);
					//else
					//	selecting.Right(false);

					return TRUE;
				}
				break;
			//default:
			//	Dprintf("key %d\n", wParam);
			//	break;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		if( hwnd == nppData._scintillaMainHandle)
		{
			targetHwnd = pSciMainWndData;
			//Dprintf("main\n");
		}
		else if( hwnd == nppData._scintillaSecondHandle)
		{
			targetHwnd = pSciSubWndData;
			//Dprintf("sub\n");
		}
		if( targetHwnd != NULL)
		{
			static LONG lastMouseDownTime;
			static POINT lastClickPt;
			LONG messageTime;
			int x, y;
			bool doubleClick = false;
			//scintillaでは3dot以内ならOKにしてるのでマージンを取って4に
			const int dblClickDistance = 4;

			messageTime = GetMessageTime();
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			if( (unsigned int)(messageTime - lastMouseDownTime) < GetDoubleClickTime() )
			{
				if( (abs(lastClickPt.x - x) < dblClickDistance) && (abs(lastClickPt.y - y) < dblClickDistance) )
					doubleClick = true;
			}

			//今回のものをlastへ
			lastMouseDownTime = messageTime;
			lastClickPt.x = x;
			lastClickPt.y = y;

			if( doubleClick == true)
			{
				int curPos;

				////URLダブルクリックの有効化箇所、パフォーマンスが落ちそうなのでコメントアウトしておく
				//LRESULT result;
				//result = CallWindowProc(OldScintillaWndProc, hwnd, uMsg, wParam, lParam);
				//Dprintf("result %d\n", result);

				Dprintf("LbuttonDBL\n");
				//curPos = SendMessage(hwnd, SCI_POSITIONFROMPOINTCLOSE, x, y);
				//内部でSCI_POSITIONFROMPOINTCLOSEではなくSCI_CHARPOSITIONFROMPOINTと同等の呼び方をしていたので変更
				curPos = pSciMsg(targetHwnd, SCI_CHARPOSITIONFROMPOINT, x, y);
				Dprintf("curPos %d x %d y %d\n", curPos, x, y);
				if( curPos != -1 )
				{
					//selecting.DBLClick(hwnd, curPos);
					selecting.DBLClick(pSciMsg, targetHwnd, curPos);
					return TRUE;
				}
			}
			//Dprintf("LbuttonDown\n");
			break;
		}
	}
	return CallWindowProc(OldScintillaWndProc, hwnd, uMsg, wParam, lParam);
}
void onJpSelectAreaCustomizeBeNotified(SCNotification *notifyCode)
{	
	switch(notifyCode->nmhdr.code){
		case NPPN_READY:
			selecting.Init(nppData);
			NppWndProcSet();
			CreateSubMenu();
			break;

		//case SCN_DOUBLECLICK:
		//	//-1は文字以外の所をクリック
		//	Dprintf("SCN_DOUBLECLICK\n");
		//	//if( notifyCode->position != -1) {
		//	//	selecting.DBLClick((HWND)notifyCode->nmhdr.hwndFrom , notifyCode->position);
		//	//}
		//	break;
		case NPPN_SHUTDOWN:
			NppWndProcUnSet();
			break;
		default:
			break;
	}
}

//従来のアクセス方法
//void leftCtrlShift(){ 
//	selecting.Left(true);
//	return;
//}
//void leftCtrl(){
//	selecting.Left(false);
//	return;
//}
//void rightCtrlShift(){ return selecting.Right(true);}
//void rightCtrl(){ return selecting.Right(false);}
//
void hanToZen(){ return selecting.ZenToHan(selecting.TOFULL);}
void hanKataToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHKata);}
void hanUpAlphaToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHUpAlpha);}
void hanLoAlphaToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHLoAlpha);}
void hanAlphaToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHLoAlpha | selecting.ZHUpAlpha);}
void hanNumToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHNum);}
void hanSymbolToZen(){ return selecting.ZenToHan(selecting.TOFULL, selecting.ZHSymbol);}

void zenToHan(){ return selecting.ZenToHan(selecting.TOHALF);}
void zenKataToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHKata);}
void zenUpAlphaToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHUpAlpha);}
void zenLoAlphaToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHLoAlpha);}
void zenAlphaToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHLoAlpha | selecting.ZHUpAlpha);}
void zenNumToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHNum);}
void zenSymbolToHan(){ return selecting.ZenToHan(selecting.TOHALF, selecting.ZHSymbol);}

void hiraToKata(){ return selecting.HiraToKata(selecting.TOKATA);}
void kataToHira(){ return selecting.HiraToKata(selecting.TOHALF);}