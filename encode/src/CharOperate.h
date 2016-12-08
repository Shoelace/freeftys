
#include "Encode.h"


enum CODE{
	error = -1,
	Hankaku,
	hEtc, hEsc, hWord, hAlpha, hUpAlpha, hLoAlpha, hNum, hKata, hPunc, hSpace, hNewLine, hKataEtc,
	Zenkaku,
	zEtc, zEsc, zWord, zAlpha, zUpAlpha, zLoAlpha, zNum, zKata, zPunc, zSpace, zHira, zKanji, zHiraEtc, zKataEtc,
	AllCodeCount
};


//コード種類判定(英字大小をまとめるなどを行う)
int CodeKind(unsigned int c, int closely);
//コード種類判定(詳細に判定)
int CodeClosely(unsigned int c);

//半角英字のみ,全角英字のみ,全て,
//HTitleCase=1<<6, ZTitleCase=1<<7, ZHTitleCase=1<<8先頭のみ(全角,半角)大文字
enum LUAlphaOpt{
	HUpCaseAlpha	= 0x01,		HLoCaseAlpha	= 0x01<<1,	//0000 0001(1	0000 0010(2
	ZUpCaseAlpha	= 0x01<<2,	ZLoCaseAlpha	= 0x01<<3,	//0000 0100(4	0000 1000(8
	ZHUpCaseAlpha	= HUpCaseAlpha&ZUpCaseAlpha,
	ZHLoCaseAlpha	= HLoCaseAlpha&ZLoCaseAlpha,
	ZTitleCase		= 0x01<<4,	HTitleCase		= 0x01<<5,	//0001 0000(16	0010 0000(32
	ZHTitleCase 	= ZTitleCase & HTitleCase
};
void LoUpCase(wchar_t *str, size_t strSize, int opt);
void TitleCase(wchar_t *str, size_t strSize, int opt);

// opt bit処理
enum ZenHanOpt{ 
	ZHLoAlpha	=0x01,		//1 -> LoAlpha
	ZHUpAlpha	=0x01<<1,	//2 -> UpAlpha
	ZHNum		=0x01<<2,	//4 -> Num
	ZHKata		=0x01<<3,	//8 -> kata
	ZHSymbol	=0x01<<4,	//16-> symbol
	ZHAll		=0xFF
};
// direction
typedef enum{
	TOHALF,	//0-> 全->半
	TOFULL,	//1-> 半->全
	TOHIRA, //2-> カタ->ひら
	TOKATA	//3-> ひら->カタ
}DIRECTION;

//全角<->半角文字列//unicode wchar_t用 return 必要バイト
int ZenHanStrW(const wchar_t *str, size_t strSize, wchar_t *dest, size_t destSize, int opt, const DIRECTION direction);
//全角<->半角文字列//unicode UTF8用 return 必要バイト
int ZenHanStrA(const char *str, size_t strSize, char *dest, size_t destSize, int opt, const DIRECTION direction);
//全角<->半角
unsigned int ZenHan(const unsigned int code, const DIRECTION direction, int opt, unsigned int *daku);
//全角→半角時,濁点、半濁点かどうかがdakuに帰る　半角→全角時は濁点、半濁点をどうかをdakuに入れる
unsigned int ZenHanKata(const unsigned int code, unsigned int *daku, const DIRECTION direction);
//記号全半変換
unsigned int ZenHanSymbol(const unsigned int code, const DIRECTION direction);
