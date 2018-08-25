#ifndef	_INTERNALS_RTC_H
#define	_INTERNALS_RTC_H

#include <rtc.h>
#include <stddef.h>

#ifndef	RTC_CB_ARRAY_SIZE
#define	RTC_CB_ARRAY_SIZE	5
#endif

/*
	rtc_callback_t
	An RTC callback with a unique id.
*/
typedef struct
{
	rtc_frequency_t freq;
	int id;

	void (*callback)(void);
	int repeats;

} rtc_callback_t;

// The callback array.
rtc_callback_t cb_array[RTC_CB_ARRAY_SIZE];

/*
	rtc_perodic_interrupt()
	Handles periodic interrupts and calls the callbacks.
*/
void rtc_periodic_interrupt(void);

/*
	rtc_cb_interrupt()
	Calls the RTC callbacks if necessary, and updates the repeat counts.
	Should only be called when RTC periodic interrupts occur.
*/
void rtc_cb_interrupt(void);

#endif	// _INTERNALS_RTC_H
