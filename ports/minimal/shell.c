
#include "tinyprintf.h"
#include "MonochromeLib.h"
#include "specialchars.h"
#include <keybios.h>
#include <fxlib.h>

unsigned int key;

int charLength = 3;
int charHeight = 7;

char redrawShell = 0;

int shellTopLine;
int shellPosX;
int shellPosY;
int shellTextEnd;
int shellTextCursorPos;
int shellCursorX;
int shellCursorLine;
int shellTopLineOffset;
//char displayEndOfShell;
#define SHELL_BUFFER_SIZE 2048
#define SHELL_MAX_LINES 9
char shellText[SHELL_BUFFER_SIZE] = {0};

extern const int _iFont3x7[];

void shell_pgup() {	
	/*locate(1,1);
			Print("pgup");
			GetKey(&key);*/
	shellTopLineOffset -= 3;
	if (shellTopLineOffset < -shellTopLine) {
		shellTopLineOffset = -shellTopLine;
	}
	shell_draw(0);
}

void shell_pgdown() {
	shellTopLineOffset += 3;
	if (shellTopLineOffset > 0) {
		shellTopLineOffset = 0;
	}
	shell_draw(0);
}

void shell_init() {
	shellTopLine = -SHELL_MAX_LINES+1; //nth line that is displayed at the top of the shell; as character wrap is activated, this is not just a matter of counting the \ns.
	shellPosX = 0; //position (relative to the screen, and in pixels) of the current printed character
	shellPosY = 0;
	shellTextEnd = 0; //to not have to recalculate strlen(shellText) each time
	shellTextCursorPos = 0; //position of the cursor, relative to the text
	shellCursorX = 0; //x position of the cursor, relative to the screen
	shellCursorLine = 0; //line of the cursor (y position), relative to the text
	shellTopLineOffset = 0; //offset used with pgup/pgdown, is reset to 0 when a character is printed or cursor is moved
	//displayEndOfShell = 1;
	memset(shellText, 0, SHELL_BUFFER_SIZE);
}

void shell_move_cursor_left(unsigned int pos) {
	if (pos == 0) return;
	/*locate(1,1);
			Print("left");
			GetKey(&key);*/
	for (int i = 0; i < pos; i++) {
		shellTextCursorPos--;
		shellCursorX--;
		//shellTextEnd--;
		if (shellCursorX < 0) {
			shellCursorX = 31;
			shellCursorLine--;
			if (shellCursorLine < shellTopLine) {
				shellTopLine--;
			}
		}
	}
	shell_draw(1);
}

void shell_move_cursor_right(char currentChar) {
	shellTextCursorPos++;
	shellCursorX++;
	//shellTextEnd++;
	if (shellTextEnd < shellTextCursorPos) {
		shellTextEnd++;
	}
	
	if (currentChar == '\n' || shellCursorX >= 32) {
		shellCursorX = 0;
		shellCursorLine++;
		if (shellCursorLine-shellTopLine > SHELL_MAX_LINES-1) {
			shellTopLine++;
		}
		redrawShell = 1;
	}
}

void shell_erase_after_cursor() {
	//As shell_draw only displays until shellTextEnd, just set it to the cursor pos
	shellTextEnd = shellTextCursorPos;
	shell_draw(1);
}

void shell_print(char* str, unsigned int len) {

	redrawShell = 0;
	//len=strlen(str);

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
			
			
			
		} else if (str[i] == CHAR_RIGHT) {
			
			shellTextCursorPos++;
			shellCursorX++;
			if (shellCursorX >= 32) {
				shellCursorX = 0;
				shellCursorLine++;
				
			}
			
		} else if (str[i] == '\0') {
			redrawShell = 1;
			
		} else {
			
			//Memory shift
			if (shellTextEnd == SHELL_BUFFER_SIZE) {
				/*locate(1,1);
				Print("moving memory");
				GetKey(&key);*/
				//get size of first line
				int memCount = 0;
				int nbLinesMoved = 0;
				while (memCount < 200) {
					int firstLineBreak = 0;
					for (firstLineBreak = 0; firstLineBreak < 32; firstLineBreak++) {
						if (firstLineBreak > 0 && shellText[firstLineBreak+memCount-1] == '\n') {
							break;
						}
					}
					memCount += firstLineBreak;
					nbLinesMoved++;
				}
				memmove(shellText, shellText+memCount, SHELL_BUFFER_SIZE-memCount);
				memset(shellText+SHELL_BUFFER_SIZE-memCount, 0, memCount);
				shellTextEnd -= memCount;
				shellTextCursorPos -= memCount;
				shellCursorLine -= nbLinesMoved;
				shellTopLine -= nbLinesMoved;
			}
			
			//special case for \n (if the cursor is at the middle of the line and user presses [exe])
			if (str[i] == '\n') {
				shellTextCursorPos = shellTextEnd;
				shellCursorLine = shellTopLine+SHELL_MAX_LINES-1;
			}
			
			shellText[shellTextCursorPos] = str[i];
			shell_move_cursor_right(str[i]);
			/*shellTextCursorPos++;
			shellCursorX++;
			shellTextEnd++;
			
			if (str[i] == '\n' || shellCursorX >= 32) {
				shellCursorX = 0;
				shellCursorLine++;
				shellTopLine++;
			}*/
			
		}
		
		
	}
	
	//we basically (efficiently) reprint all the text each time a string is printed
	//not very efficient, but dealing with deletes, scrolling up, etc is not easy
	if (redrawShell) {
		shell_draw(1);
	}

	
}

void shell_draw(char resetTopLineOffset) {
		
	
	shellPosX = 0;
	shellPosY = 0;
	
	if (resetTopLineOffset) {
		shellTopLineOffset = 0;
	}

	
	int shellTopLineTemp = shellTopLine+shellTopLineOffset;
	if (shellTopLineTemp < 0) {
		shellTopLineTemp = 0;
	}
	
	int lineCount = 0;
	
	ML_clear_vram();
	for (int i = 0; i < shellTextEnd; i++) {
	//for (int i = 0; shellText[i]; i++) {
				
		//"ghost write" until we reach shell top line
		if (lineCount >= shellTopLineTemp) {
			
			unsigned long j = 1 << ((charHeight*charLength)%32)-1; //initializes a long for bit checking. The long is equal to 0b10000.. with number of zeroes being the maximum length of the character, minus 1 because there's already a 1.
			
			for (int k = charHeight*charLength-1; k >= 0; k--) { //browses through the pixels of the character specified, shifting the 1 of j to the right each time, so that it makes 0b01000.., 0b001000... etc
				
				if (_iFont3x7[shellText[i]] & j) { //checks if the bit that is a 1 in the j is also a 1 in the character
					ML_pixel(1+shellPosX+k%(charLength), shellPosY+k/charLength, 1); //if so, locates the pixel at the coordinates, using modulo and division to calculate the coordinates relative to the top left of the character
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
	/*sprintf(strtest, "%d", shellTextEnd);
	locate(18,1);
	Print(strtest);
	sprintf(strtest, "%d", shellTopLine);
	locate(19,2);
	Print(strtest);
	sprintf(strtest, "%d", shellTopLineOffset);
	locate(19,3);
	Print(strtest);*/
	ML_line(shellCursorX*(charLength+1), (shellCursorLine-shellTopLineTemp)*(charHeight), shellCursorX*(charLength+1), (shellCursorLine-shellTopLineTemp)*(charHeight)+charHeight, ML_BLACK);
	Bdisp_PutDisp_DD();
	/*if (IsKeyDown(KEY_CTRL_MENU)) {
		GetKey(&key);
	}*/
	//ML_display_vram();
}