#include "CharOperate.h"

#include "EncodeChange.h" // ZenHanStrA用

//全角カタカナ
enum FSyllabary{
							//		jis		EUC		sjis		UNICODE	UTF8
	/*
	FDHYPHEN	= 0x30A0,	//゠	0x0000	0x0000	0x0000		0x30A0	0xE382A0
	*/
	FKLA		= 0x30A1,	//ァ	0x2521	0xA5A1	0x8340		0x30A1	0xE382A1
	FKA			= 0x30A2,	//ア	0x2522	0xA5A2	0x8341		0x30A2	0xE382A2
	FKLI		= 0x30A3,	//ィ	0x2523	0xA5A3	0x8342		0x30A3	0xE382A3
	FKI			= 0x30A4,	//イ	0x2524	0xA5A4	0x8343		0x30A4	0xE382A4
	FKLU		= 0x30A5,	//ゥ	0x2525	0xA5A5	0x8344		0x30A5	0xE382A5
	FKU			= 0x30A6,	//ウ	0x2526	0xA5A6	0x8345		0x30A6	0xE382A6
	FKLE		= 0x30A7,	//ェ	0x2527	0xA5A7	0x8346		0x30A7	0xE382A7
	FKE			= 0x30A8,	//エ	0x2528	0xA5A8	0x8347		0x30A8	0xE382A8
	FKLO		= 0x30A9,	//ォ	0x2529	0xA5A9	0x8348		0x30A9	0xE382A9
	FKO			= 0x30AA,	//オ	0x252A 	0xA5AA	0x8349		0x30AA	0xE382AA
	FKKA		= 0x30AB,	//カ	0x252B 	0xA5AB	0x834A 		0x30AB	0xE382AB
	FKGA		= 0x30AC,	//ガ	0x252C 	0xA5AC	0x834B 		0x30AC	0xE382AC
	FKKI		= 0x30AD,	//キ	0x252D 	0xA5AD	0x834C 		0x30AD	0xE382AD
	FKGI		= 0x30AE,	//ギ	0x252E 	0xA5AE	0x834D 		0x30AE	0xE382AE
	FKKU		= 0x30AF,	//ク	0x252F	0xA5AF	0x834E 		0x30AF	0xE382AF
	FKGU		= 0x30B0,	//グ	0x2530	0xA5B0	0x834F		0x30B0	0xE382B0
	FKKE		= 0x30B1,	//ケ	0x2531	0xA5B1	0x8350		0x30B1	0xE382B1
	FKGE		= 0x30B2,	//ゲ	0x2532	0xA5B2	0x8351		0x30B2	0xE382B2
	FKKO		= 0x30B3,	//コ	0x2533	0xA5B3	0x8352		0x30B3	0xE382B3
	FKGO		= 0x30B4,	//ゴ	0x2534	0xA5B4	0x8353		0x30B4	0xE382B4
	FKSA		= 0x30B5,	//サ	0x2535	0xA5B5	0x8354		0x30B5	0xE382B5
	FKZA		= 0x30B6,	//ザ	0x2536	0xA5B6	0x8355		0x30B6	0xE382B6
	FKSI		= 0x30B7,	//シ	0x2537	0xA5B7	0x8356		0x30B7	0xE382B7
	FKZI		= 0x30B8,	//ジ	0x2538	0xA5B8	0x8357		0x30B8	0xE382B8
	FKSU		= 0x30B9,	//ス	0x2539	0xA5B9	0x8358		0x30B9	0xE382B9
	FKZU		= 0x30BA,	//ズ	0x253A 	0xA5BA	0x8359		0x30BA	0xE382BA
	FKSE		= 0x30BB,	//セ	0x253B 	0xA5BB	0x835A 		0x30BB	0xE382BB
	FKZE		= 0x30BC,	//ゼ	0x253C 	0xA5BC	0x835B 		0x30BC	0xE382BC
	FKSO		= 0x30BD,	//ソ	0x253D 	0xA5BD	0x835C 		0x30BD	0xE382BD
	FKZO		= 0x30BE,	//ゾ	0x253E 	0xA5BE	0x835D 		0x30BE	0xE382BE
	FKTA		= 0x30BF,	//タ	0x253F	0xA5BF	0x835E 		0x30BF	0xE382BF
	FKDA		= 0x30C0,	//ダ	0x2540	0xA5C0	0x835F		0x30C0	0xE38380
	FKTI		= 0x30C1,	//チ	0x2541	0xA5C1	0x8360		0x30C1	0xE38381
	FKDI		= 0x30C2,	//ヂ	0x2542	0xA5C2	0x8361		0x30C2	0xE38382
	FKLTU		= 0x30C3,	//ッ	0x2543	0xA5C3	0x8362		0x30C3	0xE38383
	FKTU		= 0x30C4,	//ツ	0x2544	0xA5C4	0x8363		0x30C4	0xE38384
	FKDU		= 0x30C5,	//ヅ	0x2545	0xA5C5	0x8364		0x30C5	0xE38385
	FKTE		= 0x30C6,	//テ	0x2546	0xA5C6	0x8365		0x30C6	0xE38386
	FKDE		= 0x30C7,	//デ	0x2547	0xA5C7	0x8366		0x30C7	0xE38387
	FKTO		= 0x30C8,	//ト	0x2548	0xA5C8	0x8367		0x30C8	0xE38388
	FKDO		= 0x30C9,	//ド	0x2549	0xA5C9	0x8368		0x30C9	0xE38389
	FKNA		= 0x30CA,	//ナ	0x254A 	0xA5CA	0x8369		0x30CA	0xE3838A
	FKNI		= 0x30CB,	//ニ	0x254B 	0xA5CB	0x836A 		0x30CB	0xE3838B
	FKNU		= 0x30CC,	//ヌ	0x254C 	0xA5CC	0x836B 		0x30CC	0xE3838C
	FKNE		= 0x30CD,	//ネ	0x254D 	0xA5CD	0x836C 		0x30CD	0xE3838D
	FKNO		= 0x30CE,	//ノ	0x254E 	0xA5CE	0x836D 		0x30CE	0xE3838E
	FKHA		= 0x30CF,	//ハ	0x254F	0xA5CF	0x836E 		0x30CF	0xE3838F
	FKBA		= 0x30D0,	//バ	0x2550	0xA5D0	0x836F		0x30D0	0xE38390
	FKPA		= 0x30D1,	//パ	0x2551	0xA5D1	0x8370		0x30D1	0xE38391
	FKHI		= 0x30D2,	//ヒ	0x2552	0xA5D2	0x8371		0x30D2	0xE38392
	FKBI		= 0x30D3,	//ビ	0x2553	0xA5D3	0x8372		0x30D3	0xE38393
	FKPI		= 0x30D4,	//ピ	0x2554	0xA5D4	0x8373		0x30D4	0xE38394
	FKHU		= 0x30D5,	//フ	0x2555	0xA5D5	0x8374		0x30D5	0xE38395
	FKBU		= 0x30D6,	//ブ	0x2556	0xA5D6	0x8375		0x30D6	0xE38396
	FKPU		= 0x30D7,	//プ	0x2557	0xA5D7	0x8376		0x30D7	0xE38397
	FKHE		= 0x30D8,	//ヘ	0x2558	0xA5D8	0x8377		0x30D8	0xE38398
	FKBE		= 0x30D9,	//ベ	0x2559	0xA5D9	0x8378		0x30D9	0xE38399
	FKPE		= 0x30DA,	//ペ	0x255A 	0xA5DA	0x8379		0x30DA	0xE3839A
	FKHO		= 0x30DB,	//ホ	0x255B 	0xA5DB	0x837A 		0x30DB	0xE3839B
	FKBO		= 0x30DC,	//ボ	0x255C 	0xA5DC	0x837B 		0x30DC	0xE3839C
	FKPO		= 0x30DD,	//ポ	0x255D 	0xA5DD	0x837C 		0x30DD	0xE3839D
	FKMA		= 0x30DE,	//マ	0x255E 	0xA5DE	0x837D 		0x30DE	0xE3839E
	FKMI		= 0x30DF,	//ミ	0x255F	0xA5DF	0x837E 		0x30DF	0xE3839F
	FKMU		= 0x30E0,	//ム	0x2560	0xA5E0	0x8380		0x30E0	0xE383A0
	FKME		= 0x30E1,	//メ	0x2561	0xA5E1	0x8381		0x30E1	0xE383A1
	FKMO		= 0x30E2,	//モ	0x2562	0xA5E2	0x8382		0x30E2	0xE383A2
	FKLYA		= 0x30E3,	//ャ	0x2563	0xA5E3	0x8383		0x30E3	0xE383A3
	FKYA		= 0x30E4,	//ヤ	0x2564	0xA5E4	0x8384		0x30E4	0xE383A4
	FKLYU		= 0x30E5,	//ュ	0x2565	0xA5E5	0x8385		0x30E5	0xE383A5
	FKYU		= 0x30E6,	//ユ	0x2566	0xA5E6	0x8386		0x30E6	0xE383A6
	FKLYO		= 0x30E7,	//ョ	0x2567	0xA5E7	0x8387		0x30E7	0xE383A7
	FKYO		= 0x30E8,	//ヨ	0x2568	0xA5E8	0x8388		0x30E8	0xE383A8
	FKRA		= 0x30E9,	//ラ	0x2569	0xA5E9	0x8389		0x30E9	0xE383A9
	FKRI		= 0x30EA,	//リ	0x256A 	0xA5EA	0x838A 		0x30EA	0xE383AA
	FKRU		= 0x30EB,	//ル	0x256B 	0xA5EB	0x838B 		0x30EB	0xE383AB
	FKRE		= 0x30EC,	//レ	0x256C 	0xA5EC	0x838C 		0x30EC	0xE383AC
	FKRO		= 0x30ED,	//ロ	0x256D 	0xA5ED	0x838D 		0x30ED	0xE383AD
	FKLWA		= 0x30EE,	//ヮ	0x256E 	0xA5EE	0x838E 		0x30EE	0xE383AE
	FKWA		= 0x30EF,	//ワ	0x256F	0xA5EF	0x838F		0x30EF	0xE383AF
	FKWI		= 0x30F0,	//ヰ	0x2570	0xA5F0	0x8390		0x30F0	0xE383B0
	FKWE		= 0x30F1,	//ヱ	0x2571	0xA5F1	0x8391		0x30F1	0xE383B1
	FKWO		= 0x30F2,	//ヲ	0x2572	0xA5F2	0x8392		0x30F2	0xE383B2
	FKN			= 0x30F3,	//ン	0x2573	0xA5F3	0x8393		0x30F3	0xE383B3
	FKVU		= 0x30F4,	//ヴ	0x2574	0xA5F4	0x8394		0x30F4	0xE383B4
	FKLKA		= 0x30F5,	//ヵ	0x2575	0xA5F5	0x8395		0x30F5	0xE383B5
	FKLKE		= 0x30F6,	//ヶ	0x2576	0xA5F6	0x8396		0x30F6	0xE383B6
	FKVA		= 0x30F7,	//ヷ	0x0000	0x0000	0x0000		0x30F7	0xE383B7
	FKVI		= 0x30F8,	//ヸ	0x0000	0x0000	0x0000		0x30F8	0xE383B8
	FKVE		= 0x30F9,	//ヹ	0x0000	0x0000	0x0000		0x30F9	0xE383B9
	FKVO		= 0x30FA,	//ヺ	0x0000	0x0000	0x0000		0x30FA	0xE383BA
	/*
	FMDOT		= 0x30FB,	//・	0x2126	0xA1A6	0x8145		0x30FB	0xE383BB
	FLONGSOUND	= 0x30FC,	//ー	0x213C	0xA1BC	0x815B		0x30FC	0xE383BC
	FKICHI		= 0x30FD,	//ヽ	0x2133	0xA1B3	0x8152		0x30FD	0xE383BD
	FKICHID		= 0x30FE,	//ヾ	0x2134	0xA1B4	0x8153		0x30FE	0xE383BE
	FKOTO		= 0x30FF,	//ヿ	0x0000	0x0000	0x0000		0x30FF	0xE383BF
	*/
	FSyllabaryStart = FKLA,
	FSyllabaryEnd	= FKVO
};
//全角記号
enum FSymbol{
							//		jis		EUC		sjis		UNICODE	UTF8
	FSPACE		= 0x3000,	//　	0x2121	0xA1A1	0x8140		0x3000	0xE38080
	FICOMMA		= 0x3001,	//、	0x2122	0xA1A2	0x8141		0x3001	0xE38081
	FISTOP		= 0x3002,	//。	0x2123	0xA1A3	0x8142		0x3002	0xE38082
	FCOMMA		= 0xFF0C,	//，	0x2124	0xA1A4	0x8143		0xFF0C	0xEFBC8C
	FSTOP		= 0xFF0E,	//．	0x2125	0xA1A5	0x8144		0xFF0E	0xEFBC8E
	FMDOT		= 0x30FB,	//・	0x2126	0xA1A6	0x8145		0x30FB	0xE383BB //UTF カタカナ
	FCOLON		= 0xFF1A,	//：	0x2127	0xA1A7	0x8146		0xFF1A	0xEFBC9A
	FSCOLON		= 0xFF1B,	//；	0x2128	0xA1A8	0x8147		0xFF1B	0xEFBC9B
	FQUES		= 0xFF1F,	//？	0x2129	0xA1A9	0x8148		0xFF1F	0xEFBC9F
	FEXCLA		= 0xFF01,	//！	0x212A	0xA1AA	0x8149		0xFF01	0xEFBC81
	FDAKU		= 0x309B,	//゛	0x212B	0xA1AB	0x814A		0x309B	0xE3829B //UTF ひらがな
	FHANDAKU	= 0x309C,	//゜	0x212C	0xA1AC	0x814B		0x309C	0xE3829C //UTF ひらがな
	FCIRCUM		= 0xFF3E,	//＾	0x2130	0xA1B0	0x814F		0xFF3E	0xEFBCBE
	FLOW		= 0xFF3F,	//＿	0x2132	0xA1B2	0x8151		0xFF3F	0xEFBCBF
	FKICHI		= 0x30FD,	//ヽ	0x2133	0xA1B3	0x8152		0x30FD	0xE383BD //UTF カタカナ
	FKICHID		= 0x30FE,	//ヾ	0x2134	0xA1B4	0x8153		0x30FE	0xE383BE //UTF カタカナ
	FHICHI		= 0x309D,	//ゝ	0x2135	0xA1B5	0x8154		0x309D	0xE3829D //UTF ひらがな
	FHICHID		= 0x309E,	//ゞ	0x2136	0xA1B6	0x8155		0x309E	0xE3829E //UTF ひらがな
	FLONGSOUND	= 0x30FC,	//ー	0x213C	0xA1BC	0x815B		0x30FC	0xE383BC //UTF カタカナ
	FSOLIDUS	= 0xFF0F,	//／	0x213F	0xA1BF	0x815E		0xFF0F	0xEFBC8F
	FTILDE		= 0xFF5E,	//～	0x2141	0xA1C1	0x8160		0xFF5E	0xEFBD9E
	FVER		= 0xFF5C,	//｜	0x2143	0xA1C3	0x8162		0xFF5C	0xEFBD9C
	FLSQUO		= 0x2018,	//‘	0x2146	0xA1C6	0x8165		0x2018	0xE28098
	FRSQUO		= 0x2019,	//’	0x2147	0xA1C7	0x8166		0x2019	0xE28099
	FLDQUO		= 0x201D,	//”	0x2149	0xA1C9	0x8168		0x201D	0xE2809D
	FLPAREN		= 0xFF08,	//（	0x214A	0xA1CA	0x8169		0xFF08	0xEFBC88
	FRPAREN		= 0xFF09,	//）	0x214B	0xA1CB	0x816A		0xFF09	0xEFBC89
	FLSQUARE	= 0xFF3B,	//［	0x214E	0xA1CE	0x816D		0xFF3B	0xEFBCBB
	FRSQUARE	= 0xFF3D,	//］	0x214F	0xA1CF	0x816E		0xFF3D	0xEFBCBD
	FLCURLY		= 0xFF5B,	//｛	0x2150	0xA1D0	0x816F		0xFF5B	0xEFBD9B
	FRCURLY		= 0xFF5D,	//｝	0x2151	0xA1D1	0x8170		0xFF5D	0xEFBD9D
	FLCORNER	= 0x300C,	//「	0x2156	0xA1D6	0x8175		0x300C	0xE3808C
	FRCORNER	= 0x300D,	//」	0x2157	0xA1D7	0x8176		0x300D	0xE3808D
	FPLUS		= 0xFF0B,	//＋	0x215C	0xA1DC	0x817B		0xFF0B	0xEFBC8B
	FHYPHEN		= 0xFF0D,	//－	0x215D	0xA1DD	0x817C		0xFF0D	0xEFFC8D
	FEQUALS		= 0xFF1D,	//＝	0x2161	0xA1E1	0x8181		0xFF1D	0xEFBC9D
	FLTHAN		= 0xFF1C,	//＜	0x2163	0xA1E3	0x8183		0xFF1C	0xEFBC9C
	FGTHAN		= 0xFF1E,	//＞	0x2164	0xA1E4	0x8184		0xFF1E	0xEFBC9E
	FYEN		= 0xFFE5,	//￥	0x216F	0xA1EF	0x818F		0xFFE5	0xEFBFA5
	FDOLL		= 0xFF04,	//＄	0x2170	0xA1F0	0x8190		0xFF04	0xEFBC84
	FPERCENT	= 0xFF05,	//％	0x2173	0xA1F3	0x8193		0xFF05	0xEFBC85
	FNUMBER		= 0xFF03,	//＃	0x2174	0xA1F4	0x8194		0xFF03	0xEFBC83
	FAMPERSAND	= 0xFF06,	//＆	0x2175	0xA1F5	0x8195		0xFF06	0xEFBC86
	FASTERISK	= 0xFF0A,	//＊	0x2176	0xA1F6	0x8196		0xFF0A	0xEFBC8A
	FAT			= 0xFF20,	//＠	0x2177	0xA1F7	0x8197		0xFF20	0xEFBCA0
	FRARROW		= 0x2192,	//→	0x222A	0xA2AA	0x81A8		0x2192	0xE28692
	FLARROW		= 0x2190,	//←	0x222B	0xA2AB	0x81A9		0x2190	0xE28690
	FUARROW		= 0x2191,	//↑	0x222C	0xA2AC	0x81AA		0x2191	0xE28691
	FDARROW		= 0x2193,	//↓	0x222D	0xA2AD	0x81AB		0x2193	0xE28693
	FYORI		= 0x309F,	//ゟ	0x0000	0x0000	0x0000		0x309F	0xE3829F //UTF ひらがな
	FDHYPHEN	= 0x30A0,	//゠	0x0000	0x0000	0x0000		0x30A0	0xE382A0 //UTF カタカナ
	FKOTO		= 0x30FF,	//ヿ	0x0000	0x0000	0x0000		0x30FF	0xE383BF //UTF カタカナ
	FSymbolStart	= FSPACE,
	FSymbolEnd		= FKOTO
};

