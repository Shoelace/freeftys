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

#ifndef NPPJPSELECTAREACUSTOMIZE_H
#define NPPJPSELECTAREACUSTOMIZE_H

#include "..\dllmain.h"

enum JpSelectAreaCustomizeSubMenu{
	JPSELECTAREACUTOMIZE = 20000,
	HTOZ, HKATATOZ, HALPHATOZ, HUPALPHATOZ, HLOALPHATOZ, HNUMTOZ, HSYMBOLTOZ, //SEPARATE2,
	ZTOH, ZKATATOH, ZALPHATOH, ZUPALPHATOH, ZLOALPHATOH, ZNUMTOH, ZSYMBOLTOH, //SEPARATE3,
	HITOKA, KATOHI
};

void NppWndProcSet();
void NppWndProcUnSet();
void CreateSubMenu();
void DestorySubMenu();
void onJpSelectAreaCustomizeBeNotified(SCNotification *notifyCode);

//従来のアクセス方法
//void leftCtrlShift();
//void leftCtrl();
//void rightCtrlShift();
//void rightCtrl();

void hanToZen();
void hanKataToZen();
void hanUpAlphaToZen();
void hanLoAlphaToZen();
void hanAlphaToZen();
void hanNumToZen();
void hanSymbolToZen();
void zenToHan();
void zenKataToHan();
void zenUpAlphaToHan();
void zenLoAlphaToHan();
void zenAlphaToHan();
void zenNumToHan();
void zenSymbolToHan();
void hiraToKata();
void kataToHira();


#endif