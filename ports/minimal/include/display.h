//---
//
//	gint drawing module: display
//
//	This module does most of the monochrome drawing. It manages the video
//	memory although image rendering and text rendering, as complex tasks,
//	are left to other modules (bopti and tales, respectively).
//
//---

#ifndef	_DISPLAY_H
#define	_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

//---
//	Drawing-related types and constants.
//---

#define	DWIDTH	128	/* Width of the screen */
#define	DHEIGHT	64	/* Height of the screen */

/*
	color_t
	Defines all colors that the library knows about:
	- white is exactly what you think it is;
	- light is a light gray used by the gray module;
	- dark is a dark gray, also used by the gray engine;
	- black is nothing more than black; (sorry)
	- none means transparent, but is shorter to write.
	There are also some transformation-associated colors:
	- invert reverses the intensity of the color (white -> black, dark ->
	  light, etc);
	- lighten is some kind of partially-transparent white. It lightens the
	  color which it is drawn onto (black -> dark, light -> light);
	- lighten2 is the same as lighten, except it lightens more (black ->
	  light, light -> white);
	- darken is the exact opposite of lighten (light -> dark, black ->
	  black).
	- darken2 is the same to darken as lighten2 to lighten (white -> dark,
	  dark -> black);
	All transformations except invert only operate when the gray engine is
	running.
*/
typedef enum
{
	color_white	= 0,
	color_light	= 1,
	color_dark	= 2,
	color_black	= 3,
	color_none	= 4,

	color_invert	= 5,
	color_lighten	= 6,
	color_lighten2	= 7,
	color_darken	= 8,
	color_darken2	= 9,

} color_t;

// The bopti module provides bitmap rendering functions.
#include <bopti.h>

// The tales module provides text rendering functions but requires the color_t
// type definition.
#include <tales.h>



//---
//	Video RAM management.
//---

/*
	display_getLocalVRAM()
	Returns gint's local video RAM address. Gint does not use the system's
	buffer because it is misaligned. This function always returns the same
	address. Both the display and the gray module heavily use this buffer;
	make sure you don't interfere with them if you access it.
	This function does not necessarily returns the video ram that is
	currently in use; call display_getCurrentVRAM() for this.
*/
uint32_t *display_getLocalVRAM(void);

/*
	display_getCurrentVRAM()
	Returns the current monochrome video ram buffer. This function usually
	returns the parameter of the last call to display_useVRAM(), or the
	local vram address (which is default when the library starts).
	The return value of this function is undefined if the gray engine is
	running.
*/
uint32_t *display_getCurrentVRAM(void);

/*
	display_useVRAM()
	Changes the current monochrome video ram address. The argument must be
	a 4-aligned 1024-byte buffer because the library's design requires it.
	This function refuses misaligned buffers but trusts that enough space
	is available; failing to provide enough memory may crash the program.
	This function will most likely have no effect when running the gray
	engine.
*/
void display_useVRAM(uint32_t *vram);



//---
//	Global drawing functions.
//---

/*
	dupdate()
	Pushes the video RAM to the physical screen. This function also works
	when the gray engine is running, but that's probably not what you want.
*/
void dupdate(void);

/*
	dclear()
	Clears the whole video ram, making all pixels white.
*/
void dclear(void);

/*
	drect()
	Draws a rectangle on the screen. This function can use any color which
	is not associated with the gray engine, including the reverse operator.
	Both end points (x1, y1) and (x2, y2) are affected as well.
*/
void drect(int x1, int y1, int x2, int y2, color_t operator);



//---
//	Local drawing functions.
//---

/*
	dpixel()
	Changes a pixel's color in the video ram. The result may depend on the
	current color of the pixel.
*/
void dpixel(size_t x, size_t y, color_t operator);

/*
	dline()
	Draws a line in the vram. Automatically optimizes horizontal and
	vertical lines.

	Uses an algorithm written by PierrotLL for MonochromeLib.
*/
void dline(int x1, int y1, int x2, int y2, color_t operator);

#endif	// _DISPLAY_H