//半角カタカナ
enum HSyllabary{
							//		jis			EUC			sjis		UNICODE		UTF8
	/*
	HISTOP		= 0xFF61,	//｡		0x21		0xA1		0x8EA1		0xFF61		0xEFBDA1
	HLCORNER	= 0xFF62,	//｢		0x22		0xA2		0x8EA2		0xFF62		0xEFBDA2
	HRCORNER	= 0xFF63,	//｣		0x23		0xA3		0x8EA3		0xFF63		0xEFBDA3
	HICOMMA		= 0xFF64,	//､		0x24		0xA4		0x8EA4		0xFF64		0xEFBDA4
	HMDOT		= 0xFF65,	//･		0x25		0xA5		0x8EA5		0xFF65		0xEFBDA5
	*/
	HKWO		= 0xFF66,	//ｦ		0x26		0xA6		0x8EA6		0xFF66		0xEFBDA6
	HKLA		= 0xFF67,	//ｧ		0x27		0xA7		0x8EA7		0xFF67		0xEFBDA7
	HKLI		= 0xFF68,	//ｨ		0x28		0xA8		0x8EA8		0xFF68		0xEFBDA8
	HKLU		= 0xFF69,	//ｩ		0x29		0xA9		0x8EA9		0xFF69		0xEFBDA9
	HKLE		= 0xFF6A,	//ｪ		0x2A		0xAA		0x8EAA		0xFF6A		0xEFBDAA
	HKLO		= 0xFF6B,	//ｫ		0x2B		0xAB		0x8EAB		0xFF6B		0xEFBDAB
	HKLYA		= 0xFF6C,	//ｬ		0x2C		0xAC		0x8EAC		0xFF6C		0xEFBDAC
	HKLYU		= 0xFF6D,	//ｭ		0x2D		0xAD		0x8EAD		0xFF6D		0xEFBDAD
	HKLYO		= 0xFF6E,	//ｮ		0x2E		0xAE		0x8EAE		0xFF6E		0xEFBDAE
	HKLTU		= 0xFF6F,	//ｯ		0x2F		0xAF		0x8EAF		0xFF6F		0xEFBDAF
	HKA			= 0xFF71,	//ｱ		0x31		0xB1		0x8EB1		0xFF71		0xEFBDB1
	HKI			= 0xFF72,	//ｲ		0x32		0xB2		0x8EB2		0xFF72		0xEFBDB2
	HKU			= 0xFF73,	//ｳ		0x33		0xB3		0x8EB3		0xFF73		0xEFBDB3
	HKE			= 0xFF74,	//ｴ		0x34		0xB4		0x8EB4		0xFF74		0xEFBDB4
	HKO			= 0xFF75,	//ｵ		0x35		0xB5		0x8EB5		0xFF75		0xEFBDB5
	HKKA		= 0xFF76,	//ｶ		0x36		0xB6		0x8EB6		0xFF76		0xEFBDB6
	HKKI		= 0xFF77,	//ｷ		0x37		0xB7		0x8EB7		0xFF77		0xEFBDB7
	HKKU		= 0xFF78,	//ｸ		0x38		0xB8		0x8EB8		0xFF78		0xEFBDB8
	HKKE		= 0xFF79,	//ｹ		0x39		0xB9		0x8EB9		0xFF79		0xEFBDB9
	HKKO		= 0xFF7A,	//ｺ		0x3A		0xBA		0x8EBA		0xFF7A		0xEFBDBA
	HKSA		= 0xFF7B,	//ｻ		0x3B		0xBB		0x8EBB		0xFF7B		0xEFBDBB
	HKSI		= 0xFF7C,	//ｼ		0x3C		0xBC		0x8EBC		0xFF7C		0xEFBDBC
	HKSU		= 0xFF7D,	//ｽ		0x3D		0xBD		0x8EBD		0xFF7D		0xEFBDBD
	HKSE		= 0xFF7E,	//ｾ		0x3E		0xBE		0x8EBE		0xFF7E		0xEFBDBE
	HKSO		= 0xFF7F,	//ｿ		0x3F		0xBF		0x8EBF		0xFF7F		0xEFBDBF
	HKTA		= 0xFF80,	//ﾀ		0x40		0xC0		0x8EC0		0xFF80		0xEFBE80
	HKTI		= 0xFF81,	//ﾁ		0x41		0xC1		0x8EC1		0xFF81		0xEFBE81
	HKTU		= 0xFF82,	//ﾂ		0x42		0xC2		0x8EC2		0xFF82		0xEFBE82
	HKTE		= 0xFF83,	//ﾃ		0x43		0xC3		0x8EC3		0xFF83		0xEFBE83
	HKTO		= 0xFF84,	//ﾄ		0x44		0xC4		0x8EC4		0xFF84		0xEFBE84
	HKNA		= 0xFF85,	//ﾅ		0x45		0xC5		0x8EC5		0xFF85		0xEFBE85
	HKNI		= 0xFF86,	//ﾆ		0x46		0xC6		0x8EC6		0xFF86		0xEFBE86
	HKNU		= 0xFF87,	//ﾇ		0x47		0xC7		0x8EC7		0xFF87		0xEFBE87
	HKNE		= 0xFF88,	//ﾈ		0x48		0xC8		0x8EC8		0xFF88		0xEFBE88
	HKNO		= 0xFF89,	//ﾉ		0x49		0xC9		0x8EC9		0xFF89		0xEFBE89
	HKHA		= 0xFF8A,	//ﾊ		0x4A		0xCA		0x8ECA		0xFF8A		0xEFBE8A
	HKHI		= 0xFF8B,	//ﾋ		0x4B		0xCB		0x8ECB		0xFF8B		0xEFBE8B
	HKHU		= 0xFF8C,	//ﾌ		0x4C		0xCC		0x8ECC		0xFF8C		0xEFBE8C
	HKHE		= 0xFF8D,	//ﾍ		0x4D		0xCD		0x8ECD		0xFF8D		0xEFBE8D
	HKHO		= 0xFF8E,	//ﾎ		0x4E		0xCE		0x8ECE		0xFF8E		0xEFBE8E
	HKMA		= 0xFF8F,	//ﾏ		0x4F		0xCF		0x8ECF		0xFF8F		0xEFBE8F
	HKMI		= 0xFF90,	//ﾐ		0x50		0xD0		0x8ED0		0xFF90		0xEFBE90
	HKMU		= 0xFF91,	//ﾑ		0x51		0xD1		0x8ED1		0xFF91		0xEFBE91
	HKME		= 0xFF92,	//ﾒ		0x52		0xD2		0x8ED2		0xFF92		0xEFBE92
	HKMO		= 0xFF93,	//ﾓ		0x53		0xD3		0x8ED3		0xFF93		0xEFBE93
	HKYA		= 0xFF94,	//ﾔ		0x54		0xD4		0x8ED4		0xFF94		0xEFBE94
	HKYU		= 0xFF95,	//ﾕ		0x55		0xD5		0x8ED5		0xFF95		0xEFBE95
	HKYO		= 0xFF96,	//ﾖ		0x56		0xD6		0x8ED6		0xFF96		0xEFBE96
	HKRA		= 0xFF97,	//ﾗ		0x57		0xD7		0x8ED7		0xFF97		0xEFBE97
	HKRI		= 0xFF98,	//ﾘ		0x58		0xD8		0x8ED8		0xFF98		0xEFBE98
	HKRU		= 0xFF99,	//ﾙ		0x59		0xD9		0x8ED9		0xFF99		0xEFBE99
	HKRE		= 0xFF9A,	//ﾚ		0x5A		0xDA		0x8EDA		0xFF9A		0xEFBE9A
	HKRO		= 0xFF9B,	//ﾛ		0x5B		0xDB		0x8EDB		0xFF9B		0xEFBE9B
	HKWA		= 0xFF9C,	//ﾜ		0x5C		0xDC		0x8EDC		0xFF9C		0xEFBE9C
	HKN			= 0xFF9D,	//ﾝ		0x5D		0xDD		0x8EDD		0xFF9D		0xEFBE9D
	/*
	HDAKU		= 0xFF9E,	//ﾞ		0x5E		0xDE		0x8EDE		0xFF9E		0xEFBE9E
	HHANDAKU	= 0xFF9F,	//ﾟ		0x5F		0xDF		0x8EDF		0xFF9F		0xEFBE9F
	*/
	HSyllabaryStart	= HKWO,
	HSyllabaryEnd	= HKN
};
//半角記号
enum HSymbol{
							//		jis			EUC			sjis		UNICODE		UTF8
	HSPACE		= 0x20,		// 		0x20		0x20		0x0020		0x0020		0x000020
	HEXCLA		= 0x21,		//!		0x21		0x21		0x0021		0x0021		0x000021
	HDQUO		= 0x22,		//"		0x22		0x22		0x0022		0x0022		0x000022
	HNUMBER		= 0x23,		//#		0x23		0x23		0x0023		0x0023		0x000023
	HDOLL		= 0x24,		//$		0x24		0x24		0x0024		0x0024		0x000024
	HPERCENT	= 0x25,		//%		0x25		0x25		0x0025		0x0025		0x000025
	HAMPERSAND	= 0x26,		//&		0x26		0x26		0x0026		0x0026		0x000026
	HLSQUO		= 0x27,		//'		0x27		0x27		0x0027		0x0027		0x000027
	HLPAREN		= 0x28,		//(		0x28		0x28		0x0028		0x0028		0x000028
	HRPAREN		= 0x29,		//)		0x29		0x29		0x0029		0x0029		0x000029
	HASTERISK	= 0x2A,		//*		0x2A		0x2A		0x002A		0x002A		0x00002A
	HPLUS		= 0x2B,		//+		0x2B		0x2B		0x002B		0x002B		0x00002B
	HCOMMA		= 0x2C,		//,		0x2C		0x2C		0x002C		0x002C		0x00002C
	HHYPHEN		= 0x2D,		//-		0x2D		0x2D		0x002D		0x002D		0x00002D
	HSTOP		= 0x2E,		//.		0x2E		0x2E		0x002E		0x002E		0x00002E
	HSOLIDUS	= 0x2F,		///		0x2F		0x2F		0x002F		0x002F		0x00002F
	HCOLON		= 0x3A,		//:		0x3A		0x3A		0x003A		0x003A		0x00003A
	HSCOLON		= 0x3B,		//;		0x3B		0x3B		0x003B		0x003B		0x00003B
	HLTHAN		= 0x3C,		//<		0x3C		0x3C		0x003C		0x003C		0x00003C
	HEQUALS		= 0x3D,		//=		0x3D		0x3D		0x003D		0x003D		0x00003D
	HGTHAN		= 0x3E,		//>		0x3E		0x3E		0x003E		0x003E		0x00003E
	HQUES		= 0x3F,		//?		0x3F		0x3F		0x003F		0x003F		0x00003F
	HAT			= 0x40,		//@		0x40		0x40		0x0040		0x0040		0x000040
	HLSQUARE	= 0x5B,		//[		0x5B		0x5B		0x005B		0x005B		0x00005B
	HYEN		= 0x5C,		//\		0x5C		0x5C		0x005C		0x005C		0x00005C
	HRSQUARE	= 0x5D,		//]		0x5D		0x5D		0x005D		0x005D		0x00005D
	HCIRCUM		= 0x5E,		//^		0x5E		0x5E		0x005E		0x005E		0x00005E
	HLOW		= 0x5F,		//_		0x5F		0x5F		0x005F		0x005F		0x00005F
	HRSQUO		= 0x60,		//`		0x60		0x60		0x0060		0x0060		0x000060
	HLCURLY		= 0x7B,		//{		0x7B		0x7B		0x007B		0x007B		0x00007B
	HVER		= 0x7C,		//|		0x7C		0x7C		0x007C		0x007C		0x00007C
	HRCURLY		= 0x7D,		//}		0x7D		0x7D		0x007D		0x007D		0x00007D
	HTILDE		= 0x7E,		//~		0x7E		0x7E		0x007E		0x007E		0x00007E
	HISTOP		= 0xFF61,	//｡		0x21		0xA1		0x8EA1		0xFF61		0xEFBDA1 //半角カタカナ
	HLCORNER	= 0xFF62,	//｢		0x22		0xA2		0x8EA2		0xFF62		0xEFBDA2 //半角カタカナ
	HRCORNER	= 0xFF63,	//｣		0x23		0xA3		0x8EA3		0xFF63		0xEFBDA3 //半角カタカナ
	HICOMMA		= 0xFF64,	//､		0x24		0xA4		0x8EA4		0xFF64		0xEFBDA4 //半角カタカナ
	HMDOT		= 0xFF65,	//･		0x25		0xA5		0x8EA5		0xFF65		0xEFBDA5 //半角カタカナ
	HLONGSOUND	= 0xFF70,	//ｰ		0x30		0xB0		0x8EB0		0xFF70		0xEFBDB0 //半角カタカナ
	HDAKU		= 0xFF9E,	//ﾞ		0x5E		0xDE		0x8EDE		0xFF9E		0xEFBE9E //半角カタカナ
	HHANDAKU	= 0xFF9F,	//ﾟ		0x5F		0xDF		0x8EDF		0xFF9F		0xEFBE9F //半角カタカナ
	HRARROW		= 0xFFE9,	//￩		0x00		0x00		0x0000		0xFFE9		0xEFBFA9
	HLARROW		= 0xFFEA,	//￪		0x00		0x00		0x0000		0xFFEA		0xEFBFAA
	HUARROW		= 0xFFEB,	//￫		0x00		0x00		0x0000		0xFFEB		0xEFBFAB
	HDARROW		= 0xFFEC,	//￬		0x00		0x00		0x0000		0xFFEC		0xEFBFAC
	HKICHI		= 0x00,		//ヽ全	0x00		0x00		0x0000		0x0000		0x000000
	HKICHID		= 0x00,		//ヾ全	0x00		0x00		0x0000		0x0000		0x000000
	HHICHI		= 0x00,		//ゝ全	0x00		0x00		0x0000		0x0000		0x000000
	HHICHID		= 0x00,		//ゞ全	0x00		0x00		0x0000		0x0000		0x000000
	HSymbolStart	= HSPACE,
	HSymbolEnd		= HDARROW
};

