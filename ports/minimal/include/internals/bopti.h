#ifndef	_INTERNALS_BOPTI_H
#define	_INTERNALS_BOPTI_H

#include <stdint.h>
#include <display.h>

/*
	channel_t
	Indicates what operation a layer is made for. Each operation affects
	the video ram differently (setting or clearing pixels, transparency,
	etc). An image is made of several layers.
*/
typedef enum
{
	channel_full_alpha	= 0x01,
	channel_light_alpha	= 0x02,
	channel_dark_alpha	= 0x04,

	channel_mono		= 0x08,
	channel_light		= 0x10,
	channel_dark		= 0x20,

} channel_t;

/*
	format_t
	Describes the various combination of layer channels that are allowed by
	bopti. Technically one could try other formats but they're not of much
	use (transparent gray is even totally useless).
*/
typedef enum
{
	format_mono		= channel_mono,
	format_mono_alpha	= format_mono | channel_full_alpha,
	format_gray		= channel_light | channel_dark,
	format_gray_alpha	= format_gray | channel_full_alpha,
	format_greater_alpha	= format_mono | channel_light_alpha |
				  channel_dark_alpha
} format_t;

/*
	structure_t
	Basically an image's dimensions, data pointer, and a few other useful
	information such as the pitch in bytes.
*/
typedef struct
{
	int width, height;
	int layer_size;

	const uint8_t *data;
	int columns;
	int end_size, end_bytes;

} structure_t;

/*
	command_t
	The parameters of a drawing operation. A pointer to such a structure is
	created by the public functions and passed down to the module's
	sub-functions during rendering.
*/
typedef struct command_t
{
	// Channel being drawn.
	channel_t channel;
	// Operation used (whether bopti_op_mono() or bopti_op_gray()).
	void (*op)(int offset, uint32_t operator, struct command_t *command);
	// Portion of the bitmap which is drawn. 'top' and 'bottom' refer to
	// lines where 'left' and 'right' refer to column ids.
	int left, right, top, bottom;
	// Position of the bitmap on the screen.
	int x, y;
	// Rectangle masks that define the drawing area.
	uint32_t masks[4];
	// Video rams being used.
	union {
		// "Different names, same fate." (Kingdom Hearts II)
		uint32_t *vram;
		uint32_t *v1;
	};
	uint32_t *v2;

} command_t;

// The video ram addresses are set by the public functions and used internally
// by the module.
// Monochrome video ram, light and dark buffers (in this order).
extern uint32_t *bopti_vram, *bopti_v1, *bopti_v2;



//---
//	Internal bopti routines.
//---

/*
	bopti_op()
	Operates on a vram long. The operator will often not contain 32 bits of
	image information. Since neutral bits are not the same for all
	operations, a mask is used to indicate which bits should be used for
	the operation. This mask is taken for the image's rectangle masks (see
	the 'display' module internal header for more information on rectangle
	masks). Which operation is performed is determined by the channel
	setting of the command argument.
*/
void bopti_op_mono(int offset, uint32_t operator, command_t *c);
void bopti_op_gray(int offset, uint32_t operator, command_t *c);

/*
	bopti_grid()		-- general form
	bopti_grid_a32()	-- when x is a multiple of 32

	Draws the grid at the beginning of a layer's data. The length of this
	grid is always a multiple of 32.
	The need for bopti_grid_a32() is not only linked to optimization,
	because bopti_grid() will perform a 32-bit shift when x is a multiple
	of 32, which is undefined behavior.
	bopti_grid() automatically calls bopti_grid_a32() when required.
*/
void bopti_grid_a32(const uint32_t *layer, int columns, int height,
	command_t *c);
void bopti_grid(const uint32_t *layer, int columns, int height, command_t *c);
/*
	bopti_end_get()
	Returns an operator for the end of a line, whose width is lower than 32
	(by design: otherwise, it would have been a column). The given pointer
	is read and updated so that it points to the next line at the end of
	the operation.
*/
uint32_t bopti_end_get1(const unsigned char **data);
uint32_t bopti_end_get2(const unsigned char **data);

/*
	bopti_rest()		-- general form
	bopti_rest_nover()	-- when the end does not overlap two vram longs

	Draws the end of a layer, which can be considered as a whole layer
	whose with is lower than 32. (Actually is it lower or equal to 16;
	otherwise it would have been a column and the end would be empty). The
	'size' arguments is in bytes, thus 1 or 2.
	Unlike bopti_grid_a32(), bopti_end_nover() is not called automatically
	by bopti_end().
*/
void bopti_end_nover(const unsigned char *end, int size, command_t *c);
void bopti_end(const unsigned char *end, int size, command_t *c);

/*
	bopti()
	Draws a layer's data in the video ram areas specified in the command
	argument.
*/
void bopti(const unsigned char *layer, structure_t *s, command_t *c);

/*
	getStructure()
	Determines the image size (large images have a somehow different
	structure), the data pointer and a few dimensions inside the image.
*/
void getStructure(image_t *img, structure_t *structure);

#endif	// _INTERNALS_BOPTI_H
