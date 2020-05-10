//---
//
//	gint core module: keyboard analyzer
//
//	Probably the most difficult hardware interaction. There is very few
//	documentation on how the system actually analyzes the keyboard. While
//	disassembling syscalls reveals the following procedure (which was
//	already documented by SimonLothar), there is nothing about the
//	detection problems of the multi-getkey system.
//
//---

#ifndef	_KEYBOARD_H
#define	_KEYBOARD_H

#include <stdint.h>
#include <rtc.h>

//---
//	Keycodes and related.
//---

/*
	key_t
	The following codes are gint matrix codes. They are not compatible with
	the system's. Some keycodes are special event codes; all others are
	made of a key identifier and possibly one or more modifiers.
	Binary-and a keycode with MOD_CLEAR to remove the modifiers; this will
	not work with special event codes.
*/
typedef enum
{
	// Special events codes.
	KEY_NONE	= 0x00,
	KEY_NOEVENT	= 0xff,

	// Key modifiers.
	MOD_SHIFT	= 0x80,
	MOD_ALPHA	= 0x100,
	MOD_CLEAR	= ~(MOD_SHIFT | MOD_ALPHA),

	// Key identifiers.

	KEY_F1		= 0x69,
	KEY_F2		= 0x59,
	KEY_F3		= 0x49,
	KEY_F4		= 0x39,
	KEY_F5		= 0x29,
	KEY_F6		= 0x19,

	KEY_SHIFT	= 0x68,
	KEY_OPTN	= 0x58,
	KEY_VARS	= 0x48,
	KEY_MENU	= 0x38,
	KEY_LEFT	= 0x28,
	KEY_UP		= 0x18,

	KEY_ALPHA	= 0x67,
	KEY_SQUARE	= 0x57,
	KEY_POWER	= 0x47,
	KEY_EXIT	= 0x37,
	KEY_DOWN	= 0x27,
	KEY_RIGHT	= 0x17,

	KEY_XOT		= 0x66,
	KEY_LOG		= 0x56,
	KEY_LN		= 0x46,
	KEY_SIN		= 0x36,
	KEY_COS		= 0x26,
	KEY_TAN		= 0x16,

	KEY_FRAC	= 0x65,
	KEY_FD		= 0x55,
	KEY_LEFTP	= 0x45,
	KEY_RIGHTP	= 0x35,
	KEY_COMMA	= 0x25,
	KEY_ARROW	= 0x15,

	KEY_7		= 0x64,
	KEY_8		= 0x54,
	KEY_9		= 0x44,
	KEY_DEL		= 0x34,
	KEY_AC_ON	= 0x24,

	KEY_4		= 0x63,
	KEY_5		= 0x53,
	KEY_6		= 0x43,
	KEY_MUL		= 0x33,
	KEY_DIV		= 0x23,

	KEY_1		= 0x62,
	KEY_2		= 0x52,
	KEY_3		= 0x42,
	KEY_PLUS	= 0x32,
	KEY_MINUS	= 0x22,

	KEY_0		= 0x61,
	KEY_DOT		= 0x51,
	KEY_EXP		= 0x41,
	KEY_NEG		= 0x31,
	KEY_EXE		= 0x21,

} key_t;



//---
//	Keyboard configuration.
//---

/*
	keyboard_setAnalysisDelay()
	Sets the keyboard analysis delay, that is, the delay (in ms) between
	two keyboard analyzes. If a key is pressed then released in the lapse
	between two analyzes, the program won't notice anything. On the other
	hand, if the program spends too much time reading the keyboard, it will
	lose a bit of execution power.
	The default frequency is about 40 Hz; very few programs will need to
	change this setting. Please note that the repeat delays should be
	multiples of the analysis delay for better accuracy.
*/
void keyboard_setAnalysisDelay(int analysis_delay_ms);

/*
	keyboard_setRepeatRate()
	Sets the default repeat rate for key events. The delay before the first
	repeat may have a different value (usually longer). The unit for the
	argument is ms, but the repeat events themselves may only be fired when
	a keyboard analysis is performed; which means that for better accuracy,
	these delays should be a multiple of the keyboard period. The keyboard
	period may be changed by calling keyboard_setAnalysisDelay().
	For instance, delays of (625 ms, 125 ms) will imitate the system's
	default setting.
	You can disable repetitions by passing 0 as arguments:
	- if first = 0, no repetition will ever occur;
	- if first != 0 and next = 0, only one repetition will occur.
*/
void keyboard_setRepeatRate(int first, int next);



//---
//	Keyboard access.
//---

/*
	getkey_opt_t
	Options available to customize the behavior of the getkey_opt()
	function.
*/
typedef enum
{
	getkey_none			= 0x00,

	// Consider [SHIFT] and [ALPHA] as modifiers. Returns key identifiers
	// with MOD_SHIFT and MOD_ALPHA flags instead of returning KEY_SHIFT
	// and KEY_ALPHA.
	getkey_shift_modifier		= 0x01,
	getkey_alpha_modifier		= 0x02,

	// Allow changing the backlight status on [SHIFT] + [OPTN] on
	// compatible models.
	getkey_manage_backlight		= 0x04,

	// Allow returning to menu using the [MENU] key. (This operation is not
	// absolutely safe.)
	getkey_task_switch		= 0x08,

	// Allow key repetition. This option does not control the generation of
	// repeat events (use keyboard_setRepeatRate() for this) but filters
	// them. Please note that modifiers will never be repeated, even when
	// pressed continuously.
	getkey_repeat_arrow_keys	= 0x10,
	getkey_repeat_char_keys		= 0x20,
	getkey_repeat_ctrl_keys		= 0x40,
	getkey_repeat_func_keys		= 0x80,
	// Shorthand for the four previous properties.
	getkey_repeat_all_keys		= 0xf0,

	// Default combination of getkey().
	getkey_default			= 0x1f,

} getkey_option_t;

