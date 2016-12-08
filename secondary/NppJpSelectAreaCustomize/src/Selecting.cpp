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

#include "MyDebug.h"
#include "Selecting.h"

enum FSyllabary{
	/*
	FDHYPHEN	= 0xE382A0,	//゠	0x0000	0x0000	0x0000		0x30A0	0xE382A0
	*/
	FKLA		= 0xE382A1,	//ァ
	FKA			= 0xE382A2,	//ア
	FKLI		= 0xE382A3,	//ィ
	FKI			= 0xE382A4,	//イ
	FKLU		= 0xE382A5,	//ゥ
	FKU			= 0xE382A6,	//ウ
	FKLE		= 0xE382A7,	//ェ
	FKE			= 0xE382A8,	//エ
	FKLO		= 0xE382A9,	//ォ
	FKO			= 0xE382AA,	//オ
	FKKA		= 0xE382AB,	//カ
	FKGA		= 0xE382AC,	//ガ
	FKKI		= 0xE382AD,	//キ
	FKGI		= 0xE382AE,	//ギ
	FKKU		= 0xE382AF,	//ク
	FKGU		= 0xE382B0,	//グ
	FKKE		= 0xE382B1,	//ケ
	FKGE		= 0xE382B2,	//ゲ
	FKKO		= 0xE382B3,	//コ
	FKGO		= 0xE382B4,	//ゴ
	FKSA		= 0xE382B5,	//サ
	FKZA		= 0xE382B6,	//ザ
	FKSI		= 0xE382B7,	//シ
	FKZI		= 0xE382B8,	//ジ
	FKSU		= 0xE382B9,	//ス
	FKZU		= 0xE382BA,	//ズ
	FKSE		= 0xE382BB,	//セ
	FKZE		= 0xE382BC,	//ゼ
	FKSO		= 0xE382BD,	//ソ
	FKZO		= 0xE382BE,	//ゾ
	FKTA		= 0xE382BF,	//タ
	FKDA		= 0xE38380,	//ダ
	FKTI		= 0xE38381,	//チ
	FKDI		= 0xE38382,	//ヂ
	FKLTU		= 0xE38383,	//ッ
	FKTU		= 0xE38384,	//ツ
	FKDU		= 0xE38385,	//ヅ
	FKTE		= 0xE38386,	//テ
	FKDE		= 0xE38387,	//デ
	FKTO		= 0xE38388,	//ト
	FKDO		= 0xE38389,	//ド
	FKNA		= 0xE3838A,	//ナ
	FKNI		= 0xE3838B,	//ニ
	FKNU		= 0xE3838C,	//ヌ
	FKNE		= 0xE3838D,	//ネ
	FKNO		= 0xE3838E,	//ノ
	FKHA		= 0xE3838F,	//ハ
	FKBA		= 0xE38390,	//バ
	FKPA		= 0xE38391,	//パ
	FKHI		= 0xE38392,	//ヒ
	FKBI		= 0xE38393,	//ビ
	FKPI		= 0xE38394,	//ピ
	FKHU		= 0xE38395,	//フ
	FKBU		= 0xE38396,	//ブ
	FKPU		= 0xE38397,	//プ
	FKHE		= 0xE38398,	//ヘ
	FKBE		= 0xE38399,	//ベ
	FKPE		= 0xE3839A,	//ペ
	FKHO		= 0xE3839B,	//ホ
	FKBO		= 0xE3839C,	//ボ
	FKPO		= 0xE3839D,	//ポ
	FKMA		= 0xE3839E,	//マ
	FKMI		= 0xE3839F,	//ミ
	FKMU		= 0xE383A0,	//ム
	FKME		= 0xE383A1,	//メ
	FKMO		= 0xE383A2,	//モ
	FKLYA		= 0xE383A3,	//ャ
	FKYA		= 0xE383A4,	//ヤ
	FKLYU		= 0xE383A5,	//ュ
	FKYU		= 0xE383A6,	//ユ
	FKLYO		= 0xE383A7,	//ョ
	FKYO		= 0xE383A8,	//ヨ
	FKRA		= 0xE383A9,	//ラ
	FKRI		= 0xE383AA,	//リ
	FKRU		= 0xE383AB,	//ル
	FKRE		= 0xE383AC,	//レ
	FKRO		= 0xE383AD,	//ロ
	FKLWA		= 0xE383AE,	//ヮ
	FKWA		= 0xE383AF,	//ワ
	FKWI		= 0xE383B0,	//ヰ
	FKWE		= 0xE383B1,	//ヱ
	FKWO		= 0xE383B2,	//ヲ
	FKN			= 0xE383B3,	//ン
	FKVU		= 0xE383B4,	//ヴ
	FKLKA		= 0xE383B5,	//ヵ
	FKLKE		= 0xE383B6,	//ヶ
	FKVA		= 0xE383B7,	//ヷ
	FKVI		= 0xE383B8,	//ヸ
	FKVE		= 0xE383B9,	//ヹ
	FKVO		= 0xE383BA,	//ヺ
	/*
	FMDOT		= 0xE383BB,	//・	0x2126	0xA1A6	0x8145		0x30FB	0xE383BB
	FLONGSOUND	= 0xE383BC,	//ー	0x213C	0xA1BC	0x815B		0x30FC	0xE383BC
	FKICHI		= 0xE383BD,	//ヽ	0x2133	0xA1B3	0x8152		0x30FD	0xE383BD
	FKICHID		= 0xE383BE,	//ヾ	0x2134	0xA1B4	0x8153		0x30FE	0xE383BE
	FKOTO		= 0xE383BF,	//ヿ	0x0000	0x0000	0x0000		0x30FF	0xE383BF
	*/
	FSyllabaryStart = FKLA,
	FSyllabaryEnd	= FKVO
};
enum FSymbol{
	FSPACE		= 0xE38080,	//　
	FICOMMA		= 0xE38081,	//、
	FISTOP		= 0xE38082,	//。
	FCOMMA		= 0xEFBC8C,	//，
	FSTOP		= 0xEFBC8E,	//．
	FMDOT		= 0xE383BB,	//・ //UTF カタカナ
	FCOLON		= 0xEFBC9A,	//：
	FSCOLON		= 0xEFBC9B,	//；
	FQUES		= 0xEFBC9F,	//？
	FEXCLA		= 0xEFBC81,	//！
	FDAKU		= 0xE3829B,	//゛ //UTF ひらがな
	FHANDAKU	= 0xE3829C,	//゜ //UTF ひらがな
	FCIRCUM		= 0xEFBCBE,	//＾
	FLOW		= 0xEFBCBF,	//＿
	FKICHI		= 0xE383BD,	//ヽ //UTF カタカナ
	FKICHID		= 0xE383BE,	//ヾ //UTF カタカナ
	FHICHI		= 0xE3829D,	//ゝ //UTF ひらがな
	FHICHID		= 0xE3829E,	//ゞ //UTF ひらがな
	FLONGSOUND	= 0xE383BC,	//ー //UTF カタカナ
	FSOLIDUS	= 0xEFBC8F,	//／
	FTILDE		= 0xEFBD9E,	//～
	FVER		= 0xEFBD9C,	//｜
	FLSQUO		= 0xE28098,	//‘
	FRSQUO		= 0xE28099,	//’
	FLDQUO		= 0xE2809D,	//”
	FLPAREN		= 0xEFBC88,	//（
	FRPAREN		= 0xEFBC89,	//）
	FLSQUARE	= 0xEFBCBB,	//［
	FRSQUARE	= 0xEFBCBD,	//］
	FLCURLY		= 0xEFBD9B,	//｛
	FRCURLY		= 0xEFBD9D,	//｝
	FLCORNER	= 0xE3808C,	//「
	FRCORNER	= 0xE3808D,	//」
	FPLUS		= 0xEFBC8B,	//＋
	FHYPHEN		= 0xEFFC8D,	//－
	FEQUALS		= 0xEFBC9D,	//＝
	FLTHAN		= 0xEFBC9C,	//＜
	FGTHAN		= 0xEFBC9E,	//＞
	FYEN		= 0xEFBFA5,	//￥
	FDOLL		= 0xEFBC84,	//＄
	FPERCENT	= 0xEFBC85,	//％
	FNUMBER		= 0xEFBC83,	//＃
	FAMPERSAND	= 0xEFBC86,	//＆
	FASTERISK	= 0xEFBC8A,	//＊
	FAT			= 0xEFBCA0,	//＠
	FRARROW		= 0xE28692,	//→
	FLARROW		= 0xE28690,	//←
	FUARROW		= 0xE28691,	//↑
	FDARROW		= 0xE28693,	//↓
	FYORI		= 0xE3829F,	//ヿ //UTF ひらがな
	FDHYPHEN	= 0xE382A0,	//゠ //UTF カタカナ
	FKOTO		= 0xE383BF	//ゟ //UTF カタカナ
};

enum HSyllabary{
	/*
	HISTOP		= 0xEFBDA1,	//｡		0x21		0xA1		0x8EA1		0xFF61		0xEFBDA1
	HLCORNER	= 0xEFBDA2,	//｢		0x22		0xA2		0x8EA2		0xFF62		0xEFBDA2
	HRCORNER	= 0xEFBDA3,	//｣		0x23		0xA3		0x8EA3		0xFF63		0xEFBDA3
	HICOMMA		= 0xEFBDA4,	//､		0x24		0xA4		0x8EA4		0xFF64		0xEFBDA4
	HMDOT		= 0xEFBDA5,	//･		0x25		0xA5		0x8EA5		0xFF65		0xEFBDA5
	*/
	HKWO		= 0xEFBDA6,	//ｦ
	HKLA		= 0xEFBDA7,	//ｧ
	HKLI		= 0xEFBDA8,	//ｨ
	HKLU		= 0xEFBDA9,	//ｩ
	HKLE		= 0xEFBDAA,	//ｪ
	HKLO		= 0xEFBDAB,	//ｫ
	HKLYA		= 0xEFBDAC,	//ｬ
	HKLYU		= 0xEFBDAD,	//ｭ
	HKLYO		= 0xEFBDAE,	//ｮ
	HKLTU		= 0xEFBDAF,	//ｯ
	HKA			= 0xEFBDB1,	//ｱ
	HKI			= 0xEFBDB2,	//ｲ
	HKU			= 0xEFBDB3,	//ｳ
	HKE			= 0xEFBDB4,	//ｴ
	HKO			= 0xEFBDB5,	//ｵ
	HKKA		= 0xEFBDB6,	//ｶ
	HKKI		= 0xEFBDB7,	//ｷ
	HKKU		= 0xEFBDB8,	//ｸ
	HKKE		= 0xEFBDB9,	//ｹ
	HKKO		= 0xEFBDBA,	//ｺ
	HKSA		= 0xEFBDBB,	//ｻ
	HKSI		= 0xEFBDBC,	//ｼ
	HKSU		= 0xEFBDBD,	//ｽ
	HKSE		= 0xEFBDBE,	//ｾ
	HKSO		= 0xEFBDBF,	//ｿ
	HKTA		= 0xEFBE80,	//ﾀ
	HKTI		= 0xEFBE81,	//ﾁ
	HKTU		= 0xEFBE82,	//ﾂ
	HKTE		= 0xEFBE83,	//ﾃ
	HKTO		= 0xEFBE84,	//ﾄ
	HKNA		= 0xEFBE85,	//ﾅ
	HKNI		= 0xEFBE86,	//ﾆ
	HKNU		= 0xEFBE87,	//ﾇ
	HKNE		= 0xEFBE88,	//ﾈ
	HKNO		= 0xEFBE89,	//ﾉ
	HKHA		= 0xEFBE8A,	//ﾊ
	HKHI		= 0xEFBE8B,	//ﾋ
	HKHU		= 0xEFBE8C,	//ﾌ
	HKHE		= 0xEFBE8D,	//ﾍ
	HKHO		= 0xEFBE8E,	//ﾎ
	HKMA		= 0xEFBE8F,	//ﾏ
	HKMI		= 0xEFBE90,	//ﾐ
	HKMU		= 0xEFBE91,	//ﾑ
	HKME		= 0xEFBE92,	//ﾒ
	HKMO		= 0xEFBE93,	//ﾓ
	HKYA		= 0xEFBE94,	//ﾔ
	HKYU		= 0xEFBE95,	//ﾕ
	HKYO		= 0xEFBE96,	//ﾖ
	HKRA		= 0xEFBE97,	//ﾗ
	HKRI		= 0xEFBE98,	//ﾘ
	HKRU		= 0xEFBE99,	//ﾙ
	HKRE		= 0xEFBE9A,	//ﾚ
	HKRO		= 0xEFBE9B,	//ﾛ
	HKWA		= 0xEFBE9C,	//ﾜ
	HKN			= 0xEFBE9D,	//ﾝ
	/*
	HDAKU		= 0xEFBE9E,	//ﾞ		0x5E		0xDE		0x8EDE		0xFF9E		0xEFBE9E
	HHANDAKU	= 0xEFBE9F,	//ﾟ		0x5F		0xDF		0x8EDF		0xFF9F		0xEFBE9F
	*/
	HSyllabaryStart	= HKWO,
	HSyllabaryEnd	= HKN
};
enum HSymbol{
	HSPACE		= 0x000020,// 
	HEXCLA		= 0x000021,//!
	HDQUO		= 0x000022,//"
	HNUMBER		= 0x000023,//#
	HDOLL		= 0x000024,//$
	HPERCENT	= 0x000025,//%
	HAMPERSAND	= 0x000026,//&
	HLSQUO		= 0x000027,//'
	HLPAREN		= 0x000028,//(
	HRPAREN		= 0x000029,//)
	HASTERISK	= 0x00002A,//*
	HPLUS		= 0x00002B,//+
	HCOMMA		= 0x00002C,//,
	HHYPHEN		= 0x00002D,//-
	HSTOP		= 0x00002E,//.
	HSOLIDUS	= 0x00002F,///
	HCOLON		= 0x00003A,//:
	HSCOLON		= 0x00003B,//;
	HLTHAN		= 0x00003C,//<
	HEQUALS		= 0x00003D,//=
	HGTHAN		= 0x00003E,//>
	HQUES		= 0x00003F,//?
	HAT			= 0x000040,//@
	HLSQUARE	= 0x00005B,//[
	HYEN		= 0x00005C,//\//
	HRSQUARE	= 0x00005D,//]
	HCIRCUM		= 0x00005E,//^
	HLOW		= 0x00005F,//_
	HRSQUO		= 0x000060,//`
	HLCURLY		= 0x00007B,//{
	HVER		= 0x00007C,//|
	HRCURLY		= 0x00007D,//}
	HTILDE		= 0x00007E,//~
	HISTOP		= 0xEFBDA1,//｡ //半角カタカナ
	HLCORNER	= 0xEFBDA2,//｢ //半角カタカナ
	HRCORNER	= 0xEFBDA3,//｣ //半角カタカナ
	HICOMMA		= 0xEFBDA4,//､ //半角カタカナ
	HMDOT		= 0xEFBDA5,//･ //半角カタカナ
	HLONGSOUND	= 0xEFBDB0,//ｰ //半角カタカナ
	HDAKU		= 0xEFBE9E,//ﾞ //半角カタカナ
	HHANDAKU	= 0xEFBE9F,//ﾟ //半角カタカナ
	HRARROW		= 0xEFBFA9,//￩
	HLARROW		= 0xEFBFAA,//￪
	HUARROW		= 0xEFBFAB,//￫
	HDARROW		= 0xEFBFAC,//￬
	HKICHI		= 0x000000,//ヽ
	HKICHID		= 0x000000,//ヾ
	HHICHI		= 0x000000,//ゝ
	HHICHID		= 0x000000//ゞ
};