//ひらがな
enum FHiragana{
						//		jis		EUC		sjis		UNICODE	UTF8
	FHLA		=0x3041,//ぁ	0x2421	0xA4A1	0x829F		0x3041	0xE38181
	/*
	FHA			=0x3042,//あ	0x2422	0xA4A2	0x82A0		0x3042	0xE38182
	FHLI		=0x3043,//ぃ	0x2423	0xA4A3	0x82A1		0x3043	0xE38183
	FHI			=0x3044,//い	0x2424	0xA4A4	0x82A2		0x3044	0xE38184
	FHLU		=0x3045,//ぅ	0x2425	0xA4A5	0x82A3		0x3045	0xE38185
	FHU			=0x3046,//う	0x2426	0xA4A6	0x82A4		0x3046	0xE38186
	FHLE		=0x3047,//ぇ	0x2427	0xA4A7	0x82A5		0x3047	0xE38187
	FHE			=0x3048,//え	0x2428	0xA4A8	0x82A6		0x3048	0xE38188
	FHLO		=0x3049,//ぉ	0x2429	0xA4A9	0x82A7		0x3049	0xE38189
	FHO			=0x304A,//お	0x242A	0xA4AA	0x82A8		0x304A	0xE3818A
	FHKA		=0x304B,//か	0x242B	0xA4AB	0x82A9		0x304B	0xE3818B
	FHGA		=0x304C,//が	0x242C	0xA4AC	0x82AA		0x304C	0xE3818C
	FHKI		=0x304D,//き	0x242D	0xA4AD	0x82AB		0x304D	0xE3818D
	FHGI		=0x304E,//ぎ	0x242E	0xA4AE	0x82AC		0x304E	0xE3818E
	FHKU		=0x304F,//く	0x242F	0xA4AF	0x82AD		0x304F	0xE3818F
	FHGU		=0x3050,//ぐ	0x2430	0xA4B0	0x82AE		0x3050	0xE38190
	FHKE		=0x3051,//け	0x2431	0xA4B1	0x82AF		0x3051	0xE38191
	FHGE		=0x3052,//げ	0x2432	0xA4B2	0x82B0		0x3052	0xE38192
	FHKO		=0x3053,//こ	0x2433	0xA4B3	0x82B1		0x3053	0xE38193
	FHGO		=0x3054,//ご	0x2434	0xA4B4	0x82B2		0x3054	0xE38194
	FHSA		=0x3055,//さ	0x2435	0xA4B5	0x82B3		0x3055	0xE38195
	FHZA		=0x3056,//ざ	0x2436	0xA4B6	0x82B4		0x3056	0xE38196
	FHSI		=0x3057,//し	0x2437	0xA4B7	0x82B5		0x3057	0xE38197
	FHZI		=0x3058,//じ	0x2438	0xA4B8	0x82B6		0x3058	0xE38198
	FHSU		=0x3059,//す	0x2439	0xA4B9	0x82B7		0x3059	0xE38199
	FHZU		=0x305A,//ず	0x243A	0xA4BA	0x82B8		0x305A	0xE3819A
	FHSE		=0x305B,//せ	0x243B	0xA4BB	0x82B9		0x305B	0xE3819B
	FHZE		=0x305C,//ぜ	0x243C	0xA4BC	0x82BA		0x305C	0xE3819C
	FHSO		=0x305D,//そ	0x243D	0xA4BD	0x82BB		0x305D	0xE3819D
	FHZO		=0x305E,//ぞ	0x243E	0xA4BE	0x82BC		0x305E	0xE3819E
	FHTA		=0x305F,//た	0x243F	0xA4BF	0x82BD		0x305F	0xE3819F
	FHDA		=0x3060,//だ	0x2440	0xA4C0	0x82BE		0x3060	0xE381A0
	FHTI		=0x3061,//ち	0x2441	0xA4C1	0x82BF		0x3061	0xE381A1
	FHDI		=0x3062,//ぢ	0x2442	0xA4C2	0x82C0		0x3062	0xE381A2
	FHLTU		=0x3063,//っ	0x2443	0xA4C3	0x82C1		0x3063	0xE381A3
	FHTU		=0x3064,//つ	0x2444	0xA4C4	0x82C2		0x3064	0xE381A4
	FHDU		=0x3065,//づ	0x2445	0xA4C5	0x82C3		0x3065	0xE381A5
	FHTE		=0x3066,//て	0x2446	0xA4C6	0x82C4		0x3066	0xE381A6
	FHDE		=0x3067,//で	0x2447	0xA4C7	0x82C5		0x3067	0xE381A7
	FHTO		=0x3068,//と	0x2448	0xA4C8	0x82C6		0x3068	0xE381A8
	FHDO		=0x3069,//ど	0x2449	0xA4C9	0x82C7		0x3069	0xE381A9
	FHNA		=0x306A,//な	0x244A	0xA4CA	0x82C8		0x306A	0xE381AA
	FHNI		=0x306B,//に	0x244B	0xA4CB	0x82C9		0x306B	0xE381AB
	FHNU		=0x306C,//ぬ	0x244C	0xA4CC	0x82CA		0x306C	0xE381AC
	FHNE		=0x306D,//ね	0x244D	0xA4CD	0x82CB		0x306D	0xE381AD
	FHNO		=0x306E,//の	0x244E	0xA4CE	0x82CC		0x306E	0xE381AE
	FHHA		=0x306F,//は	0x244F	0xA4CF	0x82CD		0x306F	0xE381AF
	FHBA		=0x3070,//ば	0x2450	0xA4D0	0x82CE		0x3070	0xE381B0
	FHPA		=0x3071,//ぱ	0x2451	0xA4D1	0x82CF		0x3071	0xE381B1
	FHHI		=0x3072,//ひ	0x2452	0xA4D2	0x82D0		0x3072	0xE381B2
	FHBI		=0x3073,//び	0x2453	0xA4D3	0x82D1		0x3073	0xE381B3
	FHPI		=0x3074,//ぴ	0x2454	0xA4D4	0x82D2		0x3074	0xE381B4
	FHHU		=0x3075,//ふ	0x2455	0xA4D5	0x82D3		0x3075	0xE381B5
	FHBU		=0x3076,//ぶ	0x2456	0xA4D6	0x82D4		0x3076	0xE381B6
	FHPU		=0x3077,//ぷ	0x2457	0xA4D7	0x82D5		0x3077	0xE381B7
	FHHE		=0x3078,//へ	0x2458	0xA4D8	0x82D6		0x3078	0xE381B8
	FHBE		=0x3079,//べ	0x2459	0xA4D9	0x82D7		0x3079	0xE381B9
	FHPE		=0x307A,//ぺ	0x245A	0xA4DA	0x82D8		0x307A	0xE381BA
	FHHO		=0x307B,//ほ	0x245B	0xA4DB	0x82D9		0x307B	0xE381BB
	FHBO		=0x307C,//ぼ	0x245C	0xA4DC	0x82DA		0x307C	0xE381BC
	FHPO		=0x307D,//ぽ	0x245D	0xA4DD	0x82DB		0x307D	0xE381BD
	FHMA		=0x307E,//ま	0x245E	0xA4DE	0x82DC		0x307E	0xE381BE
	FHMI		=0x307F,//み	0x245F	0xA4DF	0x82DD		0x307F	0xE381BF
	FHMU		=0x3080,//む	0x2460	0xA4E0	0x82DE		0x3080	0xE38280
	FHME		=0x3081,//め	0x2461	0xA4E1	0x82DF		0x3081	0xE38281
	FHMO		=0x3082,//も	0x2462	0xA4E2	0x82E0		0x3082	0xE38282
	FHLYA		=0x3083,//ゃ	0x2463	0xA4E3	0x82E1		0x3083	0xE38283
	FHYA		=0x3084,//や	0x2464	0xA4E4	0x82E2		0x3084	0xE38284
	FHLYU		=0x3085,//ゅ	0x2465	0xA4E5	0x82E3		0x3085	0xE38285
	FHYU		=0x3086,//ゆ	0x2466	0xA4E6	0x82E4		0x3086	0xE38286
	FHLYO		=0x3087,//ょ	0x2467	0xA4E7	0x82E5		0x3087	0xE38287
	FHYO		=0x3088,//よ	0x2468	0xA4E8	0x82E6		0x3088	0xE38288
	FHRA		=0x3089,//ら	0x2469	0xA4E9	0x82E7		0x3089	0xE38289
	FHRI		=0x308A,//り	0x246A	0xA4EA	0x82E8		0x308A	0xE3828A
	FHRU		=0x308B,//る	0x246B	0xA4EB	0x82E9		0x308B	0xE3828B
	FHRE		=0x308C,//れ	0x246C	0xA4EC	0x82EA		0x308C	0xE3828C
	FHRO		=0x308D,//ろ	0x246D	0xA4ED	0x82EB		0x308D	0xE3828D
	FHLWA		=0x308E,//ゎ	0x246E	0xA4EE	0x82EC		0x308E	0xE3828E
	FHWA		=0x308F,//わ	0x246F	0xA4EF	0x82ED		0x308F	0xE3828F
	FHWI		=0x3090,//ゐ	0x2470	0xA4F0	0x82EE		0x3090	0xE38290
	FHWE		=0x3091,//ゑ	0x2471	0xA4F1	0x82EF		0x3091	0xE38291
	FHWO		=0x3092,//を	0x2472	0xA4F2	0x82F0		0x3092	0xE38292
	FHN			=0x3093,//ん	0x2473	0xA4F3	0x82F1		0x3093	0xE38293
	*//*
	FHVU		=0x3094,//ゔ								0x3094	0xE38294
	FHLKA		=0x3095,//ゕ								0x3095	0xE38295
	*/
	FHLKE		=0x3096,//ゖ								0x3096	0xE38296
	/*
	FDAKU		=0x309B,//゛	0x212B	0xA1AB	0x814A		0x309B	0xE3829B
	FHANDAKU	=0x309C,//゜	0x212C	0xA1AC	0x814B		0x309C	0xE3829C
	FKICHI		=0x309D,//ゝ	0x2135	0xA1B5	0x8154		0x309D	0xE3829D
	FKICHID		=0x309E,//ゞ	0x2136	0xA1B6	0x8155		0x309E	0xE3829E
	*//*
	FYORI		=0x309F,//ゟ								0x309F	0xE3829F
	*/
	FHiraganaStart	= FHLA,
	FHiraganaEnd	= FHLKE
};

