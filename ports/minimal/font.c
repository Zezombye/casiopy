//Font functions -----------------------------------------------------------------------

//Include files
#include "fxlib.h"
#include "stdio.h"
#include "font.h"
#include "tinyprintf.h"
#include "MonochromeLib.h"

// ------------------------------------------------------------------------------------- 
// Global variables

// Font 3x5 data
static const unsigned int _iFont3x5[128]={
 3960, //Character 000 [NUL]
 3960, //Character 001 [SOH]
 3960, //Character 002 [STX]
 3960, //Character 003 [ETX]
 3960, //Character 004 [EOT]
 3960, //Character 005 [ENQ]
 3960, //Character 006 [ACK]
 3960, //Character 007 [BEL]
 3960, //Character 008 [BS]
 3960, //Character 009 [TAB]
 3960, //Character 010 [LF]
 3960, //Character 011 [VT]
32000, //Character 012 [FF]
 3960, //Character 013 [CR]
 3960, //Character 014 [SO]
 3960, //Character 015 [SI]
 3960, //Character 016 [DEL]
 3960, //Character 017 [XON]
 3960, //Character 018 [DC2]
 3960, //Character 019 [XOFF]
 3960, //Character 020 [DC4]
 3960, //Character 021 [NAK]
 3960, //Character 022 [SYN]
 3960, //Character 023 [ETB]
 3960, //Character 024 [CAN]
 3960, //Character 025 [EM]
 3960, //Character 026 [SUB]
 3960, //Character 027 [ESC]
 3960, //Character 028 [FS]
 3960, //Character 029 [GS]
 3960, //Character 030 [RS]
 3960, //Character 031 [US]
    0, //Character 032 [SP]
 8338, //Character 033 [!]
   45, //Character 034 ["]
16254, //Character 035 [#]
32223, //Character 036 [$]
21157, //Character 037 [%]
10922, //Character 038 [&]
  166, //Character 039 [']
17556, //Character 040 [(]
 5265, //Character 041 [)]
 2728, //Character 042 [*]
 1488, //Character 043 [+]
10624, //Character 044 [,]
  448, //Character 045 [-]
13824, //Character 046 [.]
 4756, //Character 047 [/]
31599, //Character 048 [0]
29850, //Character 049 [1]
29671, //Character 050 [2]
31207, //Character 051 [3]
18925, //Character 052 [4]
31183, //Character 053 [5]
31695, //Character 054 [6]
18727, //Character 055 [7]
31727, //Character 056 [8]
31215, //Character 057 [9]
13851, //Character 058 [:]
 5147, //Character 059 [;]
17492, //Character 060 [<]
 3640, //Character 061 [=]
 5393, //Character 062 [>]
 8355, //Character 063 [?]
11171, //Character 064 [@]
23530, //Character 065 [A]
15083, //Character 066 [B]
25166, //Character 067 [C]
15211, //Character 068 [D]
29647, //Character 069 [E]
 5071, //Character 070 [F]
27470, //Character 071 [G]
23533, //Character 072 [H]
29847, //Character 073 [I]
11044, //Character 074 [J]
23277, //Character 075 [K]
29257, //Character 076 [L]
23421, //Character 077 [M]
23403, //Character 078 [N]
11114, //Character 079 [O]
 4843, //Character 080 [P]
17770, //Character 081 [Q]
23275, //Character 082 [R]
14478, //Character 083 [S]
 9367, //Character 084 [T]
31597, //Character 085 [U]
11117, //Character 086 [V]
12141, //Character 087 [W]
23213, //Character 088 [X]
 9389, //Character 089 [Y]
29351, //Character 090 [Z]
25750, //Character 091 [[]
17545, //Character 092 [\]
26918, //Character 093 []]
   42, //Character 094 [^]
28672, //Character 095 [_]
  139, //Character 096 [`]
27554, //Character 097 [a]
15225, //Character 098 [b]
25200, //Character 099 [c]
27516, //Character 100 [d]
29674, //Character 101 [e]
 9684, //Character 102 [f]
14766, //Character 103 [g]
23385, //Character 104 [h]
 9346, //Character 105 [i]
11012, //Character 106 [j]
22345, //Character 107 [k]
29843, //Character 108 [l]
23408, //Character 109 [m]
23376, //Character 110 [n]
11088, //Character 111 [o]
 5976, //Character 112 [p]
19824, //Character 113 [q]
 4840, //Character 114 [r]
14448, //Character 115 [s]
17586, //Character 116 [t]
27496, //Character 117 [u]
11112, //Character 118 [v]
32616, //Character 119 [w]
23208, //Character 120 [x]
 5480, //Character 121 [y]
29496, //Character 122 [z]
25814, //Character 123 [{]
 9362, //Character 124 [|]
13715, //Character 125 [}]
  408, //Character 126 [~]
 3960  //Character 127 []
};

