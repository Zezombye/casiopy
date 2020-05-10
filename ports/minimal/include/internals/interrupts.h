#ifndef	_INTERNALS_INTERRUPTS_H
#define	_INTERNALS_INTERRUPTS_H

#include <stdint.h>

/*
	inth_timer_underflow()
	Wake up, your timer has expired!
*/
void inth_timer_underflow(uint32_t channel);

/*
	inth_rtc_periodic()
	Don't you forget to execute the periodic tasks.
*/
void inth_rtc_periodic(void);

#endif	// _INTERNALS_INTERRUPTS_H
