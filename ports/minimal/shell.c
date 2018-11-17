
#include "tinyprintf.h"
#include "MonochromeLib.h"
#include "specialchars.h"

unsigned int key;

int charLength = 3;
int charHeight = 7;
	

int shellTopLine;
int shellPosX;
int shellPosY;
int shellTextEnd;
int shellTextCursorPos;
int shellCursorX;
int shellCursorLine;
char displayEndOfShell;
#define SHELL_BUFFER_SIZE 200
char shellText[SHELL_BUFFER_SIZE] = {0};

extern const int _iFont3x7[];

void shell_init() {
	shellTopLine = -8; //nth line that is displayed at the top of the shell; as character wrap is activated, this is not just a matter of counting the \ns.
	shellPosX = 0; //position (relative to the screen, and in pixels) of the current printed character
	shellPosY = 0;
	shellTextEnd = 0; //to not have to recalculate strlen(shellText) each time
	shellTextCursorPos = 0; //position of the cursor, relative to the text
	shellCursorX = 0; //x position of the cursor, relative to the screen
	shellCursorLine = 0; //line of the cursor (y position), relative to the text
	char displayEndOfShell = 1;
	memset(shellText, 0, SHELL_BUFFER_SIZE);
}

void shell_print(char* str, unsigned int len) {

	for (int i = 0; i < len; i++) {
		
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
			
		/*} else if (str[i] == '\n') {
			shellPosX = 0;
			shellPosY += charHeight;*/
			
		} else if (str[i] == CHAR_LEFT) {
			
			shellTextCursorPos--;
			if (shellTextCursorPos < 0) {
				shellTextCursorPos = 31;
				shellCursorLine--;
				if (shellCursorLine < shellTopLine) {
					shellTopLine--;
				}
			}
			
		} else if (str[i] == CHAR_RIGHT) {
			
			shellTextCursorPos++;
			if (shellTextCursorPos >= 32) {
				shellTextCursorPos = 0;
				shellCursorLine++;
				
			}
			
		} else {
			
			if (shellTextEnd == SHELL_BUFFER_SIZE) {
				/*locate(1,1);
				Print("moving memory");
				GetKey(&key);*/
				//get size of first line
				int firstLineBreak = 0;
				for (firstLineBreak = 0; firstLineBreak < 32; firstLineBreak++) {
					if (firstLineBreak > 0 && shellText[firstLineBreak-1] == '\n') {
						break;
					}
				}
				memmove(shellText, shellText+firstLineBreak, SHELL_BUFFER_SIZE-firstLineBreak);
				memset(shellText+SHELL_BUFFER_SIZE-firstLineBreak, 0, firstLineBreak);
				shellTextEnd -= firstLineBreak;
				shellTextCursorPos -= firstLineBreak;
				shellCursorLine--;
				shellTopLine--;
			}
			
			shellText[shellTextEnd] = str[i];
			shellTextCursorPos++;
			shellCursorX++;
			shellTextEnd++;
			
			if (str[i] == '\n' || shellCursorX >= 32) {
				shellCursorX = 0;
				shellCursorLine++;
				shellTopLine++;
			}
			
		}
		
		
	}
	
	//we basically (efficiently) reprint all the text each time a string is printed
	//not very efficient, but dealing with deletes, scrolling up, etc is not easy
	
	shellPosX = 0;
	shellPosY = 0;
	

	
	int shellTopLineTemp = shellTopLine;
	if (shellTopLineTemp < 0) {
		shellTopLineTemp = 0;
	}
	
	int lineCount = 0;
	
	ML_clear_vram();
	for (int i = 0; shellText[i]; i++) {
				
		//"ghost write" until we reach shell top line
		if (lineCount >= shellTopLineTemp) {
			
			unsigned long j = 1 << ((charHeight*charLength)%32)-1; //initializes a long for bit checking. The long is equal to 0b10000.. with number of zeroes being the maximum length of the character, minus 1 because there's already a 1.
			
			for (int k = charHeight*charLength-1; k >= 0; k--) { //browses through the pixels of the character specified, shifting the 1 of j to the right each time, so that it makes 0b01000.., 0b001000... etc
				
				if (_iFont3x7[shellText[i]] & j) { //checks if the bit that is a 1 in the j is also a 1 in the character
					ML_pixel(shellPosX+k%(charLength), shellPosY+k/charLength, 1); //if so, locates the pixel at the coordinates, using modulo and division to calculate the coordinates relative to the top left of the character
				}
				
				if (j != 1)
					j >>= 1;
				else
					j = 2147483648;
				
			}
		
		}
		
		shellPosX += charLength+1;
		
		if (shellPosX > 125 || shellText[i] == '\n') {
			shellPosX = 0;
			if (lineCount >= shellTopLineTemp) {
				shellPosY += charHeight;
			}
			lineCount++;
			
		}
	}
	char strtest[10] = {0};
	sprintf(strtest, "%d", shellTextEnd);
	locate(19,1);
	Print(strtest);
	ML_line(shellCursorX*(charLength+1), (shellCursorLine-shellTopLineTemp)*(charHeight), shellCursorX*(charLength+1), (shellCursorLine-shellTopLineTemp)*(charHeight)+charHeight, ML_BLACK);
	ML_display_vram();
	
}