//漢字
enum FKanji{
										//jis				EUC				sjis			UNICODE				UTF8
	//全角漢字1
	FKanjiStart1	=0x2E80,//⺀			//0x3021,//亜		0xB0A1,//亜		0x889F,//亜		//0x2E80,//⺀		0xE2BA80,//⺀
	FKanjiEnd1		=0x2FDF,//　部首	//0x7426,//熙		0xF4A6,//熙		0x9FFC,//滌		//0x2FDF,//　部首	0xE2BF9F,//　部首
	//全角漢字2
	FKanjiStart2	=0x3400,//㐀			//0x0000,//			0x0000,//  		0xE040,//漾		//0x3400,//㐀		0xE39080,//㐀
	FKanjiEnd2		=0x9FBB,//龻			//0x0000,//			0x0000,//  		0xEAA4,//熙		//0x9FBB,//龻		0xE9BEBB,//龻
	//全角漢字3
	FKanjiStart3	=0xF900,//豈		//0x0000,//			0x0000,//  		0x0000,//		//0xF900,//豈		0xEFA480,//豈
	FKanjiEnd3		=0xFA60 //頻		//0x0000,//			0x0000,//  		0x0000,//		//0xFA60,//頻		0xEFA9AA,//頻
};

const unsigned int STARTEND = 2;
const unsigned int CODESTART = 0;
const unsigned int CODEEND = 1;

