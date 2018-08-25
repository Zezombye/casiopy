//---
//
//	gint drawing module: tales
//
//	Text displaying. Does some pretty good optimization, though requires
//	dynamic allocation. The stack is used.
//
//---

#ifndef	_TALES_H
#define	_TALES_H

#include <display.h>
#include <stdint.h>
#include <stddef.h>

//---
//	Types and constants.
//---

/*
	font_format_t
	This type holds information about the characters in the font. Each bit
	represents various characters, and the type itself is a combination of
	several of those bits.
	Bits represent the following characters (lsb right):
	--  --  --  non-print  |  special  capitals  lower  numbers
*/
typedef enum
{
	font_format_unknown	= 0x00,
	font_format_numeric	= 0x01,
	font_format_lower	= 0x02,
	font_format_upper	= 0x04,
	font_format_letters	= 0x06,
	font_format_common	= 0x07,
	font_format_print	= 0x0f,
	font_format_ascii	= 0x1f,

} font_format_t;

/*
	font_glyph_t
	Holds a glyph's data. The width is used for spacing, and the raw data
	is encoded line after line, from to to bottom, by appending bits
	without consideration of the byte boundaries.
	This structure is actually never used, because data is read directly
	as a longword array (hence the 4-byte alignment).
*/
typedef struct
{
	uint8_t width;
	const uint8_t data[];

} __attribute__((packed, aligned(4))) font_glyph_t;

/*
	font_t
	Holds a font's data. Data is accessed using longword operations, hence
	the 4-alignment attributes. The line height is the one given in the
	font image header line, which may be used by applications that write
	strings on several lines. The data height is the height of the biggest
	glyph. Every glyph is encoded on 'data_height' lines, for optimization
	considerations.	
	The index field is used to reduce character access time.
	The name field may not be NUL-terminated when the name contains 28
	characters. When the name is shorter, the field is padded with zeros.
*/
typedef struct
{
	uint8_t magic;
	uint8_t format;
	uint8_t line_height;
	uint8_t data_height;

	// Warning : this field may not be NUL-terminated.
	char name[28];

	uint16_t index[16];

	__attribute__((aligned(4))) const uint32_t glyphs[];

} __attribute__((packed, aligned(4))) font_t;



//---
//	Generic functions.
//---

/*
	text_configure()
	Sets the font and color to use for subsequent text operations. Pass
	font = NULL to use the default font.
*/
void text_configure(font_t *font, color_t operator);

/*
	text_length()
	Computes the length of a string using the currently configured font.
*/
size_t text_length(const char *str);

/*
	dtext()
	Prints the given string, without any analysis.
*/
void dtext(int x, int y, const char *str);

/*
	gtext()
	Prints the given raw string.
*/
void gtext(int x, int y, const char *str);

/*
	dprint()
	Prints a formatted string. Works the same as printf().
*/
void dprint(int x, int y, const char *format, ...);

/*
	gprint()
	Prints a formatted string. Works the same as printf().
*/
void gprint(int x, int y, const char *format, ...);

#endif	// _TALES_H
