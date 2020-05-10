//---
//
//	gint display module: screen
//
//	Interacts with the physical screen. See other display modules for video
//	ram management and drawing.
//
//	The screen basically has two input values, which are a register
//	selector and the selected register's value. What this module does is
//	essentially selecting registers by setting *selector and assigning them
//	values by setting *data.
//---

#ifndef	_SCREEN_H
#define	_SCREEN_H

/*
	screen_display()
	Displays contents on the full screen. Expects a 1024-byte buffer.
*/
void screen_display(const void *vram);

/*
	screen_setBacklight()
	On compatible models, turns on or turns off the backlight.
*/
void screen_setBacklight(int on);

/*
	screen_toggleBacklight()
	Changes the backlight state, regardless of its current state.
*/
void screen_toggleBacklight(void);

#endif