//ひらがな
enum FHiragana{
						//		jis		EUC		sjis		UNICODE	UTF8
	FHLA		=0xE38181,//ぁ	0x2421	0xA4A1	0x829F		0x3041	0xE38181
	/*                   
	FHA			=0xE38182,//あ	0x2422	0xA4A2	0x82A0		0x3042	0xE38182
	FHLI		=0xE38183,//ぃ	0x2423	0xA4A3	0x82A1		0x3043	0xE38183
	FHI			=0xE38184,//い	0x2424	0xA4A4	0x82A2		0x3044	0xE38184
	FHLU		=0xE38185,//ぅ	0x2425	0xA4A5	0x82A3		0x3045	0xE38185
	FHU			=0xE38186,//う	0x2426	0xA4A6	0x82A4		0x3046	0xE38186
	FHLE		=0xE38187,//ぇ	0x2427	0xA4A7	0x82A5		0x3047	0xE38187
	FHE			=0xE38188,//え	0x2428	0xA4A8	0x82A6		0x3048	0xE38188
	FHLO		=0xE38189,//ぉ	0x2429	0xA4A9	0x82A7		0x3049	0xE38189
	FHO			=0xE3818A,//お	0x242A	0xA4AA	0x82A8		0x304A	0xE3818A
	FHKA		=0xE3818B,//か	0x242B	0xA4AB	0x82A9		0x304B	0xE3818B
	FHGA		=0xE3818C,//が	0x242C	0xA4AC	0x82AA		0x304C	0xE3818C
	FHKI		=0xE3818D,//き	0x242D	0xA4AD	0x82AB		0x304D	0xE3818D
	FHGI		=0xE3818E,//ぎ	0x242E	0xA4AE	0x82AC		0x304E	0xE3818E
	FHKU		=0xE3818F,//く	0x242F	0xA4AF	0x82AD		0x304F	0xE3818F
	FHGU		=0xE38190,//ぐ	0x2430	0xA4B0	0x82AE		0x3050	0xE38190
	FHKE		=0xE38191,//け	0x2431	0xA4B1	0x82AF		0x3051	0xE38191
	FHGE		=0xE38192,//げ	0x2432	0xA4B2	0x82B0		0x3052	0xE38192
	FHKO		=0xE38193,//こ	0x2433	0xA4B3	0x82B1		0x3053	0xE38193
	FHGO		=0xE38194,//ご	0x2434	0xA4B4	0x82B2		0x3054	0xE38194
	FHSA		=0xE38195,//さ	0x2435	0xA4B5	0x82B3		0x3055	0xE38195
	FHZA		=0xE38196,//ざ	0x2436	0xA4B6	0x82B4		0x3056	0xE38196
	FHSI		=0xE38197,//し	0x2437	0xA4B7	0x82B5		0x3057	0xE38197
	FHZI		=0xE38198,//じ	0x2438	0xA4B8	0x82B6		0x3058	0xE38198
	FHSU		=0xE38199,//す	0x2439	0xA4B9	0x82B7		0x3059	0xE38199
	FHZU		=0xE3819A,//ず	0x243A	0xA4BA	0x82B8		0x305A	0xE3819A
	FHSE		=0xE3819B,//せ	0x243B	0xA4BB	0x82B9		0x305B	0xE3819B
	FHZE		=0xE3819C,//ぜ	0x243C	0xA4BC	0x82BA		0x305C	0xE3819C
	FHSO		=0xE3819D,//そ	0x243D	0xA4BD	0x82BB		0x305D	0xE3819D
	FHZO		=0xE3819E,//ぞ	0x243E	0xA4BE	0x82BC		0x305E	0xE3819E
	FHTA		=0xE3819F,//た	0x243F	0xA4BF	0x82BD		0x305F	0xE3819F
	FHDA		=0xE381A0,//だ	0x2440	0xA4C0	0x82BE		0x3060	0xE381A0
	FHTI		=0xE381A1,//ち	0x2441	0xA4C1	0x82BF		0x3061	0xE381A1
	FHDI		=0xE381A2,//ぢ	0x2442	0xA4C2	0x82C0		0x3062	0xE381A2
	FHLTU		=0xE381A3,//っ	0x2443	0xA4C3	0x82C1		0x3063	0xE381A3
	FHTU		=0xE381A4,//つ	0x2444	0xA4C4	0x82C2		0x3064	0xE381A4
	FHDU		=0xE381A5,//づ	0x2445	0xA4C5	0x82C3		0x3065	0xE381A5
	FHTE		=0xE381A6,//て	0x2446	0xA4C6	0x82C4		0x3066	0xE381A6
	FHDE		=0xE381A7,//で	0x2447	0xA4C7	0x82C5		0x3067	0xE381A7
	FHTO		=0xE381A8,//と	0x2448	0xA4C8	0x82C6		0x3068	0xE381A8
	FHDO		=0xE381A9,//ど	0x2449	0xA4C9	0x82C7		0x3069	0xE381A9
	FHNA		=0xE381AA,//な	0x244A	0xA4CA	0x82C8		0x306A	0xE381AA
	FHNI		=0xE381AB,//に	0x244B	0xA4CB	0x82C9		0x306B	0xE381AB
	FHNU		=0xE381AC,//ぬ	0x244C	0xA4CC	0x82CA		0x306C	0xE381AC
	FHNE		=0xE381AD,//ね	0x244D	0xA4CD	0x82CB		0x306D	0xE381AD
	FHNO		=0xE381AE,//の	0x244E	0xA4CE	0x82CC		0x306E	0xE381AE
	FHHA		=0xE381AF,//は	0x244F	0xA4CF	0x82CD		0x306F	0xE381AF
	FHBA		=0xE381B0,//ば	0x2450	0xA4D0	0x82CE		0x3070	0xE381B0
	FHPA		=0xE381B1,//ぱ	0x2451	0xA4D1	0x82CF		0x3071	0xE381B1
	FHHI		=0xE381B2,//ひ	0x2452	0xA4D2	0x82D0		0x3072	0xE381B2
	FHBI		=0xE381B3,//び	0x2453	0xA4D3	0x82D1		0x3073	0xE381B3
	FHPI		=0xE381B4,//ぴ	0x2454	0xA4D4	0x82D2		0x3074	0xE381B4
	FHHU		=0xE381B5,//ふ	0x2455	0xA4D5	0x82D3		0x3075	0xE381B5
	FHBU		=0xE381B6,//ぶ	0x2456	0xA4D6	0x82D4		0x3076	0xE381B6
	FHPU		=0xE381B7,//ぷ	0x2457	0xA4D7	0x82D5		0x3077	0xE381B7
	FHHE		=0xE381B8,//へ	0x2458	0xA4D8	0x82D6		0x3078	0xE381B8
	FHBE		=0xE381B9,//べ	0x2459	0xA4D9	0x82D7		0x3079	0xE381B9
	FHPE		=0xE381BA,//ぺ	0x245A	0xA4DA	0x82D8		0x307A	0xE381BA
	FHHO		=0xE381BB,//ほ	0x245B	0xA4DB	0x82D9		0x307B	0xE381BB
	FHBO		=0xE381BC,//ぼ	0x245C	0xA4DC	0x82DA		0x307C	0xE381BC
	FHPO		=0xE381BD,//ぽ	0x245D	0xA4DD	0x82DB		0x307D	0xE381BD
	FHMA		=0xE381BE,//ま	0x245E	0xA4DE	0x82DC		0x307E	0xE381BE
	FHMI		=0xE381BF,//み	0x245F	0xA4DF	0x82DD		0x307F	0xE381BF
	FHMU		=0xE38280,//む	0x2460	0xA4E0	0x82DE		0x3080	0xE38280
	FHME		=0xE38281,//め	0x2461	0xA4E1	0x82DF		0x3081	0xE38281
	FHMO		=0xE38282,//も	0x2462	0xA4E2	0x82E0		0x3082	0xE38282
	FHLYA		=0xE38283,//ゃ	0x2463	0xA4E3	0x82E1		0x3083	0xE38283
	FHYA		=0xE38284,//や	0x2464	0xA4E4	0x82E2		0x3084	0xE38284
	FHLYU		=0xE38285,//ゅ	0x2465	0xA4E5	0x82E3		0x3085	0xE38285
	FHYU		=0xE38286,//ゆ	0x2466	0xA4E6	0x82E4		0x3086	0xE38286
	FHLYO		=0xE38287,//ょ	0x2467	0xA4E7	0x82E5		0x3087	0xE38287
	FHYO		=0xE38288,//よ	0x2468	0xA4E8	0x82E6		0x3088	0xE38288
	FHRA		=0xE38289,//ら	0x2469	0xA4E9	0x82E7		0x3089	0xE38289
	FHRI		=0xE3828A,//り	0x246A	0xA4EA	0x82E8		0x308A	0xE3828A
	FHRU		=0xE3828B,//る	0x246B	0xA4EB	0x82E9		0x308B	0xE3828B
	FHRE		=0xE3828C,//れ	0x246C	0xA4EC	0x82EA		0x308C	0xE3828C
	FHRO		=0xE3828D,//ろ	0x246D	0xA4ED	0x82EB		0x308D	0xE3828D
	FHLWA		=0xE3828E,//ゎ	0x246E	0xA4EE	0x82EC		0x308E	0xE3828E
	FHWA		=0xE3828F,//わ	0x246F	0xA4EF	0x82ED		0x308F	0xE3828F
	FHWI		=0xE38290,//ゐ	0x2470	0xA4F0	0x82EE		0x3090	0xE38290
	FHWE		=0xE38291,//ゑ	0x2471	0xA4F1	0x82EF		0x3091	0xE38291
	FHWO		=0xE38292,//を	0x2472	0xA4F2	0x82F0		0x3092	0xE38292
	FHN			=0xE38293,//ん	0x2473	0xA4F3	0x82F1		0x3093	0xE38293
	*//*                 
	FHVU		=0xE38294,//ゔ								0x3094	0xE38294
	FHLKA		=0xE38295,//ゕ								0x3095	0xE38295
	*/                   
	FHLKE		=0xE38296,//ゖ								0x3096	0xE38296
	/*                   
	FDAKU		=0xE3829B,//゛	0x212B	0xA1AB	0x814A		0x309B	0xE3829B
	FHANDAKU	=0xE3829C,//゜	0x212C	0xA1AC	0x814B		0x309C	0xE3829C
	FKICHI		=0xE3829D,//ゝ	0x2135	0xA1B5	0x8154		0x309D	0xE3829D
	FKICHID		=0xE3829E,//ゞ	0x2136	0xA1B6	0x8155		0x309E	0xE3829E
	*//*                 
	FYORI		=0xE3829F,//ゟ								0x309F	0xE3829F
	*/
	FHiraganaStart	= FHLA,
	FHiraganaEnd	= FHLKE
};

//漢字
enum FKanji{
										//jis				EUC				sjis			UNICODE				UTF8
	//全角漢字1
	FKanjiStart1	=0xE2BA80,//⺀		//0x3021,//亜		0xB0A1,//亜		0x889F,//亜		//0x2E80,//⺀		0xE2BA80,//⺀
	FKanjiEnd1		=0xE2BF9F,//　部首	//0x7426,//熙		0xF4A6,//熙		0x9FFC,//滌		//0x2FDF,//　部首	0xE2BF9F,//　部首
	//全角漢字2               
	FKanjiStart2	=0xE39080,//㐀		//0x0000,//			0x0000,//  		0xE040,//漾		//0x3400,//㐀		0xE39080,//㐀
	FKanjiEnd2		=0xE9BEBB,//龻		//0x0000,//			0x0000,//  		0xEAA4,//熙		//0x9FBB,//龻		0xE9BEBB,//龻
	//全角漢字3               
	FKanjiStart3	=0xEFA480,//豈		//0x0000,//			0x0000,//  		0x0000,//		//0xF900,//豈		0xEFA480,//豈
	FKanjiEnd3		=0xEFA9AA//頻		//0x0000,//			0x0000,//  		0x0000,//		//0xFA60,//頻		0xEFA9AA,//頻
};


const unsigned int STARTEND = 2;
const unsigned int CODESTART = 0;
const unsigned int CODEEND = 1;
const unsigned int hEscArea[STARTEND] 		= { 0x0,		0x1F }; /*NULL - US*/
const unsigned int hUpAlphaArea[STARTEND]	= { 0x41,		0x5A }; /*A - Z*/
const unsigned int hLoAlphaArea[STARTEND]	= { 0x61,		0x7A }; /*a - z*/
const unsigned int hNumArea[STARTEND]		= { 0x30,		0x39 }; /*0 - 9*/
const unsigned int hNewLines[]				= { 0x0A, 0x0c, 0x0d }; /*\n \f \r*/
const unsigned int hSpaces[]				= { 0x09, 0x20 }; /*\t SP*/
const unsigned int hPuncs[]					= { 0x5F }; /*_ -0x2D*/
const unsigned int hPuncsCount				= sizeof(hPuncs)/sizeof(hPuncs[0]);

