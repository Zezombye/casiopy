#ifndef __MYMALLOC_H_
#define __MYMALLOC_H_

#include <stddef.h>

#define malloc(x) mymalloc(x)
#define free(x) myfree(x)

extern void* mymalloc(size_t size);
extern void myfree(void* ptr);

#endif