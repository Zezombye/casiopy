//---
//
//	gint core module: syscalls
//
//	Some of the functionality still requires interacting with the system.
//
//---

#ifndef	_INTERNALS_SYSCALLS_H
#define	_INTERNALS_SYSCALLS_H

#include <stddef.h>

/* malloc() -- allocate data in heap */
void *__malloc(size_t size);

/* free() -- free data allocated by malloc(), calloc() or realloc() */
void __free(void *ptr);

/* realloc() -- reallocate a chunk of memory */
void *__realloc(void *chunk, size_t new_size);

/* get_os_version() -- write the OS version in format MM.mm.pppp to a string */
void __get_os_version(char *str);

/* system_menu() -- go back to menu, assuming the system has the control */
void __system_menu(const void *vram);

#endif	// _INTERNALS_SYSCALLS_H
