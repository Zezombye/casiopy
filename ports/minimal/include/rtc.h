//---
//
//	gint core module: rtc
//
//	Manages the Real-Time Clock (RTC). This module provides access to the
//	current time as well as regular callbacks at predefined frequencies,
//	more or less like a timer.
//	The standard time module is built upon this one.
//
//---

#ifndef	_RTC_H
#define	_RTC_H

#include <stdint.h>

//---
//	Time access.
//---

/*
	rtc_time_t
	Defines a point in time.
*/
typedef struct
{
	uint8_t seconds;	// Seconds in range 0-59
	uint8_t minutes;	// Minutes in range 0-59
	uint8_t hours;		// Hours in range 0-23
	uint8_t month_day;	// Day of month in range 1-31
	uint8_t month;		// Month in range 0-11
	uint8_t week_day;	// Day of week in range 0(Sunday)-6(Saturday).
	uint16_t year;		// Years (around 2000)

} rtc_time_t;

/*
	rtc_getTime()
	Reads the current time from the RTC. There is no guarantee that the
	week day is correct (use the time API for that).
*/
void rtc_getTime(rtc_time_t *time);

/*
	rtc_setTime()
	Sets the time in the RTC registers. The week day is set to 0 if greater
	than 6. Other fields are not checked.
*/
void rtc_setTime(const rtc_time_t *time);



//---
//	Callback API.
//---

/*
	rtc_frequency_t
	Describes the possible frequencies available for the real-time clock
	interrupt.
*/
typedef enum
{
	rtc_freq_500mHz	= 7,
	rtc_freq_1Hz	= 6,
	rtc_freq_2Hz	= 5,
	rtc_freq_4Hz	= 4,
	rtc_freq_16Hz	= 3,
	rtc_freq_64Hz	= 2,
	rtc_freq_256Hz	= 1,
	rtc_freq_none	= 0,

} rtc_frequency_t;

/*
	rtc_cb_add()
	Registers a new callback for the RTC. Returns the callback id on
	success (positive integer), or one of the following error codes:
	  -1	Array is full
	  -2	Invalid parameter
	The number of repeats may be set to 0, in which case the callback is
	called indefinitely unless the user calls rtc_cb_end().
*/
int rtc_cb_add(rtc_frequency_t freq, void (*function)(void), int repeats);

/*
	rtc_cb_end()
	Removes the callback with the given id (as returned by rtc_cb_add())
	from the callback array.
*/
void rtc_cb_end(int id);

/*
	rtc_cb_edit()
	Changes information related to a callback. This function returns 0 on
	success, or one of the following error codes:
	  -1	Callback does not exist
	  -2	Invalid parameters
	This function never removes a callback. Call rtc_cb_end() for this. One
	can set the function to NULL or the frequency to rtc_freq_none to
	temporarily disable the callback.
*/
int rtc_cb_edit(int id, rtc_frequency_t new_freq, void (*new_function)(void));

#endif	// _RTC_H