const unsigned int hKataArea[STARTEND]		= { HSyllabaryStart,	HSyllabaryEnd };/*ｦ - ﾝ*/
const unsigned int hKataEtcs[]				= {
	/*= ｡ ｢ ｣ ､ ･ ｰ ﾞ ﾟ*/
	HEQUALS, HISTOP, HLCORNER, HRCORNER, HICOMMA, HMDOT, HLONGSOUND, HDAKU, HHANDAKU
};
const unsigned int hKataEtcsCount			= sizeof(hKataEtcs)/sizeof(hKataEtcs[0]);
const unsigned int hKataDakus[]				= { HDAKU,		HHANDAKU };
const unsigned int hKataDakuCount			= sizeof(hKataDakus)/sizeof(hKataDakus[0]);


const unsigned int zHiraArea[STARTEND]		= { FHiraganaStart,		FHiraganaEnd };/*ぁ - ゖ*/
const unsigned int zHiraEtcs[]				= { FDAKU, FHANDAKU, FKICHI, FKICHID, FYORI };/* ゛ ゜ ゝ ゞ ゟ */
const unsigned int zHiraEtcCount			= sizeof(zHiraEtcs) / sizeof(zHiraEtcs[0]);
const unsigned int zKataArea[STARTEND]		= { FKLA,		FKVO };/*ァ  ヺ*/
const unsigned int zKataEtcs[]				= { FDHYPHEN, FMDOT, FLONGSOUND, FKICHI, FKICHID, FKOTO };/*゠ ・ ー ヽ ヾ ヿ */
const unsigned int zKataEtcCount			= sizeof(zKataEtcs) / sizeof(zKataEtcs[0]);
const unsigned int zKanjiArea[][STARTEND] 	= { 
	{ FKanjiStart1, FKanjiEnd1 }, { FKanjiStart2, FKanjiEnd2 }, { FKanjiStart3, FKanjiEnd3 } 
};
const unsigned int zKanjiLine				= sizeof(zKanjiArea)/sizeof(zKanjiArea[0]);
const unsigned int zNumArea[STARTEND]		= { 0xEFBC90,		0xEFBC99 };
const unsigned int zUpAlphaArea[STARTEND]	= { 0xEFBCA1,		0xEFBCBA };
const unsigned int zLoAlphaArea[STARTEND]	= { 0xEFBD81,		0xEFBD9A };
const unsigned int zSpaces[]				= { 0xE38080 };
const unsigned int zSpacesCount				= sizeof(zSpaces) / sizeof(zSpaces[0]);
const unsigned int zPuncs[]				= {
	0xE280B0, 0xE280B1, 0xE280B2, 0xE280B3, 0xE280B4, 0xE280B5, //ハイフン
	0xE28193, 0xE3809C, 0xE380B0,                               //波ダッシュ
	0xEFBD9E,                                                   //全角チルダ
	0xE383BC, 0xEFBDB0,                                         //長音符
	0xEFBCBF                                                    //アンダーバー
};
const unsigned int zPuncsCount			= sizeof(zPuncs)/sizeof(zPuncs[0]);
const unsigned int zOdoris[]				= {
	//々, 〱, 〲, 〻, ゝ, ゞ, ヽ, ヾ
	0xE38085, 0xE380B1, 0xE380B2, 0xE382BB, 0xE3829D, 0xE3829E, 0xE383BD, 0xE383BE
};
const unsigned int zOdorisCount			= sizeof(zOdoris)/sizeof(zOdoris[0]);

Selecting::Selecting(){
	this->lineStrLength = 1024;
	this->lineStr = new char[this->lineStrLength];
}
Selecting::~Selecting(){
	if( this->lineStr != NULL)
		delete[] this->lineStr;
}
void Selecting::Init(NppData nppData){
	this->nppHwnd = nppData._nppHandle;
	this->mainScintilla = nppData._scintillaMainHandle;
	this->secondScintilla = nppData._scintillaSecondHandle;
	return;
}
void Selecting::ZenToHan(const DIRECTION direction, int opt)
{

	int currentScintilla = -1;
	//現在の選択範囲の取得
	int anchorPos;
	int curPos;
	//現在の選択範囲のテキスト取得
	int textLen;
	char *selectText;

	int bufferLen;
	char *buffer;
	int bufferCount;

	////前のターゲットの情報
	//int oldTargetStart, oldTargetEnd;
	//int targetStart, targetEnd;
	
	//コード分割前
	//int code, codeKind, readChar;
	//int changeCode;
	//int i,j;
	//int replaceCount;


	//現在のscintillaの取得 0->main 1->sub
	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		this->_hWnd = this->mainScintilla;
	else
		this->_hWnd = this->secondScintilla;

	curPos = ::SendMessage(this->_hWnd, SCI_GETCURRENTPOS, 0, 0);
	anchorPos = ::SendMessage(this->_hWnd, SCI_GETANCHOR, 0, 0);

	//現在の選択範囲のテキスト取得
	textLen = ::SendMessage(this->_hWnd, SCI_GETSELTEXT, 0, 0);
	selectText = new char[textLen];
	::SendMessage(this->_hWnd, SCI_GETSELTEXT, textLen, (LPARAM)selectText);

	//最大3倍必要になるためバッファを3倍取得
	bufferLen = textLen * 3;
	buffer = new char[bufferLen];
	ZeroMemory(buffer, bufferLen);

	//
	//i=0;
	//bufferCount=0;
	//while(i<textLen)
	//{
	//	int daku=0;
	//	changeCode = 0;
	//	readChar = this->SetChar(i, selectText);
	//	code = this->GetUTFCode();
	//	codeKind = this->CodeKind(code, true);
	//	Dprintf("0x%x\n", codeKind);
	//	if(direction)
	//	{
	//		//if( (opt & this->ZHSymbol) )
	//		//{
	//		//	changeCode = this->ZenHanSymbol(code, direction);
	//		//}
	//		//半->全
	//		switch(codeKind)
	//		{
	//		case hUpAlpha:
	//			if( opt & ZHUpAlpha )
	//				changeCode = code - hUpAlphaArea[CODESTART] + zUpAlphaArea[CODESTART];
	//			break;
	//		case hLoAlpha:
	//			if( opt & ZHLoAlpha )
	//				changeCode = code - hLoAlphaArea[CODESTART] + zLoAlphaArea[CODESTART]; 
	//			break;
	//		case hNum:
	//			if( opt & ZHNum ) 
	//				changeCode = code - hNumArea[CODESTART] + zNumArea[CODESTART];
	//			break;
	//		case hKata:
	//			if( opt & ZHKata )
	//			{
	//				int dakuCode;
	//				int readDakuCode;
	//				int j;

	//				readDakuCode = this->SetChar(i+readChar, selectText);
	//				dakuCode = this->GetUTFCode();				
	//				for(j=0; j<hKataDakuCount; j++)
	//				{
	//					if( dakuCode == hKataDakus[j] )
	//					{
	//						daku = dakuCode;
	//						readChar += readDakuCode;
	//					}
	//				}
	//				changeCode = this->ZenHanKata(code, &daku);
	//			}
	//			break;
	//		case hKataEtc:
	//			if( opt & (ZHKata | ZHSymbol) )
	//				changeCode = this->ZenHanSymbol(code, direction);
	//			break;
	//		case hSpace:
	//		case hEtc:
	//			if( opt & ZHSymbol )
	//				changeCode = this->ZenHanSymbol(code, direction);
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		//if( (opt & this->ZHSymbol) )
	//		//{
	//		//	changeCode = this->ZenHanSymbol(code, direction);
	//		//}
	//		//全角->半角
	//		switch(codeKind)
	//		{
	//		case zUpAlpha:
	//			if( opt & ZHUpAlpha )
	//				changeCode = code - zUpAlphaArea[CODESTART] + hUpAlphaArea[CODESTART];
	//			break;
	//		case zLoAlpha:
	//			if( opt & ZHLoAlpha )
	//				changeCode = code - zLoAlphaArea[CODESTART] + hLoAlphaArea[CODESTART];
	//			break;
	//		case zNum:
	//			if( opt & ZHNum )
	//				changeCode = code - zNumArea[CODESTART] + hNumArea[CODESTART];
	//			break;
	//		case zKata:
	//			if( opt & ZHKata )
	//				changeCode = this->ZenHanKata(code, &daku);
	//			break;
	//		case zHiraEtc:
	//		case zKataEtc:
	//			if( opt & (ZHKata | ZHSymbol) )
	//				changeCode = this->ZenHanSymbol(code, direction);
	//			break;
	//		case zSpace:
	//		case zEtc:
	//			if( opt & ZHSymbol )
	//				changeCode = this->ZenHanSymbol(code, direction);
	//			break;
	//		}
	//	}
	//	if( changeCode != 0)
	//	{
	//		j=0;

	//		Dprintf("変換前 %s\n", this->utfChar);
	//		this->GetMultibyteCharacter(changeCode);
	//		Dprintf("変換後 %s\n", this->utfChar);

	//		while(this->utfChar[j]){
	//			buffer[bufferCount] = this->utfChar[j];
	//			j++;
	//			bufferCount++;
	//		}
	//		if(codeKind == this->zKata && daku != 0)
	//		{
	//			j=0;
	//			this->GetMultibyteCharacter(daku);
	//			while(this->utfChar[j]){
	//				buffer[bufferCount] = this->utfChar[j];
	//				j++;
	//				bufferCount++;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		this->GetMultibyteCharacter(code);
	//		for(j=0; j< readChar; j++)
	//		{
	//			buffer[bufferCount] = this->utfChar[j];
	//			bufferCount++;
	//		}
	//	}
	//	i += readChar;		
	//}
	bufferCount = this->ZenHanStr(selectText, textLen, buffer, bufferLen, direction, opt);
	::SendMessage(this->_hWnd, SCI_TARGETFROMSELECTION, 0, 0);
	::SendMessage(this->_hWnd, SCI_REPLACESEL, 0, (LPARAM)buffer);
	
	//小さい方から選択
	if( anchorPos < curPos)
		curPos = anchorPos;
	::SendMessage(this->_hWnd, SCI_SETSELECTION, curPos, curPos+bufferCount-1);
	
	delete[] buffer;
	delete[] selectText;

	return;
}
void Selecting::HiraToKata(const DIRECTION direction)
{
	int currentScintilla = -1;
	//現在の選択範囲の取得
	int anchorPos;
	int curPos;
	//現在の選択範囲のテキスト取得
	int textLen;
	char *selectText;
	int replaceLen;
	wchar_t *replaceText;
	int selectTextUtf8Len;
	wchar_t *selectTextUtf8;

	////前のターゲットの情報
	//int oldTargetStart, oldTargetEnd;
	//int targetStart, targetEnd;

	//現在のscintillaの取得 0->main 1->sub
	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	if(currentScintilla == -1) return;
	if(currentScintilla == 0)
		this->_hWnd = this->mainScintilla;
	else
		this->_hWnd = this->secondScintilla;

	curPos = ::SendMessage(this->_hWnd, SCI_GETCURRENTPOS, 0, 0);
	anchorPos = ::SendMessage(this->_hWnd, SCI_GETANCHOR, 0, 0);

	//WinApi使用すべて変換のみ

	//選択文字列の取得
	textLen = ::SendMessage(this->_hWnd, SCI_GETSELTEXT, 0, 0);
	selectText = new char[textLen];
	::SendMessage(this->_hWnd, SCI_GETSELTEXT, textLen, (LPARAM)selectText);

	//utf8をwchar_tへLCMapStringがutf8のままだと受け付けない
	selectTextUtf8Len = ::MultiByteToWideChar( CP_UTF8, 0, selectText, textLen, NULL, NULL);
	selectTextUtf8 = new wchar_t[selectTextUtf8Len];
	::MultiByteToWideChar( CP_UTF8, 0, selectText, textLen, selectTextUtf8, selectTextUtf8Len);
	
	if( direction == TOHIRA)
	{
		replaceLen = ::LCMapStringW(GetUserDefaultLCID(), LCMAP_HIRAGANA, selectTextUtf8, selectTextUtf8Len, 0, 0);
		replaceText = new wchar_t[replaceLen];
		::LCMapStringW(GetUserDefaultLCID(), LCMAP_HIRAGANA, selectTextUtf8, selectTextUtf8Len, replaceText, replaceLen);
	}
	else
	{
		replaceLen = ::LCMapStringW(GetUserDefaultLCID(), LCMAP_KATAKANA, selectTextUtf8, selectTextUtf8Len, 0, 0);
		replaceText = new wchar_t[replaceLen];
		::LCMapStringW(GetUserDefaultLCID(), LCMAP_KATAKANA, selectTextUtf8, selectTextUtf8Len, replaceText, replaceLen);
	}
	
	//取得したものがsjisになるのでutf8へ変換
	char *utf8;
	int utf8Len;
	
	//To utf8
	utf8Len = ::WideCharToMultiByte( CP_UTF8, 0, replaceText, replaceLen, NULL, NULL, NULL, NULL);
	utf8 = new char[utf8Len];
	::WideCharToMultiByte( CP_UTF8, 0, replaceText, replaceLen, utf8, utf8Len, NULL, NULL);


	////古いターゲット範囲の取得
	//oldTargetStart = ::SendMessage(this->_hWnd, SCI_GETTARGETSTART, 0, 0);
	//oldTargetEnd = ::SendMessage(this->_hWnd, SCI_GETTARGETEND, 0, 0);
	//Dprintf("旧ターゲット範囲 %d - %d\n", oldTargetStart, oldTargetEnd);
	//ターゲットの設定
	//SCI_SETTARGETSTART or ENDを使用時は置き換え多分アンカーとキャレットポジションを計算しなおさないといけない為使わない
	::SendMessage(this->_hWnd, SCI_TARGETFROMSELECTION, 0, 0);
	//::SendMessage(this->_hWnd, SCI_SETTARGETSTART, anchorPos, 0);
	//::SendMessage(this->_hWnd, SCI_SETTARGETEND, curPos, 0);
	//Dprintf("ターゲット範囲 %d - %d\n", anchorPos, curPos);
	
	//::SendMessage(this->_hWnd, SCI_REPLACESEL, 0, (LPARAM)utf8);
	//::SendMessage(this->_hWnd, SCI_REPLACETARGET, utf8Len-1, (LPARAM)utf8);
	::SendMessage(this->_hWnd, SCI_REPLACESEL, 0, (LPARAM)utf8);
	//targetStart = ::SendMessage(this->_hWnd, SCI_GETTARGETSTART, 0, 0);
	//::SendMessage(this->_hWnd, SCI_INSERTTEXT, targetStart, (LPARAM)utf8);
	
	//小さい方から選択
	if( anchorPos < curPos)
		curPos = anchorPos;
	::SendMessage(this->_hWnd, SCI_SETSELECTION, curPos, curPos+utf8Len-1);

	delete[] utf8;
	delete[] replaceText;
	delete[] selectTextUtf8;

	return;
}