//半角
const unsigned int hEscArea[STARTEND] 		= { 0x0,		0x1F }; /*NULL - US*/
const unsigned int hUpAlphaArea[STARTEND]	= { 0x41,		0x5A }; /*A - Z*/
const unsigned int hLoAlphaArea[STARTEND]	= { 0x61,		0x7A }; /*a - z*/
const unsigned int hNumArea[STARTEND]		= { 0x30,		0x39 }; /*0 - 9*/
const unsigned int hNewLines[]				= { 0x0A, 0x0c, 0x0d }; /*\n \f \r*/
const unsigned int hSpaces[]				= { 0x09, 0x20 }; /*\t SP*/
const unsigned int hPuncs[]					= { 0x5F }; /*_ -0x2D*/
const unsigned int hPuncsCount				= sizeof(hPuncs)/sizeof(hPuncs[0]);

//半角カタカナ
const unsigned int hKataArea[STARTEND]		= { HSyllabaryStart,	HSyllabaryEnd };/*ｦ - ﾝ*/
const unsigned int hKataEtcs[]				= { HEQUALS, HISTOP, HLCORNER, HRCORNER, HICOMMA, HMDOT, HLONGSOUND, HDAKU, HHANDAKU };/*= ｡ ｢ ｣ ､ ･ ｰ ﾞ ﾟ*/
const unsigned int hKataEtcsCount			= sizeof(hKataEtcs)/sizeof(hKataEtcs[0]);
const unsigned int hKataDakus[]				= { HDAKU,		HHANDAKU };
const unsigned int hKataDakusCount			= sizeof(hKataDakus)/sizeof(hKataDakus[0]);

