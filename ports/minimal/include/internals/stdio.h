#ifndef	_INTERNALS_STDIO_H
#define	_INTERNALS_STDIO_H

#include <stddef.h>
#include <stdarg.h>

//---
//	Formatted printing.
//---

#ifndef		__stdio_buffer_size
#define		__stdio_buffer_size 256
#endif

extern char	__stdio_buffer[];

/*
	__printf()
	Formatted printing to the stdio buffer.
*/
int __printf(size_t size, const char *format, va_list args);

#endif	// _INTERNALS_STDIO_H
