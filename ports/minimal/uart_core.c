#include <unistd.h>
#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

extern unsigned int key;
// Receive single character

char teststr[] = "";
int index = 1;

int mp_hal_stdin_rx_chr(void) {
	
	//casiopy_print("C");
	char tempstr[2] = {0};
	//tempstr[0] = index;
	//casiopy_print("D");
    if (teststr[index-1]) {
		//casiopy_print("E");
		tempstr[0] = teststr[index-1];
		//casiopy_print("F");
		//casiopy_print(tempstr);
		return teststr[index++-1];
	} else {
		//casiopy_print("G");
		return 0;
	}
	return 0;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    casiopy_print(str, len);
}