// Font 3x7 data
const int _iFont3x7[128]={
 2022255, //Character 000 [NUL]
 2022255, //Character 001 [SOH]
 2022255, //Character 002 [STX]
 2022255, //Character 003 [ETX]
 2022255, //Character 004 [EOT]
 2022255, //Character 005 [ENQ]
 2022255, //Character 006 [ACK]
 2022255, //Character 007 [BEL]
 2022255, //Character 008 [BS]
 2022255, //Character 009 [TAB]
 2022255, //Character 010 [LF]
 2022255, //Character 011 [VT]
0, //Character 012 [FF]
 2022255, //Character 013 [CR]
 2022255, //Character 014 [SO]
 2022255, //Character 015 [SI]
 2022255, //Character 016 [DEL]
 2022255, //Character 017 [XON]
 2022255, //Character 018 [DC2]
 2022255, //Character 019 [XOFF]
 2022255, //Character 020 [DC4]
 2022255, //Character 021 [NAK]
 2022255, //Character 022 [SYN]
 2022255, //Character 023 [ETB]
 2022255, //Character 024 [CAN]
 2022255, //Character 025 [EM]
 2022255, //Character 026 [SUB]
 2022255, //Character 027 [ESC]
 2022255, //Character 028 [FS]
 2022255, //Character 029 [GS]
 2022255, //Character 030 [RS]
 2022255, //Character 031 [US]
0,      //Character 032 [SP]
66704, //Character 033 [!]
360,   //Character 034 ["]
95696, //Character 035 [#]
773754, //Character 036 [$]
169256, //Character 037 [%]
218224, //Character 038 [&]
1328, //Character 039 [']
140448, //Character 040 [(]
42120, //Character 041 [)]
21824, //Character 042 [*]
11904, //Character 043 [+]
679936, //Character 044 [,]
3584, //Character 045 [-]
110592, //Character 046 [.]
38176, //Character 047 [/]
252792, //Character 048 [0]
238800, //Character 049 [1]
237368, //Character 050 [2]
249144, //Character 051 [3]
151400, //Character 052 [4]
249464, //Character 053 [5]
253560, //Character 054 [6]
75064,  //Character 055 [7] 
253816, //Character 056 [8]
249720, //Character 057 [9]
110808, //Character 058 [:]
340184,//Character 059 [;]
139936, //Character 060 [<]
29120,  //Character 061 [=]
43144,  //Character 062 [>]
66840,  //Character 063 [?]
220440,  //Character 064 [@]
188240,   //Character 065 [A]
120664,   //Character 066 [B]
201328,   //Character 067 [C]
121688,   //Character 068 [D]
237176,   //Character 069 [E]
40568,  //Character 070 [F]
219760,   //Character 071 [G]
188264,   //Character 072 [H]
238776,   //Character 073 [I]
88352,   //Character 074 [J]
186216,   //Character 075 [K]
234056,   //Character 076 [L]
187368,   //Character 077 [M]
187224,   //Character 078 [N]
88912,   //Character 079 [O]
38744,  //Character 080 [P]
1137488,   //Character 081 [Q]
186200,   //Character 082 [R]
115824,   //Character 083 [S]
74936,   //Character 084 [T]
252776,   //Character 085 [U]
88936,   //Character 086 [V]
195432,   //Character 087 [W]
185704,   //Character 088 [X]
75112,   //Character 089 [Y]
234808,   //Character 090 [Z]
206000, //Character 091 [[]
148552, //Character 092 [\]
107672, //Character 093 []]
336,    //Character 094 [^]
-262144, //Character 095 [_]
1112,   //Character 096 [`]
220032, //Character 097 [a]
121544, //Character 098 [b]
201600, //Character 099 [c]
220064, //Character 100 [d]
211840, //Character 101 [e]
38512,  //Character 102 [f]
949120, //Character 103 [g]
185928, //Character 104 [h]
239120, //Character 105 [i]
337424, //Character 106 [j]
186184, //Character 107 [k]
140440,  //Character 108 [l]
188224,  //Character 109 [m]
187072, //Character 110 [n]
88704,  //Character 111 [o]
383680, //Character 112 [p]
-828544,//Character 113 [q]
38720,  //Character 114 [r]
107200, //Character 115 [s]
70344, //Character 116 [t]
252736, //Character 117 [u]
88896,  //Character 118 [v]
195392,  //Character 119 [w]
185664, //Character 120 [x]
944960, //Character 121 [y]
234944, //Character 122 [z]
205488, //Character 123 [{]
74896,  //Character 124 [|]
108696, //Character 125 [}]
20032,  //Character 126 [~]
0, //Character 127 []

};
//Current context
int _iCntx=0;