//全角
const unsigned int zHiraArea[STARTEND]		= { FHiraganaStart,		FHiraganaEnd };/*ぁ - ゖ*/
const unsigned int zHiraEtcs[]				= { FDAKU, FHANDAKU, FKICHI, FKICHID, FYORI };/* ゛ ゜ ゝ ゞ ゟ *///ひらがなでは通常長音符(ー)は使用しない
const unsigned int zHiraEtcsCount			= sizeof(zHiraEtcs) / sizeof(zHiraEtcs[0]);
const unsigned int zKataArea[STARTEND]		= { FKLA,		FKVO };/*ァ  ヺ*/
const unsigned int zKataEtcs[]				= { FMDOT, FLONGSOUND, FKICHI, FKICHID, FKOTO };/* ・ ー ヽ ヾ ヿ */
const unsigned int zKataEtcsCount			= sizeof(zKataEtcs) / sizeof(zKataEtcs[0]);
const unsigned int zKanjiArea[][STARTEND] 	= { { FKanjiStart1, FKanjiEnd1 }, { FKanjiStart2, FKanjiEnd2 }, { FKanjiStart3, FKanjiEnd3 } };
const unsigned int zKanjiLine				= sizeof(zKanjiArea)/sizeof(zKanjiArea[0]);
const unsigned int zNumArea[STARTEND]		= { 0xFF10,		0xFF19 };
const unsigned int zUpAlphaArea[STARTEND]	= { 0xFF21,		0xFF3A };
const unsigned int zLoAlphaArea[STARTEND]	= { 0xFF41,		0xFF5A };
const unsigned int zSpaces[]				= { FSPACE };
const unsigned int zSpacesCount				= sizeof(zSpaces) / sizeof(zSpaces[0]);
const unsigned int zPuncs[]				= {
	0x2010, 0x2011, 0x2012, 0x2013, 0x2014, 0x2015,	//ハイフン
	0x2053, 0x301C, 0x3030,							//波ダッシュ
	0xFF5E,											//全角チルダ
	0x30FC, 0xFF70,									//長音符
	0xFF3F											//アンダーバー
};
const unsigned int zPuncsCount			= sizeof(zPuncs)/sizeof(zPuncs[0]);
const unsigned int zOdoris[]				= {
	//々, 〱, 〲, 〻, ゝ, ゞ, ヽ, ヾ
	0x3005, 0x3031, 0x3032, 0x303B, 0x309D, 0x309E, 0x30FD,	0x30FE
};
const unsigned int zOdorisCount			= sizeof(zOdoris)/sizeof(zOdoris[0]);


