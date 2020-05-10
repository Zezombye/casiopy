#ifndef	_INTERNALS_TIMER_H
#define	_INTERNALS_TIMER_H

#include <timer.h>
#include <stdint.h>

/*
	timer_t
	A virtual or hardware timer. We need to declare the struct timer_t name
	so that we can forward-reference it.
*/
typedef struct timer_t
{
	// Current delay, how much time elapsed since last interrupt occurred.
	uint32_t ms_delay;
	uint32_t ms_elapsed;

	// Is the virtual slot free? Is the virtual timer active?
	uint8_t	used		:1;
	uint8_t	active		:1;
	// Is this a virtual timer? Is this the virtual timer support?
	uint8_t virtual		:1;
	uint8_t vsupport	:1;
	// How many events do I have received but not executed?
	uint8_t	events		:4;
	// How many repeats are left.
	uint32_t repeats_left	:24;

	// Callback function (NULL for event-firing timers) and its argument.
	void *callback;
	void *argument;

} __attribute__((packed, aligned(4))) timer_t;

// Hardware timers.
extern timer_t htimers[3];
// Virtual timers.
extern timer_t vtimers[TIMER_SLOTS];

/*
	timer_interrupt()
	Handles the interrupt for the given timer channel.
*/
void timer_interrupt(int channel);

/*
	timer_callback_event()
	Executes the callback of a timer, or pushes a new timer event depending
	on the timer configuration. Also reduces the amount of repeats left and
	clears the active flag (or stops the hardware timer) if this number
	falls from one to zero.
*/
void timer_callback_event(timer_t *timer);

/*
	vtimer_interrupt()
	Interrupt handling subsystem for the virtual timers.
*/
void vtimer_interrupt(void);

/*
	vtimer_updateOne()
	Update the virtual timer hardware support timer, knowing that a virtual
	timer with the given delay has been started.
*/
void vtimer_updateOne(int additional_delay_ms);

/*
	vtimer_updateAll()
	Updates the virtual timer hardware support after computing the GCD of
	all virtual timers delays. This is rather long so avoid calling this
	when possible.
*/
void vtimer_updateAll(void);

#endif	// _INTERNALS_TIMER_H
