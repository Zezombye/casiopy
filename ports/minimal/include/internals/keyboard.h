#ifndef	_INTERNALS_KEYBOARD_H
#define	_INTERNALS_KEYBOARD_H

#include <keyboard.h>
#include <timer.h>
#include <clock.h>

// Current keyboard state and keyboard interrupt flag.
extern volatile uint8_t keyboard_state[10];
extern volatile int interrupt_flag;

// Delays (milliseconds) before repetitions, last key pressed, how many times
// it has been repeated already, time elapsed since last repetition (ms).
extern int repeat_first, repeat_next;
extern int last_key, last_repeats, last_time;

// Virtual timer object.
extern timer_t *vtimer;

/*
	getPressedKey()
	Finds a pressed key in the keyboard state and returns it.
*/
int getPressedKey(volatile uint8_t *keyboard_state);

/*
	getPressedKeys()
	Find 'count' pressed keys in the keyboard state and fills the 'keys'
	array. Returns the number of keys found.
	WARNING: keyboard artifacts make this function read as pressed keys
	that aren't (typically, LEFT + DOWN + SHIFT => ALPHA).
*/
int getPressedKeys(volatile uint8_t *keyboard_state, int *keys, int count);

/*
	keyboard_updateState()
	Updates the keyboard state.
*/
void keyboard_updateState_7705(volatile uint8_t *state);
void keyboard_updateState_7305(volatile uint8_t *state);

/*
	keyboard_interrupt()
	Answers an interrupt event by updating the keyboard state and
	generating the associated keyboard events.
*/
void keyboard_interrupt(void);

#endif	// _INTERNALS_KEYBOARD_H