int Selecting::GetUtf8Code(const char *src, int pos, int *startPos)
{
	int i=0;
	int j=0;
	unsigned char *c;

	c = (unsigned char*)(src + pos);
	//3バイト文字以下はwchar1つに収められる それ以外はサロゲートペアのため2つ必要

	if( *c <= 0x7F )	//0x80以下 ascii
	{
		i = 1;
		this->utf8Code = *c;
	}
	else
	{
		for(j=0; j <= 4 ; j++)
		{
			if( *(c-j) <= 0xBF)	//0xBF以下でascii出ないものはUTF8の構成要素のため
				continue;
			else if( *(c-j) <= 0xDF)	//0xC2-0xDF 2バイト文字
			{
				i = 2;
				this->utf8Code = ( *(c-j) << 8 ) | *(c-j+1);
				//this->utf8Code = ( (*(c-j) & 0x1F)<<6 ) | (*(c-j+1) & 0x3F);
				break;
			}
			else if( *(c-j) <= 0xEF)	//0xE0-0xF0 3バイト文字
			{
				i = 3;
				this->utf8Code = ( *(c-j)<<8*2 ) | ( *(c-j+1)<<8 ) | ( *(c-j+2) );
				//this->utf8Code = ( (*(c-j) & 0x0F)<<6*2 ) | ( (*(c-j+1) & 0x3F)<<6 ) | (*(c-j+2) & 0x3F);
				break;
			}
			else					//サロゲート4バイト文字
			{
				i = 4;
				//unsigned int first, second;
				////一度unicodeへ
				//this->utf8Code = ( (*(c-j) & 0x07)<<6*3 ) | ( (*(c-j+1) & 0x3F)<<6*2 ) | ( (*(c-j+2) & 0x3F)<<6 ) | (*(c-j+3) & 0x3F) ;
				////unicode から ucs(utf16 2byte)へ
				//this->utf8Code -= 0x10000;
				////0x3FF = (11 1111 1111)2 10bit
				//second = this->utf8Code & 0x3FF | 0xDC00;
				//first  = this->utf8Code >> 10 | 0xD800;

				//this->utf8Code = first << 16 | second;
				this->utf8Code = ( *(c-j)<<8*3 ) | ( *(c-j+1)<<8*2 ) | ( *(c-j+2)<<8 ) | (*(c-j+3));
				break;
			}
		}
	}
	if( startPos != NULL)
		*startPos = j;
	//Dprintf("startPos %d useByte %d Code 0x%x\n", *startPos, i, this->utf8Code);

	return i;
}
int Selecting::SetChar(int readPos){
	int i=0;
	unsigned char c;
	//utf8の先頭バイトの検索
	for(i=0; i<UTF8BYTE; i++){
		c = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, readPos-i, 0);
		//0x80未満はasciiのため 0xC2以上はUTF8の
		if( ( c < 0x80 ) || ( c >= 0xC2) )
			break;
	}
	readPos -= i;
	
	i=1;
	ZeroMemory(this->utfChar, UTF8BYTE+1);
	this->utfChar[0] = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, readPos, 0);
	if( this->utfChar[0] > 0x80) {
		//0xE0以上 0xF0以下の場合3バイトUTF8 ラテン文字は考慮に入れない
		if( this->utfChar[0] < 0xF0 ) {
			for(i=1;i<UTF8BYTE-1;i++)
				this->utfChar[i] = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, readPos+i, 0);
		} else {
			for(i=1;i<UTF8BYTE;i++)
				this->utfChar[i] = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, readPos+i, 0);
		}
	}
	return i;
}
int Selecting::SetChar(int readPos, const char *str){
	int i=0;
	unsigned char c;
	//utf8の先頭バイトの検索
	for(i=0; i<UTF8BYTE; i++){
		c = (unsigned char)str[readPos-i];
		//0x80未満はasciiのため 0xC2以上はUTF8の
		if( ( c < 0x80 ) || ( c >= 0xC2) )
			break;
	}
	readPos -= i;
	
	i=1;
	ZeroMemory(this->utfChar, UTF8BYTE+1);
	this->utfChar[0] = (unsigned char)str[readPos];
	if( this->utfChar[0] > 0x80) {
		//0xE0以上 0xF0以下の場合3バイトUTF8 ラテン文字は考慮に入れない
		if( this->utfChar[0] < 0xF0 ) {
			for(i=1;i<UTF8BYTE-1;i++)
				this->utfChar[i] = (unsigned char)str[readPos+i];
		} else {
			for(i=1;i<UTF8BYTE;i++)
				this->utfChar[i] = (unsigned char)str[readPos+i];
		}
	}
	return i;
}
int Selecting::GetUTFCode(){
	int i=0;
	int utfCode=0;
	
	while(this->utfChar[i]!=0 || i>UTF8BYTE) {
		//1バイト左にシフト
		utfCode = utfCode<<8;
		utfCode+=this->utfChar[i];
		i++;
	}
	return utfCode;
}
int Selecting::GetMultibyteCharacter(int UTFCode)
{
	int i;
	int j=0;
	ZeroMemory(&this->utfChar, UTF8BYTE);
	for(i=0; i<UTF8BYTE; i++)
	{
		this->utfChar[j] = (UTFCode>>((4-1-i)*8) & 0xFF);
		if(this->utfChar[j] != 0)
			j++;
	}
	return i;
}
int Selecting::CodeKind(unsigned int utfCode, bool closely){
	
	int codeKind;
	int i;
	codeKind = this->CodeClosely(utfCode);
	
	if(closely == 0)
	{
		if(codeKind < Zenkaku)
		{
			switch( codeKind )
			{
			case hEtc:
				//半角
				for(i=0;i<hPuncsCount;i++)
					if( hPuncs[i] == utfCode)	return hWord;
				break;
			case hLoAlpha:
			case hUpAlpha:
			case hNum:
				codeKind = hWord;
				break;
			//case hSpace:
			//case hNewLine:
			//	codeKind = hEtc;
			//	break;
			case hKataEtc:
				codeKind = hKata;
				break;
			}
		}
		else
		{		
			//約物の検索 全角
			//最初に色々なところにまたがる約物か検査
			//for(i=0; i<zPuncCount; i++)
			//{
			//	if( c == zPunc[i])
			//		return zPunc;
			//}	
			switch( codeKind )
			{
			case zEtc:
				for(i=0;i<zOdorisCount;i++)
					if( zOdoris[i] == utfCode) return zKanji;
				break;
			case zLoAlpha:
			case zUpAlpha:
				codeKind = zAlpha;
				break;
			case zSpace:
				codeKind = zEtc;
				break;
			case zHiraEtc:
				codeKind = zHira;
				break;
			case zKataEtc:
				codeKind = zKata;
				break;
			}
		}
	}
	return codeKind;
}
int Selecting::CodeClosely(unsigned int utfCode)
{
	int i;
	if(utfCode > 0x0080)
	{
		if(		 zHiraArea[CODESTART]	<=utfCode && utfCode<=zHiraArea[CODEEND])
			return zHira;	/*全角ひらがな*/
		else if( zKataArea[CODESTART]	<=utfCode && utfCode<=zKataArea[CODEEND])
			return zKata;	/*全角カタカナ*/
		else if( zUpAlphaArea[CODESTART]<=utfCode && utfCode<=zUpAlphaArea[CODEEND])
			return zUpAlpha;/*全角英字(大)*/
		else if( zLoAlphaArea[CODESTART]<=utfCode && utfCode<=zLoAlphaArea[CODEEND])
			return zLoAlpha;/*全角英字(小)*/
		else if( zNumArea[CODESTART]	<=utfCode && utfCode<=zNumArea[CODEEND])
			return zNum;	/*全角数字*/
		else if( hKataArea[CODESTART]	<=utfCode && utfCode<=hKataArea[CODEEND])
			return hKata;	/*半角カタカナ*/	
		else
		{
			//漢字の判定
			for(i=0; i<zKanjiLine; i++)
			{
				if( zKanjiArea[i][CODESTART] <= utfCode && utfCode <= zKanjiArea[i][CODEEND] )
					return zKanji;/*全角漢字*/
			}
			for(i=0; i<zHiraEtcCount; i++)
			{
				if( utfCode == zHiraEtcs[i] )
					return zHiraEtc;/*全角ひらがな*/
			}
			for(i=0; i<zKataEtcCount; i++)
			{
				if( utfCode == zKataEtcs[i] )
					return zKataEtc;/*全角カタカナ*/
			}
			for(i=0; i<zSpacesCount; i++)
			{
				if( utfCode == zSpaces[i] )
					return zSpace;	/*全角スペース*/
			}
			for(i=0; i<hKataEtcsCount; i++)
			{
				if( utfCode == hKataEtcs[i] )
					return hKataEtc;/*半角カタカナ記号*/	
			}	
			return zEtc;			/*全角記号*/
		}
	}
	else
	{
		if(		 hEscArea[CODESTART]	<= utfCode && utfCode <= hEscArea[CODEEND]	)
		{
			for(i=0; i<(sizeof(hNewLines) / sizeof(hNewLines[0])); i++)
			{
				if( utfCode == hNewLines[i] )
					return hNewLine;/*改行文字*/
			}
			return hEsc;	/*制御文字*/
		}
		else if( hUpAlphaArea[CODESTART]<= utfCode && utfCode <= hUpAlphaArea[CODEEND])
			return hUpAlpha;/*半角英字(大)*/
		else if( hLoAlphaArea[CODESTART]<= utfCode && utfCode <= hLoAlphaArea[CODEEND])
			return hLoAlpha;/*半角英字(小)*/
		else if( hNumArea[CODESTART]	<= utfCode && utfCode <= hNumArea[CODEEND])
			return hNum;	/*半角数字*/
		else
		{
			for(i=0; i<(sizeof(hSpaces) / sizeof(hSpaces[0])); i++)
			{
				if( utfCode == hSpaces[i] )
					return hSpace;	/*スペースSP \t*/
			}
			return hEtc;	/*半角記号*/
		}
	}
}