/*
	getkey()
	Blocking function with auto-repeat that heeds for the SHIFT and ALPHA
	modifiers. In short, this function reproduces the behavior of the
	system's GetKey() function. It returns a matrix code, possibly with
	modifier bits.
	This function does not return until a key is pressed.
*/
int getkey(void);

/*
	getkey_opt()
	Enhances getkey() with more general functionalities. An OR-combination
	of options of type getkey_option_t may be given as first argument.
	If delay is non-zero and positive, getkey_opt() will return KEY_NOEVENT
	if no event occurs during the given delay. Please note that this
	function can only ever return after a keyboard analysis is performed;
	the actual delay may exceed the requested time if it's not a multiple
	of the keyboard period (which can be changed by calling
	keyboard_setAnalysisDelay()).
	Like getkey(), returns the pressed key matrix code, possibly with
	modifiers depending on the options.
*/
int getkey_opt(getkey_option_t options, int delay_ms);

/*
	multigetkey()

	Listens the keyboard for simultaneous key hits. This functions fills
	the 'keys' array with 'count' keycodes, padding with KEY_NONE values at
	the end if less that 'count' keys are detected.
	If 'delay_ms' is positive and nothing happens during this delay, this
	function returns an array of KEY_NONE. Please note that the delay
	detection suffers the same limitation as getkey_opt().

	This function suffers from severe limitations and may not be very
	convenient to use. For more accuracy, consider using the event system.

	WARNING:
	Because of hardware limitations, this function generally yields poor
	results. Rectangle and column effects make it read unpressed keys as
	pressed (see documentation for more information). The more pressed
	keys, the more errors.

	The results are guaranteed to be exact if two keys or less are pressed.
	With three keys or more, column effects (on SH4) and rectangle effects
	(on both platforms) mess up the results by making this function think
	that some keys, which are actually released, are pressed.

	This function is designed to make combinations of one or two arrow keys
	with another key as viable as possible. On SH4, this works pretty well
	even if combinations like Left + Down + SHIFT trigger ALPHA sometimes.
	On SH3, rectangle effects are *always* present, making it impossible to
	use Left + Down or Up + Right with any other key in their rows without
	having this function return junk.

	Any other combination of keys may quite randomly result in variably
	incorrect results. Please do not expect multigetkey() to work as an
	ideal multi-key analyzer.
*/
void multigetkey(int *keys, int count, int delay_ms);

/*
	keyboard_stateBuffer()

	Returns the address of the keyboard state array. The keyboard state
	consists in 10 bytes, in which every key is represented as a bit.
	The returned address is the original buffer address. You should avoid
	editing the array. It wouldn't influence the behavior of the keyboard
	functions, but the buffer data is very volatile and any data written to
	it could be replaced anytime without prior notice.

	If the user wishes to do really advanced keyboard management that they
	can't achieve it using the library, they can access this buffer.
	Updates of this buffer's contents can be detected by watching the
	'interrupt_flag' variable defined in internals/keyboard.h. However, the
	library will continue firing events so the user needs to catch them and
	ignore them.
*/
volatile uint8_t *keyboard_stateBuffer(void);



//---
//	Key analysis.
//---

/*
	keyid()
	Transforms a key identifier and returns a key code that is more
	convenient for array subscript that the original matrix codes. The new
	codes are laid out the following way:

	          +0    +1    +2    +3    +4    +5
	        ------------------------------------
	  +0  |   F1    F2    F3    F4    F5    F6
	  +6  |  SHIFT OPTN  VARS  MENU  Left  Top
	 +12  |  ALPHA  x^2   ^    EXIT  Down Right
	 +18  |  X,O,T log    ln   sin   cos   tan
	 +24  |  Frac  F<>D   (     )     ,     ->
	 +30  |   7     8     9    DEL  AC/ON
	 +36  |   4     5     6     *     /
	 +42  |   1     2     3     +     -
	 +48  |   0     .    x10^  (-)   EXE

	The returned key code is the sum of the line and column headings. For
	instance key_id(KEY_SIN) would be 18 + 3 = 21. Please note that there
	are a few holes in the numbering.
	This function ignores modifiers and returns -1 on error.
*/
int key_id(int matrix_key);

/*
	key_char()
	Returns the ASCII character associated with a character key, and 0 for
	other keys. This function expects a matrix code and not a key_id()
	code, and heeds for the ALPHA modifier.
*/
int key_char(int matrix_key);

/*
	key_type_t
	Categorizes the keyboard's keys into several types:
	- Arrow keys only include the REPLAY pad;
	- Function keys only include the F1 .. F6 keys;
	- Character keys are those which input characters;
	- Control characters are all others.
*/
typedef enum
{
	key_type_arrow		= 1,
	key_type_character	= 2,
	key_type_control	= 4,
	key_type_function	= 8,

} key_type_t;

/*
	key_type()
	Returns a key's type. This functions ignores modifiers and expects
	matrix codes as argument, not key_id() codes.
*/
key_type_t key_type(int matrix_key);

#endif	// _KEYBOARD_H
