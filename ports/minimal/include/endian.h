/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : endian.h                                        */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ENDIAN_H__
#define __ENDIAN_H__


// Macros

#define UtlSwapWord(w)      (unsigned short)((((w) & 0x00ff) << 8) | (((w) & 0xff00) >> 8))
#define UtlSwapDword(l)     (unsigned long)((((l) & 0x000000ff) << 24) | (((l) & 0x0000ff00) << 8) | (((l) & 0xff000000) >> 24) | (((l) & 0x00ff0000) >> 8))
#define UtlSwapInteger(i)   UtlSwapDword(i)
#define UtlSwapPointer(p)   (void*)((((unsigned long)(p) & 0x000000ff) << 24) | (((unsigned long)(p) & 0x0000ff00) << 8) | (((unsigned long)(p) & 0xff000000) >> 24) | (((unsigned long)(p) & 0x00ff0000) >> 8))


#endif

#ifdef __cplusplus
}
#endif