int Selecting::ZenHanStr(const char *src, size_t srcSize, char *dest, size_t destSize, const DIRECTION direction, int opt)
{
	int i = 0;
	int j;
	int bufSize = 0;
	
	unsigned int daku;
	int dakuReadByte;
	int readByte;
	int code;
	int changeCode;
		//サイズが0のときは終端文字が出てくるまで
	while(*(src+i) != 0 &&
		 (srcSize == 0 || i < (int)srcSize) &&
		 (destSize == 0 || bufSize < (int)destSize)
		 )
	{
		readByte = this->SetChar(i, src);
		code = this->GetUTFCode();

		dakuReadByte = this->SetChar( (i+readByte), src);
		daku = this->GetUTFCode();

		changeCode = this->ZenHan( code, direction, opt, &daku);
		//サイズのみ計測
		if( destSize == 0 || dest == NULL)
		{
			if( changeCode == 0)
				bufSize += readByte;
			else
			{		
				bufSize += readByte;
				//daku (全角の半濁、濁点文字) or (半角で次の文字が濁点半濁点なら0違うなら1)
				if( daku == 1) //半角でかつ次の文字が濁点半濁点の場合
				{
					i += dakuReadByte;
				}
				else if( daku != 0 )//全角で現在の文字が濁点半濁点の場合
				{
					bufSize += dakuReadByte;
				}
			}
		}
		else
		{
			if( changeCode == 0)
			{
				for(j=0; j<readByte; j++)
					dest[bufSize+j] = *(src+i+j);
				bufSize += readByte;
			}
			else
			{
				this->GetMultibyteCharacter(changeCode);
				for(j=0; this->utfChar[j]; j++)
				{
					dest[bufSize] = this->utfChar[j];
					bufSize++;
				}
		
				//daku (全角の半濁、濁点文字) or (半角で次の文字が濁点半濁点なら0違うなら1)
				if( daku == 1) //半角でかつ次の文字が濁点半濁点の場合
				{
					i+=dakuReadByte;
				}
				else if( daku != 0 )//全角で現在の文字が濁点半濁点の場合
				{
					this->GetMultibyteCharacter(daku);
					for(j=0; this->utfChar[j]; j++)
					{
						dest[bufSize] = this->utfChar[j];
						bufSize++;
					}
				}
			}
		}
		i += readByte;
	}
	////全角 -> 半角
	//if( direction == TOHALF)
	//{
	//	while( *(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
	//	{
	//		daku = 0;
	//		readByte = this->SetChar(i, src);
	//		code = this->GetUTFCode();
	//		changeCode = this->ZenHan( code, direction, opt, &daku);
	//		//置き換わるか( 0なら置き換わらない )
	//		if( changeCode == 0)
	//		{
	//			for(j=0; j<readByte; j++)
	//				dest[bufSize+j] = *(src+i+j);
	//			bufSize += readByte;
	//		}
	//		else
	//		{
	//			this->GetMultibyteCharacter(changeCode);
	//			for(j=0; this->utfChar[j]; j++)
	//			{
	//				dest[bufSize] = this->utfChar[j];
	//				bufSize++;
	//			}
	//			if( daku != 0)
	//			{
	//				this->GetMultibyteCharacter(daku);
	//				for(j=0; this->utfChar[j]; j++)
	//				{
	//					dest[bufSize] = this->utfChar[j];
	//					bufSize++;
	//				}
	//			}
	//		}
	//		i += readByte;
	//	}
	//}
	////半角->全角
	//else
	//{
	//	while( *(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
	//	{
	//		readByte = this->SetChar(i, src);
	//		code = this->GetUTFCode();

	//		dakuReadByte = this->SetChar( (i+readByte), src);
	//		daku = this->GetUTFCode();

	//		changeCode =  this->ZenHan( code, direction, opt, &daku);

	//		//置き換わるか( 0なら置き換わらない )
	//		if( changeCode == 0)
	//		{
	//			for(j=0; j<readByte; j++)
	//				dest[bufSize+j] = *(src+i+j);
	//			bufSize += readByte;
	//		}
	//		else
	//		{
	//			this->GetMultibyteCharacter(changeCode);
	//			for(j=0; this->utfChar[j]; j++)
	//			{
	//				dest[bufSize] = this->utfChar[j];
	//				bufSize++;
	//			}
	//			//次の文字が濁点、半濁点かどうか、0なら濁点半濁点->結合されるので次の文字へを増やす
	//			if( daku == 0)
	//			{					
	//				//濁点半濁点は確実に3バイト文字なので確定
	//				i += dakuReadByte;
	//			}
	//		}
	//		i += readByte;
	//	}
	//}

	//終端文字分
	*(dest + bufSize) = 0;
	bufSize++;
	return bufSize;
}
unsigned int Selecting::ZenHan(const unsigned int code, const DIRECTION direction, int opt, unsigned int *daku)
{
	int codeKind;
	int changeCode = 0;

	codeKind = CodeClosely(code);
	if( direction == TOHALF )
	{
		*daku = 0;
		//全角->半角
		switch(codeKind)
		{
		case zUpAlpha:
			if( opt & ZHUpAlpha )
				changeCode = code - zUpAlphaArea[CODESTART] + hUpAlphaArea[CODESTART];
			break;
		case zLoAlpha:
			if( opt & ZHLoAlpha )
				changeCode = code - zLoAlphaArea[CODESTART] + hLoAlphaArea[CODESTART];
			break;
		case zNum:
			if( opt & ZHNum )
				changeCode = code - zNumArea[CODESTART] + hNumArea[CODESTART];
			break;
		case zKataEtc:
		case zKata:
			if( opt & ZHKata )
				changeCode = ZenHanKata(code, daku, direction);
			break;
		case zHiraEtc:
			if( opt & (ZHKata | ZHSymbol) )
				changeCode = ZenHanSymbol(code, direction);
			break;
		case zSpace:
		case zEtc:
			if( opt & ZHSymbol )
				changeCode = ZenHanSymbol(code, direction);
			break;
		}
	}
	else
	{
		//半->全
		switch(codeKind)
		{
		case hUpAlpha:
			if( opt & ZHUpAlpha )
				changeCode = code - hUpAlphaArea[CODESTART] + zUpAlphaArea[CODESTART];
			break;
		case hLoAlpha:
			if( opt & ZHLoAlpha )
				changeCode = code - hLoAlphaArea[CODESTART] + zLoAlphaArea[CODESTART]; 
			break;
		case hNum:
			if( opt & ZHNum ) 
				changeCode = code - hNumArea[CODESTART] + zNumArea[CODESTART];
			break;
		case hKataEtc:
		case hKata:
			if( opt & ZHKata )
				changeCode = ZenHanKata(code, daku, direction);
			break;
		case hSpace:
		case hEtc:
			if( opt & ZHSymbol )
				changeCode = ZenHanSymbol(code, direction);
			break;
		}
		if( *daku != 1)
			*daku = 0;
	}
	return changeCode;
}
unsigned int Selecting::ZenHanKata(unsigned int UTFCode, unsigned int *daku, const DIRECTION direction)
{
	//全角 or 半角
	if( direction == TOHALF)
	{
		*daku = 0;
		 //全角 -> 半角
		switch(UTFCode)
		{
		case FKLA			/*ァ*/:	 return HKLA		/*ｧ*/;
		case FKA			/*ア*/:	 return HKA			/*ｱ*/;
		case FKLI			/*ィ*/:	 return HKLI		/*ｨ*/;
		case FKI			/*イ*/:	 return HKI			/*ｲ*/;
		case FKLU			/*ゥ*/:	 return HKLU		/*ｩ*/;
		case FKU			/*ウ*/:	 return HKU			/*ｳ*/;
		case FKLE			/*ェ*/:	 return HKLE		/*ｪ*/;
		case FKE			/*エ*/:	 return HKE			/*ｴ*/;
		case FKLO			/*ォ*/:	 return HKLO		/*ｫ*/;
		case FKO			/*オ*/:	 return HKO			/*ｵ*/;
		case FKKA			/*カ*/:	 return HKKA		/*ｶ*/;
		case FKKI			/*キ*/:	 return HKKI		/*ｷ*/;
		case FKKU			/*ク*/:	 return HKKU		/*ｸ*/;
		case FKKE			/*ケ*/:	 return HKKE		/*ｹ*/;
		case FKKO			/*コ*/:	 return HKKO		/*ｺ*/;
		case FKSA			/*サ*/:	 return HKSA		/*ｻ*/;
		case FKSI			/*シ*/:	 return HKSI		/*ｼ*/;
		case FKSU			/*ス*/:	 return HKSU		/*ｽ*/;
		case FKSE			/*セ*/:	 return HKSE		/*ｾ*/;
		case FKSO			/*ソ*/:	 return HKSO		/*ｿ*/;
		case FKTA			/*タ*/:	 return HKTA		/*ﾀ*/;
		case FKTI			/*チ*/:	 return HKTI		/*ﾁ*/;
		case FKLTU			/*ッ*/:	 return HKLTU		/*ｯ*/;
		case FKTU			/*ツ*/:	 return HKTU		/*ﾂ*/;
		case FKTE			/*テ*/:	 return HKTE		/*ﾃ*/;
		case FKTO			/*ト*/:	 return HKTO		/*ﾄ*/;
		case FKNA			/*ナ*/:	 return HKNA		/*ﾅ*/;
		case FKNI			/*ニ*/:	 return HKNI		/*ﾆ*/;
		case FKNU			/*ヌ*/:	 return HKNU		/*ﾇ*/;
		case FKNE			/*ネ*/:	 return HKNE		/*ﾈ*/;
		case FKNO			/*ノ*/:	 return HKNO		/*ﾉ*/;
		case FKHA			/*ハ*/:	 return HKHA		/*ﾊ*/;
		case FKHI			/*ヒ*/:	 return HKHI		/*ﾋ*/;
		case FKHU			/*フ*/:	 return HKHU		/*ﾌ*/;
		case FKHE			/*ヘ*/:	 return HKHE		/*ﾍ*/;
		case FKHO			/*ホ*/:	 return HKHO		/*ﾎ*/;
		case FKMA			/*マ*/:	 return HKMA		/*ﾏ*/;
		case FKMI			/*ミ*/:	 return HKMI		/*ﾐ*/;
		case FKMU			/*ム*/:	 return HKMU		/*ﾑ*/;
		case FKME			/*メ*/:	 return HKME		/*ﾒ*/;
		case FKMO			/*モ*/:	 return HKMO		/*ﾓ*/;
		case FKLYA			/*ャ*/:	 return HKLYA		/*ｬ*/;
		case FKYA			/*ヤ*/:	 return HKYA		/*ﾔ*/;
		case FKLYU			/*ュ*/:	 return HKLYU		/*ｭ*/;
		case FKYU			/*ユ*/:	 return HKYU		/*ﾕ*/;
		case FKLYO			/*ョ*/:	 return HKLYO		/*ｮ*/;
		case FKYO			/*ヨ*/:	 return HKYO		/*ﾖ*/;
		case FKRA			/*ラ*/:	 return HKRA		/*ﾗ*/;
		case FKRI			/*リ*/:	 return HKRI		/*ﾘ*/;
		case FKRU			/*ル*/:	 return HKRU		/*ﾙ*/;
		case FKRE			/*レ*/:	 return HKRE		/*ﾚ*/;
		case FKRO			/*ロ*/:	 return HKRO		/*ﾛ*/;
		case FKLWA			/*ヮ*/:	 return 0;
		case FKWA			/*ワ*/:	 return HKWA		/*ﾜ*/;
		case FKWI			/*ヰ*/:	 return HKI			/*ｲ*/;
		case FKWE			/*ヱ*/:	 return HKE			/*ｴ*/;
		case FKWO			/*ヲ*/:	 return HKWO		/*ｦ*/;
		case FKN			/*ン*/:	 return HKN			/*ﾝ*/;
		case FKLKA			/*ヵ*/:	 return 0;
		case FKLKE			/*ヶ*/:	 return 0;
		case FMDOT			/*・*/:	 return HMDOT		/*･*/;
		case FLONGSOUND		/*ー*/:	 return HLONGSOUND	/*ｰ*/;
		case FKICHI			/*ヽ*/:	 return 0;
		case FKICHID		/*ヾ*/:	 return 0;
		case FKOTO			/*ヿ*/:	 return 0;
		case FDAKU			/*゛*/:	 return HDAKU		/*ﾞ*/;
		case FHANDAKU		/*゜゚゙゚゙*/:	 return HHANDAKU	/*ﾟ*/;
		case FSTOP			/*。*/:	 return HSTOP		/*｡*/;
		case FLCORNER		/*「*/:	 return HLCORNER	/*｢*/;
		case FRCORNER		/*」*/:	 return HRCORNER	/*｣*/;
		case FCOMMA			/*、*/:	 return HCOMMA		/*､*/;
		case FKGA			/*ガ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKKA/*ｶ*/;
		case FKGI			/*ギ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKKI/*ｷ*/;
		case FKGU			/*グ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKKU/*ｸ*/;
		case FKGE			/*ゲ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKKE/*ｹ*/;
		case FKGO			/*ゴ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKKO/*ｺ*/;
		case FKZA			/*ザ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKSA/*ｻ*/;
		case FKZI			/*ジ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKSI/*ｼ*/;
		case FKZU			/*ズ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKSU/*ｽ*/;
		case FKZE			/*ゼ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKSE/*ｾ*/;
		case FKZO			/*ゾ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKSO/*ｿ*/;
		case FKDA			/*ダ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKTA/*ﾀ*/;
		case FKDI			/*ヂ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKTI/*ﾁ*/;
		case FKDU			/*ヅ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKTU/*ﾂ*/;
		case FKDE			/*デ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKTE/*ﾃ*/;
		case FKDO			/*ド*/:	 *daku = HDAKU/*ﾞ*/;	 return HKTO/*ﾄ*/;
		case FKBA			/*バ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKHA/*ﾊ*/;
		case FKBI			/*ビ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKHI/*ﾋ*/;
		case FKBU			/*ブ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKHU/*ﾌ*/;
		case FKBE			/*ベ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKHE/*ﾍ*/;
		case FKBO			/*ボ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKHO/*ﾎ*/;
		case FKVU			/*ヴ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKU/*ｳ*/;
		case FKVA			/*ヷ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKWA/*ﾜ*/;
		case FKVI			/*ヸ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKI/*ｲ*/;
		case FKVE			/*ヹ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKE/*ｴ*/;
		case FKVO			/*ヺ*/:	 *daku = HDAKU/*ﾞ*/;	 return HKWO/*ｦ*/;
		case FKPI			/*ピ*/:	 *daku = HHANDAKU/*ﾟ*/;	 return HKHI/*ﾋ*/;
		case FKPA			/*パ*/:	 *daku = HHANDAKU/*ﾟ*/;	 return HKHA/*ﾊ*/;
		case FKPU			/*プ*/:	 *daku = HHANDAKU/*ﾟ*/;	 return HKHU/*ﾌ*/;
		case FKPE			/*ペ*/:	 *daku = HHANDAKU/*ﾟ*/;	 return HKHE/*ﾍ*/;
		case FKPO			/*ポ*/:	 *daku = HHANDAKU/*ﾟ*/;	 return HKHO/*ﾎ*/;
		}
	}
	else
	{
		//半角 -> 半角
		if(*daku == HDAKU/*ﾞ*/)
		{
			*daku = 1;
			switch(UTFCode)
			{
			case HKWO	/*ｦ*/:	 return FKVO		/*ヺ*/;
			case HKI	/*ｲ*/:	 return FKVI		/*ヸ*/; 
			case HKU	/*ｳ*/:	 return FKVU		/*ヴ*/; 
			case HKE	/*ｴ*/:	 return FKVE		/*ヹ*/; 
			case HKKA	/*ｶ*/:	 return FKGA		/*ガ*/; 
			case HKKI	/*ｷ*/:	 return FKGI		/*ギ*/; 
			case HKKU	/*ｸ*/:	 return FKGU		/*グ*/; 
			case HKKE	/*ｹ*/:	 return FKGE		/*ゲ*/; 
			case HKKO	/*ｺ*/:	 return FKGO		/*ゴ*/; 
			case HKSA	/*ｻ*/:	 return FKZA		/*ザ*/; 
			case HKSI	/*ｼ*/:	 return FKZI		/*ジ*/; 
			case HKSU	/*ｽ*/:	 return FKZU		/*ズ*/; 
			case HKSE	/*ｾ*/:	 return FKZE		/*ゼ*/; 
			case HKSO	/*ｿ*/:	 return FKZO		/*ゾ*/; 
			case HKTA	/*ﾀ*/:	 return FKDA		/*ダ*/; 
			case HKTI	/*ﾁ*/:	 return FKDI		/*ヂ*/; 
			case HKTU	/*ﾂ*/:	 return FKDU		/*ヅ*/; 
			case HKTE	/*ﾃ*/:	 return FKDE		/*デ*/; 
			case HKTO	/*ﾄ*/:	 return FKDO		/*ド*/; 
			case HKHA	/*ﾊ*/:	 return FKBA		/*バ*/; 
			case HKHI	/*ﾋ*/:	 return FKBI		/*ビ*/; 
			case HKHU	/*ﾌ*/:	 return FKBU		/*ブ*/; 
			case HKHE	/*ﾍ*/:	 return FKBE		/*ベ*/; 
			case HKHO	/*ﾎ*/:	 return FKBO		/*ボ*/; 
			case HKWA	/*ﾜ*/:	 return FKVA		/*ヷ*/;
			}
		}
		else if(*daku == HHANDAKU/*ﾟ*/)
		{
			*daku = 1;
			switch(UTFCode)
			{
			case HKHA	/*ﾊ*/:	 return FKPA		/*パ*/; 
			case HKHI	/*ﾋ*/:	 return FKPI		/*ピ*/; 
			case HKHU	/*ﾌ*/:	 return FKPU		/*プ*/; 
			case HKHE	/*ﾍ*/:	 return FKPE		/*ペ*/; 
			case HKHO	/*ﾎ*/:	 return FKPO		/*ポ*/; 
			}
		}
		*daku = 0;

		switch(UTFCode)
		{
		case HSTOP		/*｡*/:	 return FSTOP		/*。*/;
		case HLCORNER	/*｢*/:	 return FLCORNER	/*「*/;
		case HRCORNER	/*｣*/:	 return FRCORNER	/*」*/;
		case HCOMMA		/*､*/:	 return FCOMMA		/*、*/;
		case HMDOT		/*･*/:	 return FMDOT		/*・*/;
		case HKWO		/*ｦ*/:	 return FKWO		/*ヲ*/;
		case HKLA		/*ｧ*/:	 return FKLA		/*ァ*/;
		case HKLI		/*ｨ*/:	 return FKLI		/*ィ*/;
		case HKLU		/*ｩ*/:	 return FKLU		/*ゥ*/;
		case HKLE		/*ｪ*/:	 return FKLE		/*ェ*/;
		case HKLO		/*ｫ*/:	 return FKLO		/*ォ*/;
		case HKLYA		/*ｬ*/:	 return FKLYA		/*ャ*/;
		case HKLYU		/*ｭ*/:	 return FKLYU		/*ュ*/;
		case HKLYO		/*ｮ*/:	 return FKLYO		/*ョ*/;
		case HKLTU		/*ｯ*/:	 return FKLTU		/*ッ*/;
		case HLONGSOUND	/*ｰ*/:	 return FLONGSOUND	/*ー*/;
		case HKA		/*ｱ*/:	 return FKA			/*ア*/;
		case HKI		/*ｲ*/:	 return FKI			/*イ*/; 
		case HKU		/*ｳ*/:	 return FKU			/*ウ*/; 
		case HKE		/*ｴ*/:	 return FKE			/*エ*/; 
		case HKO		/*ｵ*/:	 return FKO			/*オ*/; 
		case HKKA		/*ｶ*/:	 return FKKA		/*カ*/; 
		case HKKI		/*ｷ*/:	 return FKKI		/*キ*/; 
		case HKKU		/*ｸ*/:	 return FKKU		/*ク*/; 
		case HKKE		/*ｹ*/:	 return FKKE		/*ケ*/; 
		case HKKO		/*ｺ*/:	 return FKKO		/*コ*/; 
		case HKSA		/*ｻ*/:	 return FKSA		/*サ*/; 
		case HKSI		/*ｼ*/:	 return FKSI		/*シ*/; 
		case HKSU		/*ｽ*/:	 return FKSU		/*ス*/; 
		case HKSE		/*ｾ*/:	 return FKSE		/*セ*/; 
		case HKSO		/*ｿ*/:	 return FKSO		/*ソ*/; 
		case HKTA		/*ﾀ*/:	 return FKTA		/*タ*/; 
		case HKTI		/*ﾁ*/:	 return FKTI		/*チ*/; 
		case HKTU		/*ﾂ*/:	 return FKTU		/*ツ*/; 
		case HKTE		/*ﾃ*/:	 return FKTE		/*テ*/; 
		case HKTO		/*ﾄ*/:	 return FKTO		/*ト*/; 
		case HKNA		/*ﾅ*/:	 return FKNA		/*ナ*/; 
		case HKNI		/*ﾆ*/:	 return FKNI		/*ニ*/; 
		case HKNU		/*ﾇ*/:	 return FKNU		/*ヌ*/; 
		case HKNE		/*ﾈ*/:	 return FKNE		/*ネ*/; 
		case HKNO		/*ﾉ*/:	 return FKNO		/*ノ*/; 
		case HKHA		/*ﾊ*/:	 return FKHA		/*ハ*/; 
		case HKHI		/*ﾋ*/:	 return FKHI		/*ヒ*/; 
		case HKHU		/*ﾌ*/:	 return FKHU		/*フ*/; 
		case HKHE		/*ﾍ*/:	 return FKHE		/*ヘ*/; 
		case HKHO		/*ﾎ*/:	 return FKHO		/*ホ*/; 
		case HKMA		/*ﾏ*/:	 return FKMA		/*マ*/; 
		case HKMI		/*ﾐ*/:	 return FKMI		/*ミ*/; 
		case HKMU		/*ﾑ*/:	 return FKMU		/*ム*/; 
		case HKME		/*ﾒ*/:	 return FKME		/*メ*/; 
		case HKMO		/*ﾓ*/:	 return FKMO		/*モ*/; 
		case HKYA		/*ﾔ*/:	 return FKYA		/*ヤ*/; 
		case HKYU		/*ﾕ*/:	 return FKYU		/*ユ*/; 
		case HKYO		/*ﾖ*/:	 return FKYO		/*ヨ*/; 
		case HKRA		/*ﾗ*/:	 return FKRA		/*ラ*/; 
		case HKRI		/*ﾘ*/:	 return FKRI		/*リ*/; 
		case HKRU		/*ﾙ*/:	 return FKRU		/*ル*/; 
		case HKRE		/*ﾚ*/:	 return FKRE		/*レ*/; 
		case HKRO		/*ﾛ*/:	 return FKRO		/*ロ*/; 
		case HKWA		/*ﾜ*/:	 return FKWA		/*ワ*/;
		case HKN		/*ﾝ*/:	 return FKN			/*ン*/;
		case HDAKU		/*ﾞ*/:	 return FDAKU		/*゛*/;
		case HHANDAKU	/*ﾟ*/:	 return FHANDAKU	/*゜*/;
		}
	}
	return 0;
}

