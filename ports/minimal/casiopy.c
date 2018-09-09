
#include <fxlib.h>
#include "tinyprintf.h"
#include "MonochromeLib.h"

unsigned int key;


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