//Font definition
struct FData _sFData[FONTMAX]={
{4,6,128/4,64/6,_iFont3x5},  //3x5 Font
{4,8,128/4,64/8,_iFont3x7},  //3x7 Font
//{5,7,128/5,64/7,_iFont4x6},  //4x6 Font
{6,8,128/6,64/8,NULL     }}; //7x8 Font (Standard large font)

//Font contexts (default context defined)
struct FCntx _sFCntx[CONTMAX]={{FONTL,COLNOR,0,0}};

// ------------------------------------------------------------------------------------- 
// Set font context
void DefineFontContext(int iCntx, int iFont, int iColor, int iPx0, int iPy0)
{
  _sFCntx[iCntx].iFont  = iFont;
  _sFCntx[iCntx].iColor = iColor;
  _sFCntx[iCntx].iPx0   = iPx0;
  _sFCntx[iCntx].iPy0   = iPy0;
}

// ------------------------------------------------------------------------------------- 
// Set font context
void SetFontContext(int iCntx)
{
  _iCntx=iCntx;
}

// ------------------------------------------------------------------------------------- 
// Set font (changes to default font context)
void SetFont(int iFont)
{
  _iCntx=0;
  _sFCntx[_iCntx].iFont=iFont;
}

// ------------------------------------------------------------------------------------- 
// Set color (changes to default context)
void SetColor(int iColor)
{
  _iCntx=0;
  _sFCntx[_iCntx].iColor=iColor;
}

// ------------------------------------------------------------------------------------- 
// Set offset(changes to default context)
void SetOffset(int iPx0, int iPy0)
{
  _iCntx=0;
  _sFCntx[_iCntx].iPx0=iPx0;
  _sFCntx[_iCntx].iPy0=iPy0;
}

// ------------------------------------------------------------------------------------- 
// Set color in current context
void SetColorCntx(int iColor)
{
  _sFCntx[_iCntx].iColor=iColor;
}

// ------------------------------------------------------------------------------------- 
// Get screen sizes in chars
int GetScrCAx(void){ return(_sFData[_sFCntx[_iCntx].iFont].iSx); }
int GetScrCAy(void){ return(_sFData[_sFCntx[_iCntx].iFont].iSy); }

// ------------------------------------------------------------------------------------- 
// Print char function
void PrintCharXY(int iPx0,int iPy0, char cChr)
{
	unsigned int key;
  //Variables
  int i,j;
  int iPx,iPy;
  int iAy,iAx;
  int iColF,iColB;
  unsigned int iCount;
  unsigned int iBitmap;
  char sStr[2];
  unsigned char cChr0;
  
  //Init variables
  cChr0=cChr;
  cChr0=(cChr0<=126?cChr0:127);
  iPx=iPx0+_sFCntx[_iCntx].iPx0;
  iPy=iPy0+_sFCntx[_iCntx].iPy0;
  
  //Use standard 6x8 Font
  if(_sFData[_sFCntx[_iCntx].iFont].iChData==NULL)
  {
    sStr[0]=cChr0;
    sStr[1]=0;
    if(cChr0==127) sStr[0]=0xD8;
    PrintXY(iPx,iPy,sStr,(_sFCntx[_iCntx].iColor==COLNOR?0:1));    
  }

  //Print with custom fonts
  else
  {
    //Print loop
    iCount = 1;
    iAx=_sFData[_sFCntx[_iCntx].iFont].iAx;
    iAy=_sFData[_sFCntx[_iCntx].iFont].iAy;
    iColF=(_sFCntx[_iCntx].iColor==COLNOR?1:0);
    iColB=(_sFCntx[_iCntx].iColor==COLNOR?0:1);
    iBitmap=_sFData[_sFCntx[_iCntx].iFont].iChData[cChr0];
    for(j=0;j<=iAy-1;j++){
		for(i=0;i<=iAx-1;i++){
		  if(iPx+i>=0 && iPx+i<=127 && iPy+j>=0 && iPy+j<=63)
		  {
			if(i<iAx-1 && j<iAy-1)
			{
			  if(iBitmap&iCount) 
				ML_pixel(iPx+i,iPy+j,iColF);
			  else
				ML_pixel(iPx+i,iPy+j,iColB);
			  iCount=iCount*2;
			}
			else
			  ML_pixel(iPx+i,iPy+j,iColB);
		  }
		}
	}
  
  }

}

