//---
//
//	gint drawing module: bopti
//
//	This module is a powerful bitmap renderer. It *heavily* relies on the
//	line-based structure of the video RAM as well as the high density of
//	information. A single CPU access (longword operation) can affect 32
//	pixels at once, which is crucial for performance. The same goes for all
//	other drawing modules, but this one typically has 350 lines of code
//	just to wrap these longword accesses -- and it's blazingly fast.
//
//---

#ifndef	_BOPTI_H
#define	_BOPTI_H

/*
	image_t
	This structure holds meta-data of a bitmap encoded with fxconv. Data is
	accessed using longword operations for performance considerations,
	which requires that the all fields of the structure be properly aligned
	and of a correct size.
*/
typedef struct
{
	uint8_t magic;
	uint8_t format;

	uint8_t width;
	uint8_t height;

	const uint32_t data[];

} __attribute__((packed, aligned(4))) image_t;

/*
	dimage()
	Displays a monochrome image in the vram. This function does a real lot
	of optimization.
*/
void dimage(int x, int y, image_t *image);

/*
	dimage_part()
	Draws a portion of an image, defined by its bounding rectangle.
	Point (left, top) is included, but (left + width, top + height) is
	excluded.
*/
void dimage_part(
	int x, int y,
	image_t *img,
	int left, int top, int width, int height
);

/*
	gimage()
	Displays a gray image in the dual-vram.
*/
void gimage(int x, int y, image_t *image);

/*
	gimage_part()
	Draws a portion of a gray image, defined by its bounding rectangle.
	Point (left, top) is included, but (left + width, top + height) is
	excluded.
*/
void gimage_part(
	int x, int y,
	image_t *image,
	int left, int top, int width, int height
);

#endif	// _BOPTI_H
