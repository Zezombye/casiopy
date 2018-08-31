
#include <fxlib.h>
#include "tinyprintf.h"
#include "MonochromeLib.h"




unsigned int key;
int shellPosX = 0;
int shellPosY = 0;



int main(int isappli, unsigned short optnum)
{
		
	/*char str[50] = {0};
	tfp_sprintf(str, "abc");
	locate(1,7); Print(str);
	GetKey(&key);
	edit_main();*/
	//getkey();
	//mpy_main();
	
	//ML_pixel(1,1,1);
	/*GetKey(&key);
	char str[30] = {0};
	tfp_sprintf(str, "%p", ML_vram_adress());
	locate(1,1); Print(str);
	
	GetKey(&key);*/
	
	edit_main();
	//mpy_main();
	
	/*char str[20];
	tfp_sprintf(str, "test");
	
	Bdisp_AllClr_DDVRAM();
	locate(1,1);
	Print(str);
	GetKey(&key);
	volatile int test = 7;
	locate(1,pow(test, 1.0));
	Print("test");*/
	
	unsigned int key;
	while(1) GetKey(&key);

	return 1;
}



// Font 3x7 data
/*static const int font[128]={
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
238744, //Character 049 [1]
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
};*/

extern const int _iFont3x7[];

void casiopy_print(char* str, unsigned int len) {
	char tempstr[2] = {0};
	
	int charLength = 3;
	int charHeight = 7;
	
	for (int i = 0; i < len; i++) {
		tempstr[0] = str[i];
		if (shellPosX > 125) {
			shellPosX = 0;
			shellPosY += charHeight;
		}
		if (shellPosY > 62) {
			//Shift VRAM up 7 pixels
			char* vram_start = ML_vram_adress();
			memmove(vram_start, vram_start+7*128/8, (64-7)*128/8);
			memset(vram_start+(64-7)*128/8, 0, 7*128/8);
			shellPosY = 56;
		}
		if (str[i] == '\r' || str[i] == 0x08) {
			continue;
		} else if (str[i] == '\n') {
			shellPosX = 0;
			shellPosY += charHeight;
		} else {
			//locate(shellPosX, shellPosY);
			//Print(tempstr);
			
			unsigned long j = 1 << ((charHeight*charLength)%32)-1; //initializes a long for bit checking. The long is equal to 0b10000.. with number of zeroes being the maximum length of the character, minus 1 because there's already a 1.
			
			for (int k = charHeight*charLength-1; k >= 0; k--) { //browses through the pixels of the character specified, shifting the 1 of j to the right each time, so that it makes 0b01000.., 0b001000... etc
				
				if (_iFont3x7[str[i]] & j) { //checks if the bit that is a 1 in the j is also a 1 in the character
				
					ML_pixel(shellPosX+k%(charLength), shellPosY+k/charLength, 1); //if so, locates the pixel at the coordinates, using modulo and division to calculate the coordinates relative to the top left of the character
				}
				
				if (j != 1)
					j >>= 1;
				else
					j = 2147483648;
				
			}
			shellPosX += charLength+1;
		}
		
		//Sleep(50);
		ML_display_vram();
	}
}