unsigned int Selecting::ZenHanSymbol(unsigned int UTFCode, const DIRECTION direction)
{
	if( direction == TOHALF)
	{
		 //全角 -> 半角
		switch( UTFCode )
		{
		case FSPACE		: return HSPACE;
		case FICOMMA	: return HICOMMA;
		case FISTOP		: return HISTOP;
		case FCOMMA		: return HCOMMA;
		case FSTOP		: return HSTOP;
		case FMDOT		: return HMDOT;
		case FCOLON		: return HCOLON;
		case FSCOLON	: return HSCOLON;
		case FQUES		: return HQUES;
		case FEXCLA		: return HEXCLA;
		case FDAKU		: return HDAKU;
		case FHANDAKU	: return HHANDAKU;
		case FCIRCUM	: return HCIRCUM;
		case FLOW		: return HLOW;
		case FKICHI		: return HKICHI;
		case FKICHID	: return HKICHID;
		case FHICHI		: return HHICHI;
		case FHICHID	: return HHICHID;
		//カナ長音符は記号では変換しない
		//case FLONGSOUND	: return HLONGSOUND;
		case FSOLIDUS	: return HSOLIDUS;
		case FTILDE		: return HTILDE;
		case FVER		: return HVER;
		case FLSQUO		: return HLSQUO;
		case FRSQUO		: return HRSQUO;
		case FLDQUO		: return HDQUO;
		case FLPAREN	: return HLPAREN;
		case FRPAREN	: return HRPAREN;
		case FLSQUARE	: return HLSQUARE;
		case FRSQUARE	: return HRSQUARE;
		case FLCURLY	: return HLCURLY;
		case FRCURLY	: return HRCURLY;
		case FLCORNER	: return HLCORNER;
		case FRCORNER	: return HRCORNER;
		case FPLUS		: return HPLUS;
		case FHYPHEN	: return HHYPHEN;
		case FEQUALS	: return HEQUALS;
		case FLTHAN		: return HLTHAN;
		case FGTHAN		: return HGTHAN;
		case FYEN		: return HYEN;
		case FDOLL		: return HDOLL;
		case FPERCENT	: return HPERCENT;
		case FNUMBER	: return HNUMBER;
		case FAMPERSAND	: return HAMPERSAND;
		case FASTERISK	: return HASTERISK;
		case FAT		: return HAT;
		case FRARROW	: return HRARROW;
		case FLARROW	: return HLARROW;
		case FUARROW	: return HUARROW;
		case FDARROW	: return HDARROW;
		case FDHYPHEN	: return HEQUALS;
		}
	}
	else
	{
		//半角 -> 全角
		switch( UTFCode )
		{
		case 0			: return 0;
		/*
		case HKICHI		: return FKICHI;
		case HKICHID	: return FKICHID;
		case HHICHI		: return FHICHI;
		case HHICHID	: return FHICHID;
		*/
		case HSPACE		: return FSPACE;
		case HICOMMA	: return FICOMMA;
		case HISTOP		: return FISTOP;
		case HCOMMA		: return FCOMMA;
		case HSTOP		: return FSTOP;
		case HMDOT		: return FMDOT;
		case HCOLON		: return FCOLON;
		case HSCOLON	: return FSCOLON;
		case HQUES		: return FQUES;
		case HEXCLA		: return FEXCLA;
		case HDAKU		: return FDAKU;
		case HHANDAKU	: return FHANDAKU;
		case HCIRCUM	: return FCIRCUM;
		case HLOW		: return FLOW;
		case HLONGSOUND	: return FLONGSOUND;
		case HSOLIDUS	: return FSOLIDUS;
		case HTILDE		: return FTILDE;
		case HVER		: return FVER;
		case HLSQUO		: return FLSQUO;
		case HRSQUO		: return FRSQUO;
		case HDQUO		: return FLDQUO;
		case HLPAREN	: return FLPAREN;
		case HRPAREN	: return FRPAREN;
		case HLSQUARE	: return FLSQUARE;
		case HRSQUARE	: return FRSQUARE;
		case HLCURLY	: return FLCURLY;
		case HRCURLY	: return FRCURLY;
		case HLCORNER	: return FLCORNER;
		case HRCORNER	: return FRCORNER;
		case HPLUS		: return FPLUS;
		case HHYPHEN	: return FHYPHEN;
		case HEQUALS	: return FEQUALS;
		case HLTHAN		: return FLTHAN;
		case HGTHAN		: return FGTHAN;
		case HYEN		: return FYEN;
		case HDOLL		: return FDOLL;
		case HPERCENT	: return FPERCENT;
		case HNUMBER	: return FNUMBER;
		case HAMPERSAND	: return FAMPERSAND;
		case HASTERISK	: return FASTERISK;
		case HAT		: return FAT;
		case HRARROW	: return FRARROW;
		case HLARROW	: return FLARROW;
		case HUARROW	: return FUARROW;
		case HDARROW	: return FDARROW;
		}
	}
	return 0;
}