int CodeKind(unsigned int c, int closely)
{
	int codeKind;
	int i;
	codeKind = CodeClosely(c);
	
	if(closely == 0)
	{
		if(codeKind < Zenkaku)
		{
			switch(codeKind)
			{
			case hEtc:
				//半角
				for(i=0;i<(int)hPuncsCount;i++)
				{
					if( hPuncs[i] == c)
						codeKind = hWord;
				}
				break;
			case hLoAlpha:
			case hUpAlpha:
			case hNum:
				codeKind = hWord;
				break;
			case hSpace:
			case hNewLine:
				codeKind = hEtc;
				break;
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
				for(i=0;i<(int)zOdorisCount;i++)
				{
					if( zOdoris[i] == c)
						codeKind = zKanji;
				}
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

int CodeClosely(unsigned int c)
{	
	int i;
	if(c > 0x0080)
	{
		//漢字の判定
		for(i=0; i<zKanjiLine; i++)
		{
			if( zKanjiArea[i][CODESTART] <= c && c <= zKanjiArea[i][CODEEND] )
				return zKanji;/*全角漢字*/
		}
		if(		 zHiraArea[CODESTART]		<=c && c<=zHiraArea[CODEEND]	)			return zHira;	/*全角ひらがな*/
		else if( zKataArea[CODESTART]		<=c && c<=zKataArea[CODEEND]	)			return zKata;	/*全角カタカナ*/
		else if( zUpAlphaArea[CODESTART]	<=c && c<=zUpAlphaArea[CODEEND]	)			return zUpAlpha;/*全角英字(大)*/
		else if( zLoAlphaArea[CODESTART]	<=c && c<=zLoAlphaArea[CODEEND]	)			return zLoAlpha;/*全角英字(小)*/
		else if( zNumArea[CODESTART]		<=c && c<=zNumArea[CODEEND]		)			return zNum;	/*全角数字*/
		else if( hKataArea[CODESTART]		<=c && c<=hKataArea[CODEEND]	)			return hKata;	/*半角カタカナ*/
		else
		{
			for(i=0; i<(int)zHiraEtcsCount; i++)
			{
				if( c == zHiraEtcs[i] )
					return zHiraEtc;/*全角ひらがな記号*/
			}
			for(i=0; i<(int)zKataEtcsCount; i++)
			{
				if( c == zKataEtcs[i] )
					return zKataEtc;/*全角カタカナ記号*/
			}
			for(i=0; i<(int)zSpacesCount; i++)
			{
				if( c == zSpaces[i] )
					return zSpace;	/*全角スペース*/
			}
			for(i=0; i<(int)hKataEtcsCount; i++)
			{
				if( c == hKataEtcs[i] )
					return hKataEtc;/*半角カタカナ記号*/	
			}
			return zEtc;	/*全角記号*/
		}
	}
	else
	{
		if(		 hEscArea[CODESTART]			<= c && c <= hEscArea[CODEEND]		)
		{
			for(i=0; i<(sizeof(hNewLines) / sizeof(hNewLines[0])); i++)
			{
				if( c == hNewLines[i] )
					return hNewLine;/*改行文字*/
			}
			return hEsc;	/*制御文字*/
		}
		else if( hUpAlphaArea[CODESTART]		<= c && c <= hUpAlphaArea[CODEEND]	)	return hUpAlpha;/*半角英字(大)*/
		else if( hLoAlphaArea[CODESTART]		<= c && c <= hLoAlphaArea[CODEEND]	)	return hLoAlpha;/*半角英字(小)*/
		else if( hNumArea[CODESTART]			<= c && c <= hNumArea[CODEEND]		)	return hNum;	/*半角数字*/
		else
		{
			for(i=0; i<(sizeof(hSpaces) / sizeof(hSpaces[0])); i++)
			{
				if( c == hSpaces[i] )
					return hSpace;	/*スペースSP \t*/
			}
			return hEtc;	/*半角記号*/
		}
	}
}




//全角->半角文字列
int ZenHanStrW(const wchar_t *src, size_t srcSize, wchar_t *dest, size_t destSize, int opt, const DIRECTION direction)
{
	int i = 0;
	int bufSize = 0;

	unsigned int daku = 0;
	unsigned int code = 0;
	//サイズが0のときは終端文字が出てくるまで
	while(*(src+i) != 0 &&
		 (srcSize == 0 || i < (int)srcSize) &&
		 (destSize == 0 || bufSize < (int)destSize)
		 )
	{
		daku = *(src+i+1);
		code = ZenHan( *(src+i), direction, opt, &daku);
		//サイズのみ計測
		if( destSize == 0 || *dest == NULL)
		{
			if( code == 0)
				bufSize++;
			else
			{		
				bufSize++;
				//daku (全角の半濁、濁点文字) or (半角で次の文字が濁点半濁点なら0違うなら1)
				if( daku == 1) //半角でかつ次の文字が濁点半濁点の場合
				{
					i++;
				}
				else if( daku != 0 )//全角で現在の文字が濁点半濁点の場合
				{
					bufSize++;
				}
			}
		}
		else
		{
			if( code == 0)
			{
				dest[bufSize] = *(src+i);
				bufSize++;
			}
			else
			{
				dest[bufSize] = code;
				bufSize++;
		
				//daku (全角の半濁、濁点文字) or (半角で次の文字が濁点半濁点なら0違うなら1)
				if( daku == 1) //半角でかつ次の文字が濁点半濁点の場合
				{
					i++;
				}
				else if( daku != 0 )//全角で現在の文字が濁点半濁点の場合
				{
					dest[bufSize] = daku;
					bufSize++;
				}
			}
		}
		i++;
	}
	
	/*
	if( direction == TOHALF )
	{
		//全角 -> 半角
		unsigned int daku = 0;
		unsigned int code = 0;
		//サイズが0のときは終端文字が出てくるまで
		while(*(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
		{
			daku = 0;
			code = ZenHan( *(src+i), direction, opt, &daku);
			//サイズのみ計測
			if( destSize == 0 || *dest == NULL)
			{
				bufSize++;
				//0以外なら場合次の文字が濁点半濁点なのでバッファを増やす
				if( daku != 0)
					bufSize++;
			}
			else
			{
				if( code != 0 )
					*(dest + bufSize) = code;
				else
					*(dest + bufSize) = *(src+i);
				bufSize++;
	
				if( daku != 0)
				{
					*(dest + bufSize) = daku;
					bufSize++;
				}					
			}
			i++;
		}
	}
	else
	{
		//半角-> 全角
		unsigned int code = 0;
		unsigned int daku = 0;
		while(*(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
		{
			daku = *(src+i+1);
			code = ZenHan( *(src+i), direction, opt, &daku);
			//サイズのみ計測
			if( destSize == 0 || *dest == NULL)
			{
				bufSize++;
				if( code != 0 )
				{
					//dakuが0の場合次の文字が濁点だったので今の文字と濁点を結合されたのでソースを進める
					if( daku == 0)
						i++;
				}
			}
			else
			{
				if( code != 0 )
				{
					*(dest + bufSize) = code;
					if( daku == 0)
						i++;	
				}
				else
				{
					*(dest + bufSize) = *(src+i);
				}
				bufSize++;		
			}
			i++;
		}
	}
	*/
	
	//終端文字分
	if( destSize != 0 && dest != NULL)
		*(dest + bufSize) = 0;
	bufSize++;
	return bufSize;
}

//Utf8の場合charをwcharに置き換えるためEncodeChange.hを読み込む必要がある、使わないならコメントアウトする
int ZenHanStrA(const char *src, size_t srcSize, char *dest, size_t destSize, int opt, const DIRECTION direction)
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
		readByte = CharUtf8CodeByte( (src+i) );
		code = Utf8ToUtf16( (src+i) );

		dakuReadByte = CharUtf8CodeByte( (src+i+readByte) );
		daku = Utf8ToUtf16( (src+i+readByte) );
		
		changeCode = ZenHan( code, direction, opt, &daku);
		
		//0 or NULL でサイズ計測のみ
		if( destSize == 0 || dest == NULL)
		{
			//置き換わるか( 0なら置き換わらない )
			if( changeCode == 0)
				bufSize += readByte;
			else
			{
				bufSize += UnicodeToUtf8(changeCode, NULL );
				//daku (全角の半濁、濁点文字) or (半角で次の文字が濁点半濁点なら0違うなら1)
				if( daku == 1) //半角でかつ次の文字が濁点半濁点の場合
				{
					i += 3;
				}
				else if( daku != 0 )//全角で現在の文字が濁点半濁点の場合
				{
					//濁点半濁点は確実に3バイト文字なので確定
					//bufSize += UnicodeToUtf8(daku, NULL);
					bufSize += 3;
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
				bufSize += UnicodeToUtf8(changeCode, (dest+bufSize) );
				if( daku == 1)
				{
					i += 3;
				}
				else if( daku != 0 )
				{
					bufSize += UnicodeToUtf8(daku, (dest+bufSize) );
				}
			}
			
		}
		i += readByte;
	}
	/*
	//全角 -> 半角
	if( direction == TOHALF)
	{
		while( *(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
		{
			daku = 0;
			readByte = CharUtf8CodeByte( (src+i) );
			code = Utf8ToUtf16( (src+i) );
			changeCode = ZenHan( code, direction, opt, &daku);
			//置き換わるか( 0なら置き換わらない )
			if( changeCode == 0)
			{
				//0 or NULL でサイズ計測のみ
				if( destSize != 0 && dest != NULL)
				{					
					for(j=0; j<readByte; j++)
						dest[bufSize+j] = *(src+i+j);
				}
				bufSize += readByte;
			}
			else
			{
				if( destSize == 0 || dest == NULL)
				{
					bufSize += UnicodeToUtf8(changeCode, NULL );
					//今の文字が濁点、半濁点かどうか0以外なら濁点半濁点->バッファを増やす
					if( daku != 0)
					{
						//bufSize += UnicodeToUtf8(daku, NULL);
						//濁点半濁点は確実に3バイト文字なので確定
						bufSize += 3;
					}
				}
				else
				{
					bufSize += UnicodeToUtf8(changeCode, (dest+bufSize) );
					if( daku != 0)
						bufSize += UnicodeToUtf8(daku, (dest+bufSize) );
				}
			}
			i += readByte;
		}
	}
	//半角 -> 全角
	else
	{
		while( *(src+i) != 0 && ( (srcSize == 0) || ( i < (int)srcSize) ) )
		{
			readByte = CharUtf8CodeByte( (src+i) );
			code = Utf8ToUtf16( (src+i) );

			dakuReadByte = CharUtf8CodeByte( (src+i+readByte) );
			daku = Utf8ToUtf16( (src+i+readByte) );

			changeCode = ZenHan( code, direction, opt, &daku);
			//置き換わるか( 0なら置き換わらない )
			if( changeCode == 0)
			{
				//0 or NULL でサイズ計測のみ
				if( destSize != 0 && dest != NULL)
				{
					for(j=0; j<readByte; j++)
						dest[bufSize+j] = *(src+i+j);
				}
				bufSize += readByte;
			}
			else
			{
				if( destSize == 0 || dest == NULL)
					bufSize += UnicodeToUtf8(changeCode, NULL );
				else
					bufSize += UnicodeToUtf8(changeCode, (dest+bufSize) );
				
				//次の文字が濁点、半濁点かどうか、0なら濁点半濁点->結合されるので次の文字へを増やす
				if( daku == 0)
				{
					//濁点半濁点は確実に3バイト文字なので確定
					//bufSize += UnicodeToUtf8(daku, (dest+bufSize) );
					i += dakuReadByte;
				}
			}
			i += readByte;
		}
	}
	*/
	//終端文字分
	if( destSize != 0 && dest != NULL)
		*(dest + bufSize) = 0;
	bufSize++;
	return bufSize;
}
unsigned int ZenHan(const unsigned int code, const DIRECTION direction, int opt, unsigned int *daku)
{
	int codeKind;
	int changeCode = 0;

	codeKind = CodeClosely(code);
	if( direction == TOHALF )
	{
		*daku = 0;
		//全角 -> 半角
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
		//半 -> 全
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
unsigned int ZenHanKata(const unsigned int code, unsigned int *daku, const DIRECTION direction)
{
	//全角 or 半角
	//hKataArea[CODESTART] > code || code > hKataArea[CODEEND]
	if( direction == TOHALF)
	{
		*daku = 0;
		 //全角 -> 半角
		switch(code)
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
		case FDHYPHEN		/*゠*/:	 return HEQUALS		/*=*/;
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
			switch(code)
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
			switch(code)
			{
			case HKHA	/*ﾊ*/:	 return FKPA		/*パ*/; 
			case HKHI	/*ﾋ*/:	 return FKPI		/*ピ*/; 
			case HKHU	/*ﾌ*/:	 return FKPU		/*プ*/; 
			case HKHE	/*ﾍ*/:	 return FKPE		/*ペ*/; 
			case HKHO	/*ﾎ*/:	 return FKPO		/*ポ*/; 
			}
		}
		*daku = 0;

		switch(code)
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
unsigned int ZenHanSymbol(const unsigned int code, const DIRECTION direction)
{
	if( direction == TOHALF)
	{
		 //全角 -> 半角
		switch( code )
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
		//記号では長音符を変換しない
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
		//半角-> 全角
		switch( code )
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

void LoUpCase(wchar_t *src, size_t srcSize, int opt)
{
	int codeKind = 0;
	int i = 0;

	while( *(src+i) != 0 || ( (unsigned int)i<srcSize && i!=0) )
	{
		codeKind = CodeClosely( *(src+i) );
		switch( codeKind )
		{
		case hUpAlpha:
			if( opt & HLoCaseAlpha)
				*(src+i) = *(src+i) - hUpAlphaArea[CODESTART] + hLoAlphaArea[CODESTART];
			break;
		case hLoAlpha:
			if( opt & HUpCaseAlpha)
				*(src+i) = *(src+i) - hLoAlphaArea[CODESTART] + hUpAlphaArea[CODESTART];
			break;
		case zUpAlpha:
			if( opt & ZLoCaseAlpha)
				*(src+i) = *(src+i) - zUpAlphaArea[CODESTART] + zLoAlphaArea[CODESTART];
			break;
		case zLoAlpha:
			if( opt & ZUpCaseAlpha)
				*(src+i) = *(src+i) - zLoAlphaArea[CODESTART] + zUpAlphaArea[CODESTART];
			break;
		}
		i++;
	}
	return;
}

void TitleCase(wchar_t *src, size_t srcSize, int opt)
{
	int codeKind = 0;
	int i = 0;
	int space = 0;
	while( *(src+i) != 0 || ( (unsigned int)i<srcSize && i!=0) )
	{
		codeKind = CodeClosely( *(src+i) );
		switch( codeKind )
		{
		case hUpAlpha:
		case hLoAlpha:
			if( opt & HTitleCase)
			{
				//前の文字がスペース,改行なら英字大文字でそれ以外なら全て小文字
				if( space == 1)
				{
					if( codeKind == hLoAlpha )
						*(src+i) = *(src+i) - hLoAlphaArea[CODESTART] + hUpAlphaArea[CODESTART];
					space = 0;
				}
				else
				{
					if( codeKind == hUpAlpha )
						*(src+i) = *(src+i) - hUpAlphaArea[CODESTART] + hLoAlphaArea[CODESTART];
				}
			}
			break;
		case zUpAlpha:
		case zLoAlpha:
			if( opt & ZTitleCase)
			{
				//前の文字がスペース,改行なら英字大文字でそれ以外なら全て小文字
				if( space == 1)
				{
					if( codeKind == zLoAlpha )
						*(src+i) = *(src+i) - zLoAlphaArea[CODESTART] + zUpAlphaArea[CODESTART];
					space = 0;
				}
				else
				{
					if( codeKind == zUpAlpha )
						*(src+i) = *(src+i) - zUpAlphaArea[CODESTART] + zLoAlphaArea[CODESTART];
				}
			}
			break;
		case zSpace:
		case hSpace:
		case hNewLine:
			space = 1;
			break;
		case zHira:
		case zEtc:
		case zKanji:
		case zKata:
		default:
			space = 0;
			break;
		}
		i++;
	}
	return;
}