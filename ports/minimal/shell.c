
#include "tinyprintf.h"
#include "MonochromeLib.h"

unsigned int key;
int shellPosX = 0;
int shellPosY = 0;
int shellTextEnd = 0;
int shellTextCursorPos = 0;
//char shellText[200] = {0};

extern const int _iFont3x7[];

void shell_go_up() {
	
}

void shell_print(char* str, unsigned int len) {
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
		if (str[i] == '\r') {
			continue;
			
		} else if (str[i] == '\b' || str[i] == 0x1b) {
			//remove character
			/*if (shellTextCursorPos <= 0) continue;
			
			shellTextCursorPos--;
			for (int j = 0; j < shellTextEnd; j++) {
				shellText[j] = shellText[j+1];
			}
			shellTextEnd--;*/
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
		
		//shellText[shellTextEnd] = str[i];
		//shellTextEnd++;
		
		//Sleep(50);
		ML_display_vram();
	}
}

