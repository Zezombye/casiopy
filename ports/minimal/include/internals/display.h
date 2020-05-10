#ifndef	_INTERNALS_DISPLAY_H
#define	_INTERNALS_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

extern uint32_t *vram;

//---
//	Rectangle masks.
//
//	The concept of 'rectangle masks' is used several times in this module.
//	It relies on the fact that operations affecting a rectangle act the
//	same for all lines, and line operation is very optimized. A rectangle
//	mask is a set of integers, where each bit indicate whether a specific
//	pixel is affected (1) by the operation, or not (0).
//
//	For example to clear a rectangle such as (14, 16, 112, 48), the masks
//	will need to hold 0003ffff ffffffff ffffffff ffff0000. Bitwise-
//	combining them with video ram long entries yields very good performance
//	as compared to operation on single pixels. Each bitwise operation will
//	produce different results, which is very flexible.
//
//	This technique can also be used in subtle cases with patterns more
//	complicated than rectangles, but within this module this is unlikely to
//	happen.
//---

/*
	adjustRectangle()
	Adjusts the given rectangle coordinates to ensure that :
	- the rectangle is entirely contained in the screen;
	- x1 < x2;
	- y1 < y2,
	which is needed when working with screen rectangles. Returns non-zero
	if the rectangle is outside the screen, which usually means there is
	nothing to do.
*/
int adjustRectangle(int *x1, int *y1, int *x2, int *y2);

/*
	getMasks()
	Computes the rectangle masks needed to affect pixels located between x1
	and x2 (both included). The four masks are stored in the third argument
	(seen as an array).
*/
void getMasks(size_t x1, size_t x2, uint32_t *masks);

#endif	// _INTERNALS_DISPLAY_H