// ------------------------------------------------------------------------------------- 
// Print string function (location by pixels)
void PrintStrXY(int iPx, int iPy,char *sStr)
{
	unsigned int key;
  //Variables
  int i;
  int iPx0=0,iPy0=0;
  int iIgnChar=0;
  char cChr;

  //Char loop
  for(i=0;sStr[i]!=0;i++)
  {
    PrintCharXY(iPx+_sFData[_sFCntx[_iCntx].iFont].iAx*(i-iIgnChar),iPy,sStr[i]);
  }
}

// ------------------------------------------------------------------------------------- 
// Print char function (location by chars)
void PrintChar(int iCx, int iCy,char cChr)
{
  PrintCharXY(iCx*_sFData[_sFCntx[_iCntx].iFont].iAx,
             iCy*_sFData[_sFCntx[_iCntx].iFont].iAy,
             cChr);
}

// ------------------------------------------------------------------------------------- 
// Print string function (location by chars)
void PrintStr(int iCx, int iCy,char *sStr)
{
  PrintStrXY(iCx*_sFData[_sFCntx[_iCntx].iFont].iAx,
             iCy*_sFData[_sFCntx[_iCntx].iFont].iAy,
             sStr);
}

// ----------------------------------------------------------------
// SetCursor
void SetCursor(int iCx, int iCy, int iColor, int iClip)
{
  //Variables
  int iPx;
  int iPy;
  int iAy;
  
  //Calculate cursor position
  iPx=iCx*_sFData[_sFCntx[_iCntx].iFont].iAx;
  iPy=_sFCntx[_iCntx].iPy0+iCy*_sFData[_sFCntx[_iCntx].iFont].iAy;
  
  //Draw cursor (normal)
  //if(iClip==0)
  //{
    iAy=_sFData[_sFCntx[_iCntx].iFont].iAy-1;
    if(iAy>=0) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+0,iColor);
    if(iAy>=1) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+1,iColor);
    if(iAy>=2) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+2,iColor);
    if(iAy>=3) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+3,iColor);
    if(iAy>=4) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+4,iColor);
    if(iAy>=5) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+5,iColor);
    if(iAy>=6) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+6,iColor);
    //if(iAy>=7) Bdisp_SetPoint_DDVRAM(iPx+0,iPy+7,iColor);
  //}
  
  //Draw cursor (Clip mode)
  /*else
  {
    Bdisp_SetPoint_DDVRAM(iPx+0,iPy+0,iColor);
    Bdisp_SetPoint_DDVRAM(iPx+0,iPy+1,iColor);
    if(iPx-1>=0  ) Bdisp_SetPoint_DDVRAM(iPx-1,iPy+0,iColor);
    if(iPx+1<=127) Bdisp_SetPoint_DDVRAM(iPx+1,iPy+0,iColor);
    if(iPx-2>=0  ) Bdisp_SetPoint_DDVRAM(iPx-2,iPy+0,iColor);
    if(iPx+2<=127) Bdisp_SetPoint_DDVRAM(iPx+2,iPy+0,iColor);
    iPy=iPy+_sFData[_sFCntx[_iCntx].iFont].iAy-8;
    Bdisp_SetPoint_DDVRAM(iPx+0,iPy+6,iColor);
    Bdisp_SetPoint_DDVRAM(iPx+0,iPy+7,iColor);
    if(iPx-1>=0  ) Bdisp_SetPoint_DDVRAM(iPx-1,iPy+7,iColor);
    if(iPx+1<=127) Bdisp_SetPoint_DDVRAM(iPx+1,iPy+7,iColor);
    if(iPx-2>=0  ) Bdisp_SetPoint_DDVRAM(iPx-2,iPy+7,iColor);
    if(iPx+2<=127) Bdisp_SetPoint_DDVRAM(iPx+2,iPy+7,iColor);
  }*/

}