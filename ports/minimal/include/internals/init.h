//---
//	gint core module: init
//	Program initialization and display manipulation for the startup logs.
//---

#ifndef	_INTERNALS_INIT_H
#define	_INTERNALS_INIT_H

#include <display.h>

/* init_version() -- get a version string */
const char *init_version(void);

/* init_stage() -- change the current init stage */
void init_stage(const char *name);

/* init_halt() -- halt the program */
void init_halt(void);

/* print() -- print text on a 21*8 grid */
#define print(x, y, str) dtext((x) * 6 - 5, (y) * 8 - 8, (str))

/* print_dec() -- print a number in base 10 */
void print_dec(int x, int y, int n, int digits);

/* print_hex() -- print a number in base 16 */
void print_hex(int x, int y, uint32_t n, int digits);

#endif	// _INTERNALS_INIT_H
