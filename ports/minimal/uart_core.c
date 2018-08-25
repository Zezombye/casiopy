#include <unistd.h>
#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

extern unsigned int key;
extern char *_sText;
// Receive single character

int rx_index = 2;

//Note: this function is, normally, not called anymore. See the readline() loop in lib/mp_readline/readline.c.
int mp_hal_stdin_rx_chr(void) {
	
	//casiopy_print("C");
	char tempstr[2] = {0};
    if (_sText[rx_index-1]) {
		//casiopy_print("E");
		tempstr[0] = _sText[rx_index-1];
		//casiopy_print("F");
		//casiopy_print(tempstr);
		return _sText[rx_index++-1];
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