//従来のアクセス
//void Selecting::DBLClick(HWND hWnd, int pos){
//	int i=0;
//	//ダブルクリックされたところの情報
//	unsigned char curPosChar=0;
//	int startCode=0;
//	int startKind=0;
//	int startReadChar=0;
//	int readChar=0;
//	//int read;
//
//	//現在の行の情報取得
//	int line;
//	int lineStartPos;
//	//int length;
//	int inLinePos;
//	//文章の改行コードの取得
//	int nextLineCode;
//	int nextLineBuffer;//改行コードに必要なサイズ(終端\0も含む)
//	
//	//選択範囲用
//	//unsigned char asciiCode;
//	int code = 0;
//	int codeKind = 0;
//	int selectEnd = 0;
//	int selectStart = 0;
//
//	this->_hWnd = hWnd;
//	this->_pos = pos;
//
//	char *lineStr;
//	int lineLength;
//
//	//最初の文字の取得
//	curPosChar = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, this->_pos, 0);
//	//もし行の最後だったらスキップ
//	if( (curPosChar == '\r') || (curPosChar == '\n') )
//		return;
//
//	//クリックされたところの文字を取得
//	//Dprintf("ダブルクリック位置 %d\n", this->_pos);
//	//改行コードの取得
//	nextLineCode = ::SendMessage(this->_hWnd, SCI_GETEOLMODE, 0, 0);
//	if( nextLineCode == SC_EOL_CRLF )
//		nextLineBuffer = 3; //\r\n+\0
//	else
//		nextLineBuffer = 2; //\r or \n +\0
//
//	//現在の行の文字数,行中の何文字目かを取得
//	line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//	lineLength = ::SendMessage(this->_hWnd, SCI_GETCURLINE, 0, 0);
//	lineStr = (char*) new char[lineLength];
//	//ダブルクリックで選択領域が変更させられたので行内の位置が一番後ろになるので戻り値は使えない
//	SendMessage(this->_hWnd, SCI_GETCURLINE, lineLength, (LPARAM)lineStr);
//	inLinePos = this->_pos - lineStartPos;
//	lineLength -= nextLineBuffer;
//	//Dprintf("%d行 %d中%d文字目 行の初めは全体で%d文字目(UTF8)\n", line+1, lineLength, inLinePos, lineStartPos);
//
//	//現在の場所の文字種の取得
//	//utfCodeにセット 返値が1ならascii
//	startReadChar = this->GetUtf8Code(lineStr, inLinePos, NULL);
//	startKind = this->CodeKind(this->utf8Code);
//	//約物の場合、約物以外が出てくるまで次の文字から探す
//	if(startKind == this->zPunc) {
//		for(i=inLinePos + startReadChar; i<lineLength; i+=readChar)
//		{
//			readChar = this->GetUtf8Code(lineStr, i, NULL);
//			startKind = this->CodeKind(this->utf8Code);
//			if( (startKind != this->zPunc) ) {
//				break;
//			}
//		}
//	}
//	//Dprintf("Code 0x%x  Check %d\n", startCode, startKind);
//	
//
//	//終了側へ選択範囲を伸ばす、境界を探す
//	//asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
//	readChar = startReadChar;
//	for(i=inLinePos+readChar; i<lineLength; i+=readChar)
//	{
//		readChar = this->GetUtf8Code(lineStr, i, NULL);
//		codeKind = this->CodeKind(this->utf8Code);
//		if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
//			break;
//		}
//	}
//	//selectEnd = this->_pos + (i - inLinePos);
//	selectEnd = lineStartPos + i;
//	//Dprintf("選択後ろ %d文字\n", i - inLinePos);
//
//	//先頭側へ選択範囲を伸ばす
//	//asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
//	readChar = 0;
//	for(i=inLinePos; i>0; i-=readChar) {
//		readChar = this->GetUtf8Code(lineStr, i - 1, NULL);
//		codeKind = this->CodeKind(this->utf8Code);
//		//Dprintf("読み込み量 %d 読み込み位置 %d  code 0x%x check %d \n", read, readChar, code, codeKind);
//		if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
//			break;
//		}
//	}
//	selectStart = lineStartPos + i;
//	//Dprintf("選択前 %d文字\n", inLinePos - i);
//
//	delete[] lineStr;
//	::SendMessage(this->_hWnd, SCI_SETSEL, selectStart, selectEnd);
//
//
//
//	////クリックされたところの文字を取得
//	////Dprintf("ダブルクリック位置 %d\n", this->_pos);
//	////改行コードの取得
//	//nextLineCode = ::SendMessage(this->_hWnd, SCI_GETEOLMODE, 0, 0);
//	//if( nextLineCode == SC_EOL_CRLF )
//	//	nextLineBuffer = 3; //\r\n+\0
//	//else
//	//	nextLineBuffer = 2; //\r or \n +\0
//	////現在の行の文字数,行中の何文字目かを取得
//	//line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	//lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//	//length = ::SendMessage(this->_hWnd, SCI_GETCURLINE, 0, 0);
//	//inLinePos = this->_pos - lineStartPos;
//	//length -= nextLineBuffer;
//	////Dprintf("%d行 %d中%d文字目 行の初めは全体で%d文字目(UTF8)\n", line+1, length, inLinePos, lineStartPos);
//
//	////最初の文字の取得
//	//curPosChar = (unsigned char)::SendMessage(this->_hWnd, SCI_GETCHARAT, this->_pos, 0);
//	////もし行の最後だったらスキップ
//	//if( (curPosChar == '\r') || (curPosChar == '\n') )
//	//	return;
//
//	////utfCodeにセット 返値が1ならascii
//	//startReadChar = this->SetChar(this->_pos);
//	//startCode = this->GetUTFCode();
//	//startKind = this->CodeKind(startCode);
//	////約物の場合、約物以外が出てくるまで次の文字を探す
//	//if(startKind == this->zPunc) {
//	//	for(i=inLinePos; i<length; i++) {
//	//		readChar += this->SetChar(this->_pos+readChar);
//	//		code = this->GetUTFCode();
//	//		startKind = this->CodeKind(code);
//	//		if( (startKind != this->zPunc) ) {
//	//			break;
//	//		}
//	//	}
//	//}
//	////Dprintf("Code 0x%x  Check %d\n", startCode, startKind);
//	//
//
//	////後ろ側へ選択範囲を伸ばす、境界を探す
//	////asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
//	//readChar = startReadChar;
//	//for(i=inLinePos; i<length; i+=read) {
//	//	read = this->SetChar(this->_pos + readChar);
//	//	code = this->GetUTFCode();
//	//	codeKind = this->CodeKind(code);
//	//	if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
//	//		break;
//	//	}
//	//	readChar += read;
//	//}
//	//selectEnd = this->_pos + readChar;
//	////Dprintf("選択後ろ %d文字\n", readChar);
//
//	////前へ選択範囲を伸ばす
//	////asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
//	//readChar = 0;
//	//for(i=inLinePos; i>0; i-=read) {
//	//	read = this->SetChar(this->_pos - readChar - 1);
//	//	code = this->GetUTFCode();
//	//	codeKind = this->CodeKind(code);
//	//	//Dprintf("読み込み量 %d 読み込み位置 %d  code 0x%x check %d \n", read, readChar, code, codeKind);
//	//	if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
//	//		break;
//	//	}
//	//	readChar += read;
//	//}
//	//selectStart = this->_pos - readChar;
//	////Dprintf("選択前 %d文字\n", readChar);
//
//	//::SendMessage(this->_hWnd, SCI_SETSEL, selectStart, selectEnd);
//	////// restore the original targets to avoid conflicts with the search/replace functions
//	////::SendMessage(this->_hWnd, SCI_SETTARGETSTART, selectStart, 0);
//	////::SendMessage(this->_hWnd, SCI_SETTARGETEND, selectEnd, 0);
//
//	return;
//}
//void Selecting::Left(bool select){
//
//	int anchorPos;
//	int currentScintilla = -1;
//	//現在の行の情報取得
//	int line;
//	int lineStartPos;
//
//	int startCode=0;
//	int startKind=0;
//	int startReadChar=0;
//	int readChar=0;
//	//int read;
//	//int code;
//	int codeKind;
//	int caret;
//
//	int i;	
//
//	//現在のscintillaの取得 0->main 1->sub
//	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
//	if(currentScintilla == -1) return;
//	if(currentScintilla == 0)
//		this->_hWnd = this->mainScintilla;
//	else
//		this->_hWnd = this->secondScintilla;
//
//	//現在のカーソル、アンカー位置の取得
//	this->_pos = ::SendMessage(this->_hWnd, SCI_GETCURRENTPOS, 0, 0);
//	anchorPos = ::SendMessage(this->_hWnd, SCI_GETANCHOR, 0, 0);
//	//Dprintf("currentScintilla %d curPos %d anchor %d\n", currentScintilla, this->_pos, anchorPos);
//	
//	
//	//行を一度に全て取得してからに変更
//	//int lineEndPos;
//	char *lineStr;
//	int lineLength;
//	//int posLine;
//	int codeStartPos;
//	int readByte;
//
//	//現在の行の中での位置の取得
//	line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//	//Dprintf("%d行 行の初めは全体で%d文字目 現在%d文字目(UTF8)\n", line+1, this->_pos , lineStartPos);
//	//行の初めなら前の行へ
//	if( this->_pos != lineStartPos )
//	{
//		this->_pos -= lineStartPos;
//
//		lineLength = SendMessage(this->_hWnd, SCI_LINELENGTH, line, 0);
//		lineStr = (char*) new char[lineLength];
//		lineLength = SendMessage(this->_hWnd, SCI_GETLINE, line, (LPARAM)lineStr);
//
//		//lineLength = SendMessage(this->_hWnd, SCI_GETCURLINE, 0, NULL);
//		//lineStr = (char*) new char[lineLength];
//		//posLine = SendMessage(this->_hWnd, SCI_GETCURLINE, (WPARAM)lineLength, (LPARAM)lineStr);
//		//Dprintf("lineLength %d line : %s\n", lineLength, lineStr);
//		//Dprintf("nowPos %d\n", posLine);
//
//		//現在の場所の文字種の取得
//		readByte = this->GetUtf8Code(lineStr, this->_pos-1, &codeStartPos);
//		startKind = CodeKind(this->utf8Code);
//		
//		for(i=this->_pos - readByte; i>=0; i-=readByte)
//		{
//			readByte = this->GetUtf8Code(lineStr, i-1, &codeStartPos);
//			codeKind = CodeKind(this->utf8Code);
//			//Dprintf("pos %d code %d codeKind %d\n", i, this->utf8Code, codeKind);
//			if( (startKind != codeKind) || (this->hNewLine == codeKind)) {
//				break;
//			}
//		}
//		delete[] lineStr;
//
//		caret = i + lineStartPos;
//		//Dprintf("キャレットの移動 %d\n", caret);
//	}
//	else
//	{
//		//line--;
//		//lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//		caret = SendMessage(this->_hWnd, SCI_GETLINEENDPOSITION, line - 1, 0);
//		//this->_pos = lineEndPos;
//	}
//	if(select == true)
//		::SendMessage(this->_hWnd, SCI_SETSEL, anchorPos, caret);
//	else
//		::SendMessage(this->_hWnd, SCI_GOTOPOS, caret, 0);
//	
//
//	//if(1)
//	//{
//	//	line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	//	lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//	//	//Dprintf("%d行 行の初めは全体で%d文字目 現在%d文字目(UTF8)\n", line+1, this->_pos , lineStartPos);
//	//	//行の初めなら前の行へ
//	//	if( this->_pos == lineStartPos )
//	//		lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line-1, 0);
//	//}
//	//else
//	//{
//	//	lineStartPos = 0;
//	//}
//
//	//Time("1"){
//	////現在の文字と文字種の取得
//	////ひとつ前の文字から開始するため減算
//	////this->_pos--;
//	////utfCodeにセット 返値が1ならascii
//	//startReadChar = this->SetChar(this->_pos - 1);
//	//startCode = this->GetUTFCode();
//	//startKind = this->CodeKind(startCode);
//
//	////前へ
//	//for(i=this->_pos; i>lineStartPos; i-=read) {
//	//	read = this->SetChar(this->_pos - readChar - 1);
//	//	code = this->GetUTFCode();
//	//	codeKind = this->CodeKind(code);
//	//	//Dprintf("pos %d i %d code %d codeKine %d\n", this->_pos, i, code, codeKind);
//	//	//Dprintf("読み込み量 %d 読み込み位置 %d  code 0x%x check %d\n", read, readChar, code, codeKind);
//	//	if( (startKind != codeKind) || (this->hNewLine == codeKind)) {
//	//		break;
//	//	}
//	//	readChar += read;
//	//}
//	//}
//	//caret = this->_pos - readChar;
//	////Dprintf("キャレットの移動 %d\n", caret);
//
//	//if(select == true)
//	//	::SendMessage(this->_hWnd, SCI_SETSEL, anchorPos, caret);
//	//else
//	//	::SendMessage(this->_hWnd, SCI_GOTOPOS, caret, 0);
//
//	return;
//}
//void Selecting::Right(bool select){
//	int anchorPos;
//	int currentScintilla = -1;
//
//	//現在の行の情報取得
//	int line;
//	int lineEndPos;
//
//	int startCode=0;
//	int startKind=0;
//	int startReadChar=0;
//	int readChar=0;
//	//int read;
//	//int code;
//	int codeKind;
//	int caret;
//
//	int i;
//	
//	//現在のscintillaの取得 0->main 1->sub
//	::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
//	if(currentScintilla == -1) return;
//	if(currentScintilla == 0)
//		this->_hWnd = this->mainScintilla;
//	else
//		this->_hWnd = this->secondScintilla;
//
//	//現在のカーソル、アンカー位置の取得
//	this->_pos = ::SendMessage(this->_hWnd, SCI_GETCURRENTPOS, 0, 0);
//	anchorPos = ::SendMessage(this->_hWnd, SCI_GETANCHOR, 0, 0);
//	//Dprintf("currentScintilla %d curPos %d anchor %d\n", currentScintilla, this->_pos, anchorPos);
//
//
//	//行を一度に全て取得してからに変更
//	int lineStartPos;
//	char *lineStr;
//	int lineLength;
//	//int posLine;
//	int codeStartPos;
//	int readByte;
//
//	//現在の行の中での位置の取得
//	line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	lineEndPos = ::SendMessage(this->_hWnd, SCI_GETLINEENDPOSITION, line, 0);
//	lineStartPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line, 0);
//	//Dprintf("%d行 行の終わりは%d文字目 現在%d文字目(UTF8)\n", line+1, lineEndPos, this->_pos);
//	//行の終わりなら次の行へ
//	if( this->_pos != lineEndPos )
//	{
//		this->_pos -= lineStartPos;
//		lineEndPos -= lineStartPos;
//
//		lineLength = SendMessage(this->_hWnd, SCI_LINELENGTH, line, 0);
//		lineStr = (char*) new char[lineLength];
//		lineLength = SendMessage(this->_hWnd, SCI_GETLINE, line, (LPARAM)lineStr);
//
//		//現在の場所の文字種の取得
//		readByte = this->GetUtf8Code(lineStr, this->_pos, &codeStartPos);
//		startKind = CodeKind(this->utf8Code);
//		
//		for(i=this->_pos+readByte; i<lineEndPos; i+=readByte)
//		{
//			readByte = this->GetUtf8Code(lineStr, i, &codeStartPos);
//			codeKind = this->CodeKind(this->utf8Code);
//			//Dprintf("pos %d code %d codeKind %d\n", i, this->utf8Code, codeKind);
//			if( (startKind != codeKind) || (this->hNewLine == codeKind)) {
//				break;
//			}
//		}
//		delete[] lineStr;
//
//		caret = i + lineStartPos;
//		//Dprintf("キャレットの移動 %d\n", caret);
//	}
//	else
//	{
//		caret = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, ++line, 0);
//	}
//	if(select == true)
//		::SendMessage(this->_hWnd, SCI_SETSEL, anchorPos, caret);
//	else
//		::SendMessage(this->_hWnd, SCI_GOTOPOS, caret, 0);
//
//
//	//if(1)
//	//{
//	//	line = ::SendMessage(this->_hWnd, SCI_LINEFROMPOSITION, this->_pos, 0);
//	//	//lineLength = ::SendMessage(this->_hWnd, SCI_GETCURLINE, 0, 0);
//	//	lineEndPos = ::SendMessage(this->_hWnd, SCI_GETLINEENDPOSITION, line, 0);
//	//	Dprintf("%d行 行の終わりは%d文字目 現在%d文字目(UTF8)\n", line+1, lineEndPos, this->_pos);
//	//	//行の終わりなら次の行へ
//	//	if( this->_pos == lineEndPos )
//	//	{
//	//		lineEndPos = ::SendMessage(this->_hWnd, SCI_POSITIONFROMLINE, line+1, 0);
//	//	}
//	//}
//	//else
//	//{
//	//	//文章の最大の長さ
//	//	lineEndPos = ::SendMessage(this->_hWnd, SCI_GETLENGTH, 0, 0);
//	//}
//
//	////現在の文字と文字種の取得
//	////utfCodeにセット 返値が1ならascii
//	//startReadChar = this->SetChar(this->_pos);
//	//startCode = this->GetUTFCode();
//	//startKind = this->CodeKind(startCode);
//
//	////後ろへ
//	//for(i=this->_pos; i<lineEndPos; i+=read) {
//	//	read = this->SetChar(this->_pos + readChar);
//	//	code = this->GetUTFCode();
//	//	codeKind = this->CodeKind(code);
//	//	Dprintf("読み込み量 %d 読み込み位置 %d  code 0x%x check %d \n", read, readChar, code, codeKind);
//	//	if( (startKind != codeKind) && (this->_pos != i) ) {
//	//		break;
//	//	}
//	//	readChar += read;
//	//}
//	//caret = this->_pos+ readChar;
//	//Dprintf("キャレットの移動 %d\n", caret);
//
//	//if(select == true)
//	//	::SendMessage(this->_hWnd, SCI_SETSEL, anchorPos, caret);
//	//else
//	//	::SendMessage(this->_hWnd, SCI_GOTOPOS, caret, 0);
//
//	return;
//}
//高速アクセス用
void Selecting::DBLClick(SciFnDirect pSciMsg, sptr_t pSciWndData, int pos)
{
	int i=0;
	
	//ダブルクリックされたところの情報
	unsigned char curPosChar=0;
	int startCode=0;
	int startKind=0;
	int startReadChar=0;
	int readChar=0;
	//int read;

	//現在の行の情報取得
	int line;
	int lineStartPos;
	//int length;
	int inLinePos;
	//文章の改行コードの取得
	int nextLineCode;
	int nextLineBuffer;//改行コードに必要なサイズ
	const int eol = 1;//eol(終端文字\0)
	
	//選択範囲用
	//unsigned char asciiCode;
	int code = 0;
	int codeKind = 0;
	int selectEnd = 0;
	int selectStart = 0;

	//this->_hWnd = hWnd;
	this->_pos = pos;

	char *lineStr;
	int lineLength;

	//改行コードの取得
	nextLineCode = pSciMsg(pSciWndData, SCI_GETEOLMODE, 0, 0);
	if( nextLineCode == SC_EOL_CRLF )
		nextLineBuffer = 2; //\r\n
	else
		nextLineBuffer = 1; //\r or \n

	//Dprintf("ダブルクリック位置 %d\n", this->_pos);

	//現在の行の文字数,行中の何文字目かを取得
	line = pSciMsg(pSciWndData, SCI_LINEFROMPOSITION, this->_pos, 0);
	lineStartPos = pSciMsg(pSciWndData, SCI_POSITIONFROMLINE, line, 0);
	inLinePos = this->_pos - lineStartPos;
	
	//行の長さの取得
	lineLength = pSciMsg(pSciWndData, SCI_GETCURLINE, 0, 0);
	lineStr = (char*) new char[lineLength];
	//ダブルクリックで選択領域が変更させられたので行内の位置が一番後ろになるので戻り値は使えない
	pSciMsg(pSciWndData, SCI_GETCURLINE, lineLength, (LPARAM)lineStr);

	//現在の行数の取得
	int docLine = 0;
	docLine = pSciMsg(pSciWndData, SCI_GETLINECOUNT, 0, 0);

	//クリックした行が最後なら改行コードを引かない SCI_GETLINECOUNTは1start, SCI_LINEFROMPOSITIONは0start
	if( (docLine - 1) != line )
		lineLength -= nextLineBuffer;
	//終端文字\0文を処理
	--lineLength;
	//Dprintf("%d行中%d行 %d文字中%d文字目 行の初めは全体で%d文字目(UTF8)\n", docLine, line+1, lineLength, inLinePos, lineStartPos);

	//クリックした行が空行なら終了
	if( 0 == lineLength )
		return;

	//クリックされたところの文字を取得
	curPosChar = (unsigned char)pSciMsg(pSciWndData, SCI_GETCHARAT, this->_pos, 0);
	//もし行の最後だったらその前からにする
	if( (curPosChar == '\r') || (curPosChar == '\n') || (curPosChar == '\0'))
	{
		int prevReadChar;
		//return;
		prevReadChar = this->GetUtf8Code(lineStr, inLinePos-1, NULL);
		inLinePos -= prevReadChar;
		this->_pos -= prevReadChar;
		curPosChar = (unsigned char)pSciMsg(pSciWndData, SCI_GETCHARAT, this->_pos, 0);
	}
	Dprintf("%c %d %d\n", curPosChar, this->_pos, pos);


	//現在の場所の文字種の取得
	//utfCodeにセット 返値が1ならascii
	startReadChar = this->GetUtf8Code(lineStr, inLinePos, NULL);
	startKind = this->CodeKind(this->utf8Code);
	//約物の場合、約物以外が出てくるまで次の文字から探す
	if(startKind == this->zPunc) {
		for(i=inLinePos + startReadChar; i<lineLength; i+=readChar)
		{
			readChar = this->GetUtf8Code(lineStr, i, NULL);
			startKind = this->CodeKind(this->utf8Code);
			if( (startKind != this->zPunc) ) {
				break;
			}
		}
	}
	//Dprintf("Code 0x%x  Check %d\n", startCode, startKind);
	


	//終了側へ選択範囲を伸ばす、境界を探す
	//asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
	readChar = startReadChar;
	for(i=inLinePos+readChar; i<lineLength; i+=readChar)
	{
		//Dprintf("選択後ろ %d %d %d\n", readChar, i, lineLength);
		readChar = this->GetUtf8Code(lineStr, i, NULL);
		codeKind = this->CodeKind(this->utf8Code);
		if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
			break;
		}
	}
	//selectEnd = this->_pos + (i - inLinePos);
	selectEnd = lineStartPos + i;
	//Dprintf("選択後ろ %d文字\n", i - inLinePos);

	//先頭側へ選択範囲を伸ばす
	//asciiとUTF8で処理を分ける ascii->1byteごと UTF8->3 or 4byte
	readChar = 0;
	for(i=inLinePos; i>0; i-=readChar) {
		readChar = this->GetUtf8Code(lineStr, i - 1, NULL);
		codeKind = this->CodeKind(this->utf8Code);
		//Dprintf("読み込み量 %d 読み込み位置 %d  code 0x%x check %d \n", read, readChar, code, codeKind);
		if( (startKind != codeKind) && (this->zPunc != codeKind) ) {
			break;
		}
	}
	selectStart = lineStartPos + i;
	//Dprintf("選択前 %d文字\n", inLinePos - i);

	delete[] lineStr;
	pSciMsg(pSciWndData, SCI_SETSEL, selectStart, selectEnd);


	return;
}
void Selecting::Left(SciFnDirect pSciMsg, sptr_t pSciWndData,bool select){

	int anchorPos;
	int currentScintilla = -1;
	//現在の行の情報取得
	int line;
	int lineStartPos;

	int startCode=0;
	int startKind=0;
	int startReadChar=0;
	int readChar=0;
	//int read;
	//int code;
	int codeKind;
	int caret;

	int i;	

	////現在のscintillaの取得 0->main 1->sub
	//::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	//if(currentScintilla == -1) return;
	//if(currentScintilla == 0)
	//	this->_hWnd = this->mainScintilla;
	//else
	//	this->_hWnd = this->secondScintilla;

	//現在のカーソル、アンカー位置の取得
	this->_pos = pSciMsg(pSciWndData, SCI_GETCURRENTPOS, 0, 0);
	anchorPos = pSciMsg(pSciWndData, SCI_GETANCHOR, 0, 0);
	//Dprintf("currentScintilla %d curPos %d anchor %d\n", currentScintilla, this->_pos, anchorPos);
	
	
	//行を一度に全て取得してからに変更
	//int lineEndPos;
	char *lineStr;
	int lineLength;
	//int posLine;
	int codeStartPos;
	int readByte;

	//現在の行の中での位置の取得
	line = pSciMsg(pSciWndData, SCI_LINEFROMPOSITION, this->_pos, 0);
	lineStartPos = pSciMsg(pSciWndData, SCI_POSITIONFROMLINE, line, 0);
	//Dprintf("%d行 行の初めは全体で%d文字目 現在%d文字目(UTF8)\n", line+1, this->_pos , lineStartPos);
	//行の初めなら前の行へ
	if( this->_pos != lineStartPos )
	{
		this->_pos -= lineStartPos;

		lineLength = pSciMsg(pSciWndData, SCI_LINELENGTH, line, 0);
		//lineStr = (char*) new char[lineLength];
		//lineLength = pSciMsg(pSciWndData, SCI_GETLINE, line, (LPARAM)lineStr);
		this->HeapLineStr(lineLength);
		lineLength = pSciMsg(pSciWndData, SCI_GETLINE, line, (LPARAM)this->lineStr);
		lineStr = this->lineStr;

		//lineLength = pSciMsg(pSciWndData, SCI_GETCURLINE, 0, NULL);
		//lineStr = (char*) new char[lineLength];
		//posLine = pSciMsg(pSciWndData, SCI_GETCURLINE, (WPARAM)lineLength, (LPARAM)lineStr);
		//Dprintf("lineLength %d line : %s\n", lineLength, lineStr);
		//Dprintf("nowPos %d\n", posLine);

		//現在の場所の文字種の取得
		readByte = this->GetUtf8Code(lineStr, this->_pos-1, &codeStartPos);
		startKind = CodeKind(this->utf8Code);
		
		for(i=this->_pos - readByte; i>=0; i-=readByte)
		{
			readByte = this->GetUtf8Code(lineStr, i-1, &codeStartPos);
			codeKind = CodeKind(this->utf8Code);
			//Dprintf("pos %d code %d codeKind %d\n", i, this->utf8Code, codeKind);
			if( (startKind != codeKind) || (this->hNewLine == codeKind)) {
				break;
			}
		}
		//delete[] lineStr;

		caret = i + lineStartPos;
		//Dprintf("キャレットの移動 %d\n", caret);
	}
	else
	{
		//line--;
		//lineStartPos = pSciMsg(pSciWndData, SCI_POSITIONFROMLINE, line, 0);
		caret = pSciMsg(pSciWndData, SCI_GETLINEENDPOSITION, line - 1, 0);
		//this->_pos = lineEndPos;
	}
	if(select == true)
		pSciMsg(pSciWndData, SCI_SETSEL, anchorPos, caret);
	else
		pSciMsg(pSciWndData, SCI_GOTOPOS, caret, 0);
	
	return;
}
void Selecting::Right(SciFnDirect pSciMsg, sptr_t pSciWndData,bool select){
	int anchorPos;
	int currentScintilla = -1;

	//現在の行の情報取得
	int line;
	int lineEndPos;

	int startCode=0;
	int startKind=0;
	int startReadChar=0;
	int readChar=0;
	//int read;
	//int code;
	int codeKind;
	int caret;

	int i;
	
	////現在のscintillaの取得 0->main 1->sub
	//::SendMessage(this->nppHwnd, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintilla);
	//if(currentScintilla == -1) return;
	//if(currentScintilla == 0)
	//	this->_hWnd = this->mainScintilla;
	//else
	//	this->_hWnd = this->secondScintilla;

	//現在のカーソル、アンカー位置の取得
	this->_pos = pSciMsg(pSciWndData, SCI_GETCURRENTPOS, 0, 0);
	anchorPos = pSciMsg(pSciWndData, SCI_GETANCHOR, 0, 0);
	//Dprintf("currentScintilla %d curPos %d anchor %d\n", currentScintilla, this->_pos, anchorPos);


	//行を一度に全て取得してからに変更
	int lineStartPos;
	char *lineStr;
	int lineLength;
	//int posLine;
	int codeStartPos;
	int readByte;

	//現在の行の中での位置の取得
	line = pSciMsg(pSciWndData, SCI_LINEFROMPOSITION, this->_pos, 0);
	lineEndPos = pSciMsg(pSciWndData, SCI_GETLINEENDPOSITION, line, 0);
	lineStartPos = pSciMsg(pSciWndData, SCI_POSITIONFROMLINE, line, 0);
	//Dprintf("%d行 行の終わりは%d文字目 現在%d文字目(UTF8)\n", line+1, lineEndPos, this->_pos);
	//行の終わりなら次の行へ
	if( this->_pos != lineEndPos )
	{
		this->_pos -= lineStartPos;
		lineEndPos -= lineStartPos;

		lineLength = pSciMsg(pSciWndData, SCI_LINELENGTH, line, 0);
		//lineStr = (char*) new char[lineLength];
		//lineLength = pSciMsg(pSciWndData, SCI_GETLINE, line, (LPARAM)lineStr);
		this->HeapLineStr(lineLength);
		lineLength = pSciMsg(pSciWndData, SCI_GETLINE, line, (LPARAM)this->lineStr);
		lineStr = this->lineStr;

		//現在の場所の文字種の取得
		readByte = this->GetUtf8Code(lineStr, this->_pos, &codeStartPos);
		startKind = CodeKind(this->utf8Code);
		
		for(i=this->_pos+readByte; i<lineEndPos; i+=readByte)
		{
			readByte = this->GetUtf8Code(lineStr, i, &codeStartPos);
			codeKind = this->CodeKind(this->utf8Code);
			//Dprintf("pos %d code %d codeKind %d\n", i, this->utf8Code, codeKind);
			if( (startKind != codeKind) || (this->hNewLine == codeKind)) {
				break;
			}
		}
		//delete[] lineStr;

		caret = i + lineStartPos;
		//Dprintf("キャレットの移動 %d\n", caret);
	}
	else
	{
		caret = pSciMsg(pSciWndData, SCI_POSITIONFROMLINE, ++line, 0);
	}
	if(select == true)
		pSciMsg(pSciWndData, SCI_SETSEL, anchorPos, caret);
	else
		pSciMsg(pSciWndData, SCI_GOTOPOS, caret, 0);


	return;
}
bool Selecting::HeapLineStr(int length)
{
	//再作成されたらtrue
	//\0分を確保
	++length;
	if(length > this->lineStrLength)
	{
		if( this->lineStr != NULL)
			delete[] this->lineStr;
		this->lineStr = new char[length];
		this->lineStrLength = length;
		return true;
	}
	return false;
}