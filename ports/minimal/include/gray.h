//---
//
//	gint core/drawing module: gray
//
//	Runs the gray engine and handles drawing for the dual-buffer system.
//
//---

#ifndef	_GRAY_H
#define	_GRAY_H

#include <stdint.h>
#include <display.h>

// This module provides bitmap rendering.
#include <bopti.h>

//---
//	Engine control.
//---

/*
	gray_runs()
	Returns 1 if the gray engine is running, 0 otherwise.
*/
int gray_runs(void);

/*
	gray_start()
	Starts the gray engine. The control of the screen is transferred to the
	gray engine.
*/
void gray_start(void);

/*
	gray_stop()
	Stops the gray engine. The monochrome display system takes control of
	the video ram.
*/
void gray_stop(void);

/*
	gray_lightVRAM()
	Returns the module's light gray vram address.
*/
uint32_t *gray_lightVRAM(void);

/*
	gray_darkVRAM()
	Returns the module's dark gray vram address.
*/
uint32_t *gray_darkVRAM(void);

/*
	gray_currentVRAM()
	Returns the currently displayed video ram (if the engine runs). Used
	internally, but has no interest for the user. You don't want to draw to
	this vram.
*/
uint32_t *gray_currentVRAM(void);

/*
	gray_getDelays()
	Returns the gray engine delays. Pointers are not set if NULL.
*/
void gray_getDelays(int *light, int *dark);

/*
	gray_setDelays()
	Changes the gray engine delays. Usually you don't need to call this,
	because the engine has its default values.
	Finding values that give proper grays is quite the hard part of the
	gray engine. Usual values are about 1000, with light being between 75
	and 90% of dark.

	Typical values:

	values		stability	stripes		colors
	---------------------------------------------------------
	 860, 1298	excellent	worst static	good
	 912, 1343	bad		none		very good  (default)
	 993, 1609	medium		light fast	good
	1325, 1607	bad		light fast	excellent
	---------------------------------------------------------
*/
void gray_setDelays(int light, int dark);



//---
//	Global drawing functions.
//---

/*
	gupdate()
	Swaps the vram buffer sets. You need to call this function each time
	you finish drawing something in the video ram. Unlike the monochrome
	function dupdate(), gupdate() only does a quick operation indicating
	that drawing and exposed buffers have been swapped, but nothing on the
	screen will change until the gray timer fires.
*/
void gupdate(void);

/*
	gclear()
	Clears the gray video ram, making all pixels white.
*/
void gclear(void);

/*
	grect()
	Draws a rectangle in the gray video ram; this function accepts all
	values of the color_t type, including gray operators.
*/
void grect(int x1, int y1, int x2, int y2, color_t operator);



//---
//	Local drawing functions.
//---

/*
	gpixel()
	Puts a pixel in the vram. This function accepts all values of the
	color_t type, including gray operators.
*/
void gpixel(size_t x, size_t y, color_t operator);

/*
	gline()
	Draws a line in the vram while automatically optimizing special cases.
	This function supports all plain colors from the color_t type, but not
	the gray operators. If you need them for horizontal or vertical lines,
	you may want to use grect() as a replacement.
*/
void gline(int x1, int y1, int x2, int y2, color_t operator);

#endif	// _GRAY_H